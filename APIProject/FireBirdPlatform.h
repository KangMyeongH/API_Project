#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"

class FireBirdPlatform :public MonoBehaviour
{
public:
	FireBirdPlatform(GameObject* owner) : MonoBehaviour(owner), mReturnDelayTime(0), mReturnDurationTime(0), mReturnCurrentTime(0),
		  mReturnSpeed(100.f), mIsReturn(false),
		  mHp(4) {}

	~FireBirdPlatform() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void OnCollisionEnter(Collision other) override;
	void Damaged();
	void Damaged(int damage);
	void Respawn();
	void Return2OriginPosition();
	void StartReturn();
	void GetRandomStartPosition();

	AnimationInfo* FindAniInfo(const TCHAR* key);

	void SetReturnSpeed(float speed) { mReturnSpeed = speed; }

private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	Vector2 	mOriginPosition;
	Vector2		mReturnStartPosition;
	float		mReturnDelayTime;
	float		mReturnDurationTime;
	float 		mReturnCurrentTime;
	float		mReturnSpeed;
	bool		mIsReturn;
	int 		mHp;

};

