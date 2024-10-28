#include "pch.h"
#include "SwingState.h"

#include "Animator.h"
#include "Camera.h"
#include "ClimbingState.h"
#include "GameObject.h"
#include "Grab.h"
#include "IdleState.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "StateMachine.h"
#include "SwingJumpState.h"

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
		if (mRight) mPlayer->GetAnimator()->Flip(false);
		else mPlayer->GetAnimator()->Flip(true);
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SHIFT))
	{
		mIsDash = true;
	}

	if (mPlayer->GetKeyMgr()->Key_Up(VK_LBUTTON))
	{
		float omegaVelocity = mOmega * mLength;
		Vector2 velocity = { cos(mTheta) * omegaVelocity, -sin(mTheta) * omegaVelocity };
		mPlayer->GetRigidbody()->Velocity() = velocity * 5.f;
		mPlayer->GetRigidbody()->SetUseGravity(true);
		mPlayer->IsGrounded = false;
		mPlayer->GetGrab()->SetIsShoot(false);
		mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(0);

		if (mPlayer->GetRigidbody()->GetVelocity().y < -600.f)
		{
			mStateMachine->ChangeState(mPlayer->SwingJump);
		}

		else
		{
			mStateMachine->ChangeState(mPlayer->Jump);
			mPlayer->GetAnimator()->MotionChange(mPlayer->FindAniInfo(L"SNB_SwingJump"));
			mPlayer->GetAnimator()->SetNextMotion(mPlayer->FindAniInfo(L"SNB_Falling"));
		}
	}

	if (mPlayer->GetKeyMgr()->Key_Down(VK_SPACE))
	{
		mIsRush = true;
	}

	if (mPlayer->GetKeyMgr()->Key_Pressing(VK_SPACE))
	{
		mIsRush = true;
	}
}

void SwingState::LogicUpdate()
{
	Vector2 position = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y };
	mPlayer->GetGameObject()->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(position, mPivot) + 90.f);
}

void SwingState::PhysicsUpdate()
{
	Swinging();
	if (mLength == 0.f)
	{
		if (mPlayer->IsClimb)
		{
			mStateMachine->ChangeState(mPlayer->Climbing);
		}

		else
		{
			mStateMachine->ChangeState(mPlayer->Jump);
		}

	}
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
}

void SwingState::StartSwinging()
{
	mIsRush = false;
	mPlayer->GetRigidbody()->SetUseGravity(false);
	mPivot = mPlayer->GetGrab()->GetTargetPosition();

	Vector2 startPos = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y - mPlayer->GetTransform()->GetWorldScale().y * 0.5f };
	if (startPos.x < mPivot.x)
	{
		mPlayer->GetGameObject()->GetComponent<Animator>()->Flip(false);
	}
	if (startPos.x > mPivot.x)
	{
		mPlayer->GetGameObject()->GetComponent<Animator>()->Flip(true);
	}

	mLength = Vector2::Distance(startPos, mPivot);
	//mPlayer->GetRigidbody()->Velocity() = { 0,0 };
	mMaxAddOmega = 0.0015f;
	mTime = 0.05f;
	mGravity = 9.8f;
	mTheta = atan2(startPos.x - mPivot.x, startPos.y - mPivot.y); // 초기 각도 구해주기

	Vector2 initialVelocity = mPlayer->GetRigidbody()->GetVelocity();

	float initialSpeed = sqrt(initialVelocity.x * initialVelocity.x + initialVelocity.y * initialVelocity.y);
	mOmega = initialSpeed / mMaxLineLength /10.f; // 초기 각 속도
	float directionSign = (initialVelocity.x * -sin(mTheta) + initialVelocity.y * cos(mTheta)) >= 0 ? 1.0f : -1.0f;
	mOmega *= directionSign; // 각속도의 방향 반영


	float Test = mTheta * 57.2958f;

	mCurrentTime = 0;
	mIsDash = false;
	mIsFinish = false;

}

void SwingState::Swinging()
{
	if (!mIsRush && mMaxLineLength < mLength)
	{
		mLength -= 8.f;
		if (mLength <= mMaxLineLength)
		{
			mLength = mMaxLineLength;
		}
	}

	if (mIsDash && !mIsFinish)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		float duration = .5f;
		float t = mCurrentTime / duration;
		float easeFactor = easeInOutQuint(t);

		if (mCurrentTime >= duration)
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

	float lengthRatio = 1.f;
	if (mLength != 0 && mLength < mMaxLineLength)
	{
		lengthRatio = mMaxLineLength / mLength;
	}

	mOmega += (-mGravity / mMaxLineLength * sin(mTheta)) * mTime;

	if (abs(mOmega) >= mMaxOmega + 0.05f)
	{
		if (mOmega < 0) mOmega = -(mMaxOmega + 0.05f);
		else if (mOmega > 0) mOmega = mMaxOmega + 0.05f;
	}

	if (mIsRush)
	{
		mOmega = 0;
		mLength -= 8.f;
		if (mLength <= 0.f)
		{
			mLength = 0.f;
		}
	}

	float adjustedOmega = mOmega * lengthRatio;

	mTheta += adjustedOmega * mTime;

	// 새로운 위치 계산
	float newX = mPivot.x + mLength * sin(mTheta);
	float newY = mPivot.y + mLength * cos(mTheta);

	mPlayer->GetTransform()->SetWorldPosition({ newX,newY });
}

void SwingState::Debug(ID2D1DeviceContext* render)
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

	// 출력할 영역 설정
	D2D1_RECT_F layoutRect = D2D1::RectF(10, 10, 400, 100);

	wchar_t array[32];
	swprintf_s(array, 32, L"%f", mOmega);

	// 텍스트를 그리기
	render->DrawText(
		array,
		wcslen(array),
		textFormat,
		layoutRect,
		brush
	);

	Vector2 startPos = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y};


	D2D1_POINT_2F p1 = Camera::GetInstance().WorldToScreenVector({ startPos.x, startPos.y});
	D2D1_POINT_2F p2 = Camera::GetInstance().WorldToScreenVector({ mPivot.x, mPivot.y });

	render->DrawLine(
		p1,
		p2,
		brush,
		5.0f,
		nullptr
	);

	textFormat->Release();
	brush->Release();


}
