#pragma once
#include "MonoBehaviour.h"


class Platform : public MonoBehaviour
{
public:
	Platform(GameObject* owner) : MonoBehaviour(owner), mType(), mCanHit(false), mIsGrab(false) {}
	Platform(GameObject* owner, bool canHit, bool canGrab) : MonoBehaviour(owner), mType(), mCanHit(canHit), mIsGrab(canGrab) {}

	void SetType(PlatformType type) { mType = type; }

	PlatformType GetType() const { return mType; }

	void SetHit(bool hit) { mCanHit = hit; }

	void SetGrab(bool grab) { mIsGrab = grab; }

	bool CanHit() const { return mCanHit; }

	bool IsGrab() const { return mIsGrab; }

protected:
	PlatformType 	mType;
	bool 			mCanHit;
	bool			mIsGrab;
};