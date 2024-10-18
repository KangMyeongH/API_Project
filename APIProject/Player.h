#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class ExcState;
class ExcDashState;
class Grab;
class GrabObject;
class Ray;
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
	                                     mStateMachine(nullptr), mRay(nullptr), mGrab(nullptr), mTarget(nullptr),
	                                     mFovAngle(0),
	                                     mFowLength(0), mLineAnimationOffset(0),
	                                     Idle(nullptr), Run(nullptr), Jump(nullptr), ChargeDash(nullptr),
	                                     ExcDash(nullptr), Exc(nullptr),
	                                     Speed(0)
	{
	}

	~Player() override;
	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void OnCollisionEnter(Collision other) override;
	void Debug(ID2D1HwndRenderTarget* render) override;

	// bool FindEnemy();

	void FindEnemy();

	bool IsEnemyInFOV(Vector2 playerDir, Vector2 enemyPosition);
	bool IsEnemyVisible(Vector2 enemyPosition, GameObject* enemy);

	void SetGrab(Grab* grab) { mGrab = grab; }

	KeyManager* GetKeyMgr() const { return mKeyMgr; }
	Rigidbody* 	GetRigidbody() const { return mRigidbody; }
	Animator* 	GetAnimator() const { return mAnimator; }
	AnimationInfo* FindAniInfo(const TCHAR* key);
	GameObject* GetTarget() const { return mTarget; }
	StateMachine* GetStateMachine() const { return  mStateMachine; }
	Grab* GetGrab() const { return mGrab; }

private:
	bool LineIntersectsRect(Vector2 p1, Vector2 direction, D2D1_RECT_F rect);
	bool LineIntersectsLine(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);
	float Direction(Vector2 pi, Vector2 pj, Vector2 pk);
	bool OnSegment(Vector2 pi, Vector2 pj, Vector2 pk);

private:
	KeyManager* mKeyMgr;
	Rigidbody* mRigidbody;
	Transform* mTransform;
	Collider* mCollider;
	Animator* mAnimator;
	StateMachine* mStateMachine;

	Ray* mRay;
	Grab* mGrab;
	GameObject* mTarget;
	float mFovAngle;
	float mFowLength;

	float mLineAnimationOffset;

public:
	std::unordered_map<const TCHAR*, AnimationInfo*> AnimationMap;
	IdleState* 			Idle;
	RunState* 			Run;
	JumpState* 			Jump;
	ChargeDashState* 	ChargeDash;
	ExcDashState* 		ExcDash;
	ExcState* 			Exc;


	float		Speed;
};

