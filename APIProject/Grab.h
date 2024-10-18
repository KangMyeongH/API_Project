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

	void Shoot(Transform* target);

	Transform* GetTarget() const { return mTarget; }

	void Debug(ID2D1HwndRenderTarget* render) override;

	AnimationInfo* FindAniInfo(const TCHAR* key);


private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	Player* 		mPlayer;
	Transform* 		mTarget;
	Vector2			mStart;
	float 			mTime;
	float 			mCurrentTime;
	bool 			mIsShoot;
};

