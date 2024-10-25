#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class Player;

class Grab final : public MonoBehaviour
{
public:
	explicit Grab(GameObject* owner) : MonoBehaviour(owner), mPlayer(nullptr), mTarget(nullptr),
	                                                   mTime(0.1f),
	                                                   mCurrentTime(0), mIsShoot(false)
	{
	}

	~Grab() override;
	void Awake() override;

	void Start() override;

	void FixedUpdate() override;

	void OnCollisionEnter(Collision other) override;

	void SetOwner(Player* player) { mPlayer = player; }

	void Shoot();

	void SetIsShoot(bool isShoot) { mIsShoot = isShoot; }

	bool IsShoot() const { return mIsShoot; }

	Transform* GetTarget() const { return mTarget; }

	const Vector2& GetTargetPosition() const { return mTargetPosition; }

	void Debug(ID2D1DeviceContext* render) override;

	AnimationInfo* FindAniInfo(const TCHAR* key);


private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	Player* 		mPlayer;
	Transform* 		mTarget;
	Vector2			mTargetPosition;
	Vector2			mStart;
	float 			mTime;
	float 			mCurrentTime;
	bool 			mIsShoot;
};

