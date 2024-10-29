#pragma once
#include <unordered_map>

#include "GameObject.h"
#include "MonoBehaviour.h"

class ExcAttackState;
class SwingJumpState;
class ChargeDashAttackState;
class SwingState;
class ClimbingState;
class ExcState;
class ExcDashState;
class Grab;
class GrabObject;
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
	                                     mStateMachine(nullptr), mGrab(nullptr), mTargetEnemy(nullptr),
	                                     mTargetPlatform(nullptr), mChargeTarget(nullptr),
	                                     mFovAngle(0),
	                                     mFovLength(0), mLineAnimationOffset(0),
	                                     Idle(nullptr), Run(nullptr), Jump(nullptr), ChargeDash(nullptr),
	                                     ChargeAttack(nullptr),
	                                     ExcDash(nullptr), Exc(nullptr), Climbing(nullptr), Swing(nullptr),
	                                     Speed(0), JumpPower(0), IsGrounded(false), IsClimb(false)
	{
	}

	~Player() override;
	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void OnCollisionEnter(Collision other) override;
	void OnCollisionStay(Collision other) override;
	void OnCollisionExit(Collision other) override;
	void Debug(ID2D1DeviceContext* render) override;

	// bool FindEnemy();

	void FindEnemy();
	void FindHanging();

	bool IsEnemyInFOV(Vector2 playerDir, Vector2 enemyPosition);
	bool IsEnemyVisible(Vector2 enemyPosition, GameObject* enemy);

	void SetGrab(Grab* grab) { mGrab = grab; }
	void SetChargeTarget(GameObject* target) { mChargeTarget = target; }

	KeyManager* 	GetKeyMgr() const { return mKeyMgr; }
	Rigidbody* 		GetRigidbody() const { return mRigidbody; }
	Animator* 		GetAnimator() const { return mAnimator; }
	AnimationInfo* 	FindAniInfo(const TCHAR* key);
	GameObject* 	GetTarget() const { return mTargetEnemy; }
	GameObject* 	GetTargetPlatform() const { return mTargetPlatform; }
	GameObject* 	GetChargeTarget() const { return  mChargeTarget; }
	StateMachine* 	GetStateMachine() const { return  mStateMachine; }
	Grab* 			GetGrab() const { return mGrab; }
	const Vector2& 	GetGrabPoint() const { return mGrabPoint; }

private:
	bool LineIntersectsRect(Vector2 p1, Vector2 direction, D2D1_RECT_F rect);
	bool LineIntersectsLine(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);
	bool IntersectRayWithBox(const Vector2& rayStart, const Vector2& rayDir, const D2D1_RECT_F& rect, Vector2& intersectionPoint);
	bool IntersectRayWithLineSegment(const Vector2& rayStart, const Vector2& rayDir, const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersection);

	float Direction(Vector2 pi, Vector2 pj, Vector2 pk);
	bool OnSegment(Vector2 pi, Vector2 pj, Vector2 pk);

	void ApplyDistortionEffect(ID2D1HwndRenderTarget* renderTarget)
	{
		ID2D1Bitmap* bitmap = mOwner->GetComponent<SpriteRenderer>()->GetBitmap();

		// 원래 비트맵을 그릴 위치와 크기
		D2D1_RECT_F originalRect = D2D1::RectF(0, 0, bitmap->GetSize().width, bitmap->GetSize().height);

		// 변형된 비트맵을 그릴 위치와 크기 (여기서 왜곡이 적용됨)
		D2D1_RECT_F distortedRect = D2D1::RectF(10, 10, bitmap->GetSize().width + 30, bitmap->GetSize().height - 20);

		// 비트맵을 왜곡된 영역에 그리기
		renderTarget->DrawBitmap(
			bitmap,
			distortedRect,
			1.0f,  // 투명도
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,  // 선형 보간 모드
			originalRect  // 원본 비트맵 영역
		);
	}

private:
	KeyManager* mKeyMgr;
	Rigidbody* mRigidbody;
	Transform* mTransform;
	Collider* mCollider;
	Animator* mAnimator;
	StateMachine* mStateMachine;

	Grab* mGrab;
	GameObject* mTargetEnemy;
	GameObject* mTargetPlatform;
	GameObject* mChargeTarget;
	Vector2 mGrabPoint;
	float mFovAngle;
	float mFovLength;

	float mLineAnimationOffset;

public:
	std::unordered_map<const TCHAR*, AnimationInfo*> AnimationMap;
	IdleState* 				Idle;
	RunState* 				Run;
	JumpState* 				Jump;
	ChargeDashState* 		ChargeDash;
	ChargeDashAttackState* 	ChargeAttack;
	ExcDashState* 			ExcDash;
	ExcState* 				Exc;
	ExcAttackState* 		ExcAttack;
	ClimbingState* 			Climbing;
	SwingState* 			Swing;
	SwingJumpState* 		SwingJump;
	
	float		Speed;
	float		JumpPower;
	bool		IsGrounded;
	bool		IsClimb;
};