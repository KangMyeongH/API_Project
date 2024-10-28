#pragma once
#include "Behaviour.h"
class SpriteRenderer;

class Animator : public Behaviour
{
public:
    Animator(GameObject* owner) : Behaviour(owner), mSprite(nullptr), mNextMotion(nullptr), mFrameStart(0),
                                  mFrameEnd(0), mSpeed(0), mTime(0),
                                  mLoop(false),
                                  mPause(false), mFinish(false)
    {
    }

    void MoveFrame();

    void SetSprite(SpriteRenderer* sprite) { mSprite = sprite; }

    void MotionChange(ID2D1Bitmap* image, int start, int end, float width, float height, float speed);
    void MotionChange(AnimationInfo* nextMotion);
    void Loop(bool loop) { mLoop = loop; }
    void Pause(bool pause) { mPause = pause; }
    void Restart() { mFrameStart = 0; }
    void Flip(bool flip);
    void Destroy() override;
    bool IsFinish() const { return mFinish; }
    void SetNextMotion(AnimationInfo* nextMotion);

    bool IsNextMotionPending()
    {
        if (mNextMotion) return true;
        
        return false;
    }

private:
    SpriteRenderer* 	mSprite;
    AnimationInfo* 		mNextMotion;
    int     			mFrameStart;
    int     			mFrameEnd;
    float   			mSpeed;
    float   			mTime;
    bool                mLoop;
    bool                mPause;
    bool                mFinish;
};

