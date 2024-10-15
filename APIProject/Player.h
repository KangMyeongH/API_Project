#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
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
	                                     mTransform(nullptr),
	                                     mAnimator(nullptr),
	                                     mStateMachine(nullptr),
	                                     Idle(nullptr), Run(nullptr), Speed(0)
	{
	}

	~Player() override;
	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	KeyManager* GetKeyMgr() const { return mKeyMgr; }

	Rigidbody* 	GetRigidbody() const { return mRigidbody; }
	Animator* 	GetAnimator() const { return mAnimator; }

	AnimationInfo* FindAniInfo(const TCHAR* key);


private:
	KeyManager* mKeyMgr;

	Rigidbody* mRigidbody;
	Transform* mTransform;
	Animator* mAnimator;
	StateMachine* mStateMachine;

public:
	std::unordered_map<const TCHAR*, AnimationInfo*> AnimationMap;
	IdleState* 	Idle;
	RunState* 	Run;
	JumpState* 	Jump;
	float		Speed;
};

