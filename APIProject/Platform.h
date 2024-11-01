#pragma once
#include "GameObject.h"
#include "MonoBehaviour.h"


class Platform : public MonoBehaviour
{
public:
	Platform(GameObject* owner) : MonoBehaviour(owner), mType(), mCanHit(false), mIsGrab(false) {}
	Platform(GameObject* owner, bool canHit, bool canGrab) : MonoBehaviour(owner), mType(), mCanHit(canHit), mIsGrab(canGrab) {}
	Platform(GameObject* owner, PlatformType type, bool canHit, bool canGrab) : MonoBehaviour(owner), mType(type), mCanHit(canHit), mIsGrab(canGrab) {}

	void SetType(PlatformType type) { mType = type; }

	PlatformType GetType() const { return mType; }

	void SetHit(bool hit) { mCanHit = hit; }

	bool GetHit() const { return mCanHit; }

	void SetGrab(bool grab) { mIsGrab = grab; }

	bool GetGrab() const { return mIsGrab; }

	bool CanHit() const { return mCanHit; }

	bool IsGrab() const { return mIsGrab; }

protected:
	PlatformType 	mType;
	bool 			mCanHit;
	bool			mIsGrab;
};