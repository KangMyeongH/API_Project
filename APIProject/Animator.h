#pragma once
#include "Behaviour.h"
class SpriteRenderer;

class Animator : public Behaviour
{
public:
    Animator(GameObject* owner) : Behaviour(owner), mSprite(nullptr), mNextMotion(nullptr), mFrameStart(0),
                                  mFrameEnd(0), mSpeed(0), mTime(0),
                                  mLoop(false),
                                  mPause(false)
    {
    }

    void MoveFrame();

    void SetSprite(SpriteRenderer* sprite) { mSprite = sprite; }

   // void MotionChange(HDC hdc, int start, int end, float width, float height, float speed);
    void MotionChange(AnimationInfo* nextMotion);
    void Loop(bool loop) { mLoop = loop; }
    void Pause(bool pause) { mPause = pause; }
    void Restart() { mFrameStart = 0; }
    void Flip(bool flip);
    void Destroy() override;

    void SetNextMotion(AnimationInfo* nextMotion);

private:
    SpriteRenderer* 	mSprite;
    AnimationInfo* 		mNextMotion;
    int     			mFrameStart;
    int     			mFrameEnd;
    float   			mSpeed;
    float   			mTime;
    bool                mLoop;
    bool                mPause;
};

