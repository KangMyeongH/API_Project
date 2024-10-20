#include "pch.h"
#include "Animator.h"

#include "SpriteRenderer.h"
#include "TimeManager.h"

void Animator::MoveFrame()
{
	if (mSpeed < mTime + TimeManager::GetInstance().GetDeltaTime() && !mPause)
	{
		++mFrameStart;

		if (mFrameStart == mFrameEnd)
		{
			if (mLoop) mFrameStart = 0;
			else
			{
				if (mNextMotion)
				{
					mFrameStart = 0;
					MotionChange(mNextMotion);
				}

				else
				{
					mFrameStart--;
				}
			}
		}
		mTime = 0;
	}
	mSprite->SetFrame(mFrameStart);
	mTime += TimeManager::GetInstance().GetDeltaTime();
}


void Animator::MotionChange(ID2D1Bitmap* image, int start, int end, float width, float height, float speed)
{
	mFrameStart = start;
	mFrameEnd = end;
	mSpeed = speed;
	mTime = TimeManager::GetInstance().GetDeltaTime();
	mSprite->ChangeSprite(image, width, height, start);
}

void Animator::MotionChange(AnimationInfo* nextMotion)
{
	mFrameStart = nextMotion->Start;
	mFrameEnd = nextMotion->End;
	mSpeed = nextMotion->Speed;
	mTime = TimeManager::GetInstance().GetDeltaTime();
	mSprite->ChangeSprite(nextMotion->Image, nextMotion->Width, nextMotion->Height, nextMotion->Start);
	mLoop = nextMotion->Loop;
	mNextMotion = nullptr;
}

void Animator::Flip(bool flip)
{
	mSprite->Flip(flip);
}

void Animator::Destroy()
{
	AnimatorManager::GetInstance().RemoveAnimator(this);
	mOwner->RemoveComponent(this);
}

void Animator::SetNextMotion(AnimationInfo* nextMotion)
{
	mNextMotion = nextMotion;
}

