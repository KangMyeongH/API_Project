#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class ChargeDashState;
class Collider;
class JumpState;
class RunState;
class KeyManager;
class IdleState;
class StateMachine;
class Animator;
class Rigidbody;

class Player final : public MonoBehaviour
{
public:
	explicit Player(GameObject* owner) : MonoBehaviour(owner), mKeyMgr(nullptr), mRigidbody(nullptr),
	                                     mTransform(nullptr), mCollider(nullptr),
	                                     mAnimator(nullptr),
	                                     mStateMachine(nullptr),
	                                     Idle(nullptr), Run(nullptr), Jump(nullptr), Speed(0)
	{
	}

	~Player() override;
	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void OnCollisionEnter(Collision other) override;

	KeyManager* GetKeyMgr() const { return mKeyMgr; }

	Rigidbody* 	GetRigidbody() const { return mRigidbody; }
	Animator* 	GetAnimator() const { return mAnimator; }

	AnimationInfo* FindAniInfo(const TCHAR* key);


private:
	KeyManager* mKeyMgr;
	Rigidbody* mRigidbody;
	Transform* mTransform;
	Collider* mCollider;
	Animator* mAnimator;
	StateMachine* mStateMachine;

public:
	std::unordered_map<const TCHAR*, AnimationInfo*> AnimationMap;
	IdleState* 	Idle;
	RunState* 	Run;
	JumpState* 	Jump;
	ChargeDashState* ChargeDash;

	float		Speed;
};

