#include "pch.h"
#include "Grab.h"

#include "BoxCollider.h"
#include "ExcDashState.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ImageManager.h"
#include "MouseObj.h"
#include "Player.h"
#include "SoundMgr.h"
#include "StateMachine.h"
#include "SwingState.h"
#include "TimeManager.h"
#include "Transform.h"

Grab::~Grab()
{
	for (auto& ani : mAnimationMap)
	{
		delete ani.second;
	}
}

void Grab::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
}

void Grab::Start()
{
	mPlayer = GameObjectManager::GetInstance().GetGameObjectsForTag(PLAYER)->front()->GetComponent<Player>();
	mPlayer->SetGrab(this);
	ImageManager::GetInstance().InsertBmp(L"./Sprite/03. SNBGrab/Spr_SNBGrab_Flying.png", L"Grab_Flying");

	mAnimationMap.insert({ L"Grab_Flying",new AnimationInfo(ImageManager::GetInstance().FindImage(L"Grab_Flying"), 0, 1, 25, 67, 0.2f, false) });
	mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"Grab_Flying"));
	mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
	mOwner->GetComponent<Animator>()->SetEnable(false);
	mOwner->GetComponent<BoxCollider>()->SetEnable(false);
}

void Grab::FixedUpdate()
{
	if (mIsShoot)
	{
		mCurrentTime += TimeManager::GetInstance().GetDeltaTime();
		if (mCurrentTime > mTime)
		{
			mCurrentTime = mTime;
			if (mTarget->GetGameObject()->CompareTag(ENEMY))
			{
				mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
				mOwner->GetComponent<Animator>()->SetEnable(false);
				mOwner->GetComponent<BoxCollider>()->SetEnable(false);
				mPlayer->GetStateMachine()->ChangeState(mPlayer->ExcDash);
				mIsShoot = false;
			}

			else if (mTarget->GetGameObject()->CompareTag(PLATFORM))
			{
				mOwner->GetComponent<SpriteRenderer>()->SetEnable(false);
				mOwner->GetComponent<Animator>()->SetEnable(false);
				mOwner->GetComponent<BoxCollider>()->SetEnable(false);
				mPlayer->GetStateMachine()->ChangeState(mPlayer->Swing);
			}
		}
		GetTransform()->SetWorldPosition(Vector2::Lerp(mStart, mTargetPosition, mCurrentTime / mTime));
	}
}

void Grab::OnCollisionEnter(Collision other)
{
}

void Grab::Shoot()
{
	if (!mIsShoot)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_SNB_Shoot.wav", SOUND_PLAYER_EFFECT, gEffectVolume);
		Camera::GetInstance().Shake(0.05f, 10.f);
		mOwner->GetComponent<SpriteRenderer>()->SetEnable(true);
		mOwner->GetComponent<Animator>()->SetEnable(true);
		mOwner->GetComponent<BoxCollider>()->SetEnable(true);
		mCurrentTime = 0;
		GetTransform()->SetWorldPosition(mPlayer->GetTransform()->GetWorldPosition());
		mStart = GetTransform()->GetWorldPosition();
		if (mPlayer->GetTarget())
		{
			mTarget = mPlayer->GetTarget()->GetTransform();
			mTargetPosition = mTarget->GetWorldPosition();
		}

		else if (mPlayer->GetTargetPlatform())
		{
			mTarget = mPlayer->GetTargetPlatform()->GetTransform();
			mTargetPosition = mPlayer->GetGrabPoint();
		}

		mOwner->GetComponent<SpriteRenderer>()->SetAngle(Vector2::GetAngle(mStart, mTargetPosition) + 90.f);
		mOwner->GetComponent<Animator>()->MotionChange(FindAniInfo(L"Grab_Flying"));
		mIsShoot = true;
	}
}

void Grab::Debug(ID2D1DeviceContext* render)
{
	if (mIsShoot)
	{
		Vector2 startPos = { mPlayer->GetTransform()->GetWorldPosition().x, mPlayer->GetTransform()->GetWorldPosition().y };

		Vector2 mPivot = mOwner->GetTransform()->GetWorldPosition();

		float dx = mPivot.x - startPos.x;
		float dy = mPivot.y - startPos.y;

		float lineLength = sqrtf(dx * dx + dy * dy);

		D2D1_POINT_2F direction = { dx / lineLength, dy / lineLength };

		float currentDistance = 0.0f;

		float angle = Vector2::GetAngle(startPos, mPivot);

		ID2D1Bitmap* pBitmap = ImageManager::GetInstance().FindImage(L"SNB_Chain");

		// ���� ���� �̹����� �ݺ������� �׸�
		while (currentDistance <= lineLength)
		{
			// ���� ��ġ���� �̹����� �׸� ��ǥ ���
			D2D1_POINT_2F imagePosition = {
				startPos.x + direction.x * currentDistance,
				startPos.y + direction.y * currentDistance
			};

			// ���� ��ȯ ���� ����
			D2D1_MATRIX_3X2_F originalTransform;
			render->GetTransform(&originalTransform);

			// �̹��� �׸��� ���� ���� (�߾��� �������� �̹��� ��ġ)
			D2D1_RECT_F destRect = D2D1::RectF(
				imagePosition.x - pBitmap->GetSize().width / 2,
				imagePosition.y - pBitmap->GetSize().height / 2,
				imagePosition.x + pBitmap->GetSize().width / 2,
				imagePosition.y + pBitmap->GetSize().height / 2
			);

			D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(destRect);

			// ȸ�� �߽� (mRenderRect�� �߽��� �������� ȸ���Ѵٰ� ����)
			D2D1_POINT_2F center = D2D1::Point2F(
				(screenRect.left + screenRect.right) / 2.0f,
				(screenRect.top + screenRect.bottom) / 2.0f
			);

			// ȸ�� ��ȯ ����
			D2D1_MATRIX_3X2_F rotationMatrix = Matrix3x2F::Rotation(angle + 90.f, center);

			// ��ȯ ����
			render->SetTransform(rotationMatrix);

			// �̹��� �׸���
			render->DrawBitmap(pBitmap, screenRect);

			// ���� ��ȯ ���� ����
			render->SetTransform(originalTransform);

			// ���� �̹����� �׸��� ���� �̵��� �Ÿ� ����
			currentDistance += 8.f;
		}
	}
}

AnimationInfo* Grab::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(mAnimationMap.begin(), mAnimationMap.end(), tagFinder(key));

	if (iter == mAnimationMap.end()) return nullptr;

	return iter->second;
}
