#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"

class FireBirdBomb;

enum AttackType
{
	SHOOT,
	BOMBER,
	BEHIND_FIRE,
	BODY_ATTACK,
	RETURN,
	DAMAGED,
	PHASE02,
	ENDDING
};

class FireBird final : public MonoBehaviour
{
public:
	explicit FireBird(GameObject* owner)
		: MonoBehaviour(owner), mWingAnimation{nullptr,}, mBrokenWingAnimation{nullptr,}, mPattern(RETURN),
		  mPlayer(nullptr),
		  mWing(nullptr), mGun(nullptr),
		  mBomber(nullptr), mShootAim(nullptr), mBomb{nullptr,}, mHp(8),
		  mBaseForce(10.f),
		  mForceFactor(2.f),
		  mMaxForce(80.f), mMaxAngle(3.f), mBombDelay(0.5f), mBombCurrentTime(0), mCurrentTime(0), mWingIndex(-1),
		  mBombIndex(0),
		  mReadyBehind(false), mIsShoot(false), mReadyBodyAttack(false)
	{
	}

	~FireBird() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void OnCollisionEnter(Collision other) override;
	void Debug(ID2D1DeviceContext* render) override;

	AnimationInfo* FindAniInfo(const TCHAR* key);
	void ShootPattern();
	void BomberPattern();
	void BehindFirePattern();
	void BodyAttackPattern();
	void ReturnPattern();
	void DamagedPattern();

	void Damaged();

	void ChangeWingIndex();

	void SetRandomPattern();

	void SetWing(GameObject* wing) { mWing = wing; }
	void SetBomber(GameObject* bomber) { mBomber = bomber; }
	void SetGun(GameObject* gun) { mGun = gun; }
	void SetBomb(FireBirdBomb* bomb);

	Vector2 GetAngle() const { return mAngle; }
	std::unordered_map<const TCHAR*, AnimationInfo*>* GetAnimationMap() { return &mAnimationMap; }



private:
	float clamp(float value, float minValue, float maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}

private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	AnimationInfo* mWingAnimation[9];
	AnimationInfo* mBrokenWingAnimation[9];
	AttackType 	mPattern;

	GameObject* mPlayer;
	GameObject* mWing;
	GameObject* mGun;
	GameObject* mBomber;
	GameObject* mShootAim;

	FireBirdBomb* mBomb[8];

	Vector2		mTargetPosition;
	Vector2		mAngle;
	int			mHp;
	float		mBaseForce;
	float		mForceFactor;
	float		mMaxForce;
	float		mMaxAngle;
	float		mBombDelay;
	float		mBombCurrentTime;
	float		mCurrentTime;
	int			mWingIndex;
	int			mBombIndex;
	bool		mReadyBehind;
	bool		mIsShoot;
	bool		mReadyBodyAttack;
};

