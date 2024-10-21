#include "pch.h"
#include "SwingState.h"

#include "Animator.h"
#include "Camera.h"
#include "GameObject.h"
#include "Grab.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "StateMachine.h"

void SwingState::Enter()
{
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_Swing"));
	StartSwinging();
}

void SwingState::HandleInput()
{
	if (mPlayer->GetKeyMgr()->Key_Pressing('D'))
	{
		mOmega += mMaxAddOmega;
		mRight = true;
		mLeft = false;
	}

	else if (mPlayer->GetKeyMgr()->Key_Pressing('A'))
	{
		mOmega -= mMaxAddOmega;
		mRight = false;
		mLeft = true;
	}

	if (mPlayer->GetKeyMgr()->Key_Up('D'))
	{
		mRight = false;
	}

	else if (mPlayer->GetKeyMgr()->Key_Up('A'))
	{
		mLeft = false;
	}

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SHIFT))
	{
		mIsDash = true;
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SHIFT))
	{
		mIsDash = true;
	}

	if (mPlayer->GetKeyMgr()->Key_Up(VK_LBUTTON))
	{
		mStateMachine->ChangeState(mPlayer->Jump);
	}
}

void SwingState::LogicUpdate()
{
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mPlayer->GetTransform()->GetWorldPosition(), mPivot) + 90.f);
}

void SwingState::PhysicsUpdate()
{
	Swinging();
}

void SwingState::Exit()
{
	float omegaVelocity = mOmega * mLength;
	Vector2 velocity = { cos(mTheta) * omegaVelocity, -sin(mTheta) * omegaVelocity };
	mPlayer->GetRigidbody()->Velocity() = velocity * 5.f;
	mPlayer->GetRigidbody()->SetUseGravity(true);
	mPlayer->IsGrounded = false;
	mPlayer->GetGrab()->SetIsShoot(false);
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);
	mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_SwingJumpUp"));
	mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Rolling"));
}

void SwingState::StartSwinging()
{
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPivot = mPlayer->GetGrabPoint();

	Vector2 startPos = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y - mPlayer->GetTransform()->GetWorldScale().y * 0.5f };
	mLength = Vector2::Distance(startPos, mPivot);
	//mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mMaxAddOmega = 0.0015f;
	mTime = 0.05f;
	mGravity = 9.8f;
	mTheta = atan2(startPos.x - mPivot.x, startPos.y - mPivot.y); // �ʱ� ���� �����ֱ�

	Vector2 initialVelocity = mPlayer->GetRigidbody()->GetVelocity();

	float initialSpeed = sqrt(initialVelocity.x * initialVelocity.x + initialVelocity.y * initialVelocity.y);
	mOmega = initialSpeed / mLength /10.f; // �ʱ� �� �ӵ�
	float directionSign = (initialVelocity.x * -sin(mTheta) + initialVelocity.y * cos(mTheta)) >= 0 ? 1.0f : -1.0f;
	mOmega *= directionSign; // ���ӵ��� ���� �ݿ�


	float Test = mTheta * 57.2958f;

	mCurrentTime = 0;
	mIsDash = false;
	mIsFinish = false;

}

void SwingState::Swinging()
{
	if (mMaxLineLength < mLength)
	{
		mLength -= 25.f;
		if (mLength <= mMaxLineLength)
		{
			mLength = mMaxLineLength;
		}
	}

	if (mIsDash && !mIsFinish)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		float duration = 1.5f;
		float t = mCurrentTime / duration;
		float easeFactor = easeInOutQuint(t);

		if (easeFactor >= 1.5f)
		{
			mCurrentTime = mTime;
			mIsFinish = true;
		}

		if (mRight)
		{
			mOmega = Lerp(mOmega, mMaxOmega, easeFactor);
		}

		else if (mLeft)
		{
			mOmega = Lerp(mOmega, -mMaxOmega, easeFactor);
		}

		else if(mOmega > 0)
		{
			mOmega = Lerp(mOmega, mMaxOmega, easeFactor);
		}

		else if(mOmega < 0)
		{
			mOmega = Lerp(mOmega, -mMaxOmega, easeFactor);
		}
	}

	mOmega += (-mGravity / mLength * sin(mTheta)) * mTime * 2;

	float linearVelocity = mOmega * mLength;
	Vector2 direction = { -sin(mTheta), cos(mTheta) };

	mTheta += mOmega * mTime * 2;

	// ���ο� ��ġ ���
	float newX = mPivot.x + mLength * sin(mTheta);
	float newY = mPivot.y + mLength * cos(mTheta);

	mPlayer->GetTransform()->SetWorldPosition({ newX,newY });
}

void SwingState::Debug(ID2D1HwndRenderTarget* render)
{
	IDWriteTextFormat* textFormat = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

	gWriteFactory->CreateTextFormat(
		L"Arial",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&textFormat
	);

	render->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);

	// ����� ���� ����
	D2D1_RECT_F layoutRect = D2D1::RectF(10, 10, 400, 100);

	wchar_t array[32];
	swprintf_s(array, 32, L"%f", mOmega);

	// �ؽ�Ʈ�� �׸���
	render->DrawText(
		array,
		wcslen(array),
		textFormat,
		layoutRect,
		brush
	);

	Vector2 startPos = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y - mPlayer->GetTransform()->GetWorldScale().y * 0.5f };


	D2D1_POINT_2F p1 = Camera::GetInstance().WorldToScreenVector({ startPos.x, startPos.y });
	D2D1_POINT_2F p2 = Camera::GetInstance().WorldToScreenVector({ mPivot.x, mPivot.y });

	render->DrawLine(
		p1,
		p2,
		brush,
		1.0f,
		nullptr
	);

	textFormat->Release();
	brush->Release();




}