#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class FloatingBomb final : public MonoBehaviour
{
public:
	explicit FloatingBomb(GameObject* owner)
		: MonoBehaviour(owner), mBoundary({2800.f, 1600.f}), mSpeed(0), mIsExc(false),
		  mIsKnockBack(false), mIsExplode(false)
	{
	}

	~FloatingBomb() override
	{
		for(auto& ani : mAnimationMap)
		{
			delete ani.second;
		}
	}

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void OnEnable() override;
	void OnDisable() override;
	void OnCollisionEnter(Collision other) override;

	AnimationInfo* FindAniInfo(const TCHAR* key);

private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	Vector2 mBoundary;
	Vector2 mDir;
	float 	mSpeed;
	bool	mIsExc;
	bool	mIsKnockBack;
	bool	mIsExplode;
};


