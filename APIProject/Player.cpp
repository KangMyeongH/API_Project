#include "pch.h"
#include "Player.h"
#include "BoxCollider.h"
#include "ChargeDashAttackState.h"
#include "ChargeDashState.h"
#include "ClimbingState.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "IdleState.h"
#include "ImageManager.h"
#include "JumpState.h"
#include "KeyManager.h"
#include "RunState.h"
#include "StateMachine.h"
#include "EdgeCollider.h"
#include "Effect.h"
#include "EffectObj.h"
#include "ExcDashState.h"
#include "ExcState.h"
#include "FireBirdBodyVFXObj.h"
#include "Grab.h"
#include "Platform.h"
#include "SwingState.h"
#include "TimeManager.h"

Player::~Player()
{
	delete mStateMachine;
	delete Idle;
	delete Run;
	delete Jump;
	delete ChargeDash;
	delete ExcDash;
	delete Exc;
	delete Climbing;
	delete Swing;
	delete ChargeAttack;

	for(auto& ani : AnimationMap)
	{
		delete ani.second;
	}
}

void Player::Awake()
{
	mUpdateType = static_cast<UpdateType>(mUpdateType | FIXED_UPDATE | UPDATE);
	
}

void Player::Start()
{
	// Manager
	mKeyMgr = KeyManager::Get_Instance();

	// GetComponent
	mRigidbody = mOwner->GetComponent<Rigidbody>();
	mTransform = GetTransform();
	mCollider = mOwner->GetComponent<BoxCollider>();
	mAnimator = mOwner->GetComponent<Animator>();
	mStateMachine = new StateMachine;

	Camera::GetInstance().SetTarget(mTransform);
	Camera::GetInstance().SetOffset({ 0,-132 });
	Camera::GetInstance().SetZoom(1.4f);
	

	// Component setting
	mCollider->SetOffset({ 0, -21 });

	// State
	Idle = new IdleState(this, mStateMachine, IDLE);
	Run = new RunState(this, mStateMachine, RUN);
	Jump = new JumpState(this, mStateMachine, JUMP);
	Climbing = new ClimbingState(this, mStateMachine, CLIMBING);
	ChargeDash = new ChargeDashState(this, mStateMachine, CHARGEDASH);
	ChargeAttack = new ChargeDashAttackState(this, mStateMachine, CHARGEATTACK);
	ExcDash = new ExcDashState(this, mStateMachine, EXCDASH);
	Exc = new ExcState(this, mStateMachine, EXC);
	Swing = new SwingState(this, mStateMachine, SWING);

	// Player Sprite cashing
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Idle.png", L"SNB_Idle");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Running.png", L"SNB_Running");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_RunningStart.png", L"SNB_RunningStart");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_RunningStop.png", L"SNB_RunningStop");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Landing.png", L"SNB_Landing");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Jumping.png", L"SNB_Jumping");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_FallStart.png", L"SNB_FallStart");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Falling.png", L"SNB_Falling");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_ChargeDashChargeStart.png", L"SNB_ChargeDashChargeStart");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_ChargeDashChargeLoop.png", L"SNB_ChargeDashChargeLoop");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_ChargeDashChargeEnd.png", L"SNB_ChargeDashChargeEnd");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Swing.png", L"SNB_Swing");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Land2Run.png", L"SNB_Land2Run");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_WallSlideStart.png", L"SNB_WallStart");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_WallSliding.png", L"SNB_WallSliding");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_WallClimbDown.png", L"SNB_WallClimbDown");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_WallClimbUp.png", L"SNB_WallClimbUp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_SwingJumpUp.png", L"SNB_SwingJumpUp");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_Rolling.png", L"SNB_Rolling");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_ChargeAttack.png", L"SNB_ChargeAttack");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/00. SNB/SNB_ChargeDash.png", L"SNB_ChargeDash");


	// Player Animation cashing
	AnimationMap.insert({ L"SNB_Idle",new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Idle"), 0, 8, 56, 56, 0.2f, true) });
	AnimationMap.insert({ L"SNB_Running",new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Running"), 0, 20, 56, 56, .1f, true) });
	AnimationMap.insert({ L"SNB_RunningStart",new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_RunningStart"), 0, 2, 56, 56, .1f,false) });
	AnimationMap.insert({ L"SNB_RunningStop" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_RunningStop"), 0, 6, 56, 56, .1f, false) });
	AnimationMap.insert({ L"SNB_Landing" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Landing"), 0, 3, 56, 56, .1f, false) });
	AnimationMap.insert({ L"SNB_Jumping" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Jumping"), 0, 6, 56, 56, .1f, true) });
	AnimationMap.insert({ L"SNB_FallStart" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_FallStart"), 0, 3, 56, 56, .1f, false) });
	AnimationMap.insert({ L"SNB_Falling" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Falling"), 0, 3, 56, 56, .1f, true) });
	AnimationMap.insert({ L"SNB_ChargeDashChargeStart" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_ChargeDashChargeStart"), 0, 23, 56, 56, .08f, false) });
	AnimationMap.insert({ L"SNB_ChargeDashChargeLoop" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_ChargeDashChargeLoop"), 0, 8, 56, 56, .08f, true) });
	AnimationMap.insert({ L"SNB_ChargeDashChargeEnd" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_ChargeDashChargeEnd"), 0, 9, 56, 56, .08f, false) });
	AnimationMap.insert({ L"SNB_Swing" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Swing"), 0, 29, 56, 56, .08f, true) });
	AnimationMap.insert({ L"SNB_Land2Run" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Land2Run"), 0, 12, 56, 56, .1f, false) });
	AnimationMap.insert({ L"SNB_WallStart" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_WallStart"), 0, 8, 56, 56, .1f, false) });
	AnimationMap.insert({ L"SNB_WallSliding" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_WallSliding"), 0, 11, 56, 56, .1f, true) });
	AnimationMap.insert({ L"SNB_WallClimbDown" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_WallClimbDown"), 0, 7, 56, 56, .1f, true) });
	AnimationMap.insert({ L"SNB_WallClimbUp" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_WallClimbUp"), 0, 10, 56, 56, .08f, true) });
	AnimationMap.insert({ L"SNB_SwingJumpUp" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_SwingJumpUp"), 0, 5, 56, 56, .05f, false) });
	AnimationMap.insert({ L"SNB_Rolling" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_Rolling"), 0, 12, 56, 56, .08f, true) });
	AnimationMap.insert({ L"SNB_ChargeDash" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_ChargeDash"), 0, 10, 112, 56, .08f, false) });
	AnimationMap.insert({ L"SNB_ChargeAttack" , new AnimationInfo(ImageManager::GetInstance().FindImage(L"SNB_ChargeAttack"), 0, 10, 56, 56, .08f, false) });

	// Player stat
	Speed = 275.f;
	JumpPower = 400.f;
	mFovAngle = 60.f;
	mFovLength = 500.f;

	// Init State
	mStateMachine->Initialize(Idle);
}

void Player::FixedUpdate()
{
 //mOwner->GetComponent<Animator>()->
	mStateMachine->GetCurrentState()->PhysicsUpdate();
}

void Player::Update()
{
	FindEnemy();
	if (mTargetEnemy == nullptr)
		FindHanging();

	if (mKeyMgr->Key_Down(VK_LBUTTON))
	{
		if (mTargetEnemy || mTargetPlatform)
		{
			mGrab->Shoot();
		}
	}

	if (mKeyMgr->Key_Down('G'))
	{
		GameObjectManager::GetInstance().AddGameObject<FireBirdBodyVFXObj>();
		//GameObjectManager::GetInstance().AddGameObject<EffectObj>()->GetComponent<Effect>()->SetEffect(mTransform->GetWorldPosition(), FindAniInfo(L"SNB_RunningStart"));
	}
	mStateMachine->GetCurrentState()->HandleInput();
	mStateMachine->GetCurrentState()->LogicUpdate();
}

void Player::LateUpdate()
{
}

void Player::OnCollisionEnter(Collision other)
{
	CollisionDirection dir = NONE;
	dir = CollisionManager::DetectBoxCollisionDir(*mCollider->GetRect(), *other.GetCollider()->GetRect());

	switch (mStateMachine->GetCurrentState()->GetType())
	{
	case IDLE:

		break;
	case RUN:

		break;
	case JUMP:
		if (other.GetGameObject()->CompareTag(PLATFORM) && dir & LEFT)
		{
			IsClimb = true;
		}
		break;
	case CLIMBING:

		break;
	case CHARGEDASH:

		break;
	case CHARGEATTACK:
		if (other.GetGameObject() == mChargeTarget)
		{
			mChargeTarget->GetComponent<Rigidbody>()->AddForce(mRigidbody->GetVelocity());
			mStateMachine->ChangeState(Jump);
		}
		break;
	case SWING:
		break;
	case EXC:
		break;
	case EXCDASH:
		break;
	}


	// 충돌 방향 체크
	if (other.GetGameObject()->CompareTag(ENEMY) || other.GetGameObject()->CompareTag(BOSS)) return;


	if (other.GetGameObject()->CompareTag(PLATFORM))
	{
		CollisionManager::AdjustRect(mCollider, other.GetCollider(), dir);
		if (dir & TOP && GetRigidbody()->GetVelocity().y >= 0)
		{
			IsGrounded = true;
		}

		if (dir & BOTTOM && GetRigidbody()->GetVelocity().y < 0)
		{
			GetRigidbody()->Velocity().y = 0;
		}
	}

	else if(other.GetCollider()->GetType() == ColliderType::Edge)
	{
		dir = CollisionManager::DetectEdgeCollisionDir(mRigidbody, *other.GetCollider()->GetRect());
		CollisionManager::AdjustRect(mCollider, other.GetCollider(), dir);
		if (dir & TOP && GetRigidbody()->GetVelocity().y >= 0)
		{
			IsGrounded = true;
		}

		if (dir & BOTTOM && GetRigidbody()->GetVelocity().y < 0)
		{
			GetRigidbody()->Velocity().y = 0;
		}
	}
}

void Player::OnCollisionStay(Collision other)
{
	CollisionDirection dir = NONE;


	if (other.GetGameObject()->CompareTag(PLATFORM))
	{
		dir = CollisionManager::DetectBoxCollisionDir(*mCollider->GetRect(), *other.GetCollider()->GetRect());
		CollisionManager::AdjustRect(mCollider, other.GetCollider(), dir);
		if (dir & TOP && GetRigidbody()->GetVelocity().y >= 0)
		{
			IsGrounded = true;
		}
	}

}

void Player::OnCollisionExit(Collision other)
{
	CollisionDirection dir = NONE;
	if (other.GetGameObject()->CompareTag(PLATFORM))
	{
		dir = CollisionManager::DetectEdgeCollisionDir(mRigidbody, *other.GetCollider()->GetRect());
		if (dir & TOP)
		{
			IsGrounded = false;
		}
		IsClimb = false;
	}
}

void Player::Debug(ID2D1HwndRenderTarget* render)
{
	mStateMachine->GetCurrentState()->Debug(render);

	if (mGrab->IsShoot()) return;
	if (mStateMachine->GetCurrentState()->GetType() == SWING) return;
	if (mStateMachine->GetCurrentState()->GetType() == CHARGEDASH || mStateMachine->GetCurrentState()->GetType() == CHARGEATTACK) return;
	if (mTargetEnemy || mTargetPlatform)
	{
		mLineAnimationOffset -= 10.f * TimeManager::GetInstance().GetDeltaTime();
		if (mLineAnimationOffset < -(3.0f + 3.0f))
		{
			mLineAnimationOffset = 0.0f;
		}

		std::vector<FLOAT> dashes = { 3.0f, 3.0f };
		ID2D1SolidColorBrush* brush = nullptr;
		ID2D1StrokeStyle* strokeStyle = nullptr;
		D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f
		);

		strokeStyleProperties.dashOffset = mLineAnimationOffset;

		HRESULT hr = gFactory->CreateStrokeStyle(
			strokeStyleProperties,
			dashes.data(),
			static_cast<UINT>(dashes.size()),
			&strokeStyle
		);

		if (mTargetEnemy)
		{
			D2D1_POINT_2F p1 = { mTransform->GetWorldPosition().x, mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f) };
			D2D1_POINT_2F p2 = { mTargetEnemy->GetTransform()->GetWorldPosition().x,mTargetEnemy->GetTransform()->GetWorldPosition().y };

			render->CreateSolidColorBrush(ColorF(1.f, 0.f, 0.f), &brush);

			render->DrawLine(
				Camera::GetInstance().WorldToScreenVector(p1),
				Camera::GetInstance().WorldToScreenVector(p2),
				brush,
				3.f,
				strokeStyle
			);

			strokeStyle->Release();
			brush->Release();
			brush = nullptr;

			return;
		}

		
		if (mTargetPlatform)
		{
			D2D1_POINT_2F p1 = { mTransform->GetWorldPosition().x, mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f) };
			D2D1_POINT_2F p2 = { mGrabPoint.x, mGrabPoint.y };

			render->CreateSolidColorBrush(ColorF(0.f, 0.9725f, 1.f), &brush);

			render->DrawLine(
				Camera::GetInstance().WorldToScreenVector(p1),
				Camera::GetInstance().WorldToScreenVector(p2),
				brush,
				3.f,
				strokeStyle
			);

			strokeStyle->Release();
			brush->Release();
			brush = nullptr;
		}
	}

	/*
	// 텍스트 서식 설정
	IDWriteTextFormat* textFormat = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

	gWriteFactory->CreateTextFormat(
		L"Arial",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&textFormat
	);
	*/
	/*
	render->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);

	// 출력할 영역 설정
	D2D1_RECT_F layoutRect = D2D1::RectF(10, 10, 400, 100);


	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);

	wchar_t array[32];
	swprintf_s(array, 32,L"%d, %d", mouse.x, mouse.y);

	// 텍스트를 그리기
	render->DrawText(
		array,
		wcslen(array),
		textFormat,
		layoutRect,
		brush
	);

	textFormat->Release();*/
}

void Player::FindEnemy()
{
	GameObjectList* enemyList = GameObjectManager::GetInstance().GetGameObjectsForTag(ENEMY);
	mTargetPlatform = nullptr;
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);
	Vector2 mousePosition = Camera::GetInstance().WorldToScreenMouse({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
	Vector2 playerPos = { mTransform->GetWorldPosition().x, mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f) };
	Vector2 playerDir = (mousePosition - playerPos).Normalized();

	GameObject* closestEnemy = nullptr;
	float minDistance = FLT_MAX;

	for (const auto& enemy : *enemyList)
	{
		Vector2 enemyPosition = enemy->GetTransform()->GetWorldPosition();

		if (IsEnemyInFOV(playerDir, enemyPosition))
		{
			if (IsEnemyVisible(enemyPosition, enemy))
			{
				float dx = enemyPosition.x - mTransform->GetWorldPosition().x;
				float dy = enemyPosition.y - mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f);
				float distanceToEnemy = sqrt(dx * dx + dy * dy);

				if (distanceToEnemy < minDistance)
				{
					minDistance = distanceToEnemy;
					closestEnemy = enemy;
				}
			}
		}
	}

	mTargetEnemy = closestEnemy;
	if (mTargetEnemy) mTargetPlatform = nullptr;
}

void Player::FindHanging()
{
	GameObjectList* platformList = GameObjectManager::GetInstance().GetGameObjectsForTag(PLATFORM);

	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(gHwnd, &mouse);
	Vector2 mousePosition = Camera::GetInstance().WorldToScreenMouse({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
	Vector2 rayStart = { mTransform->GetWorldPosition().x, mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f) };
	Vector2 rayDir = (mousePosition - rayStart).Normalized();

	GameObject* closestPlatform = nullptr;
	Vector2 intersectionPoint = { 0,0 };
	float minDistance = FLT_MAX;

	for (const auto& platform : *platformList)
	{
		bool isHit = false;
		Vector2 hitPoint = { 0,0 };
		if (platform->GetComponent<Platform>()->GetType() == RECT_PLATFORM)
		{
			if (!platform->GetComponent<BoxCollider>()->IsEnabled()) continue;
			RECT* rect = platform->GetComponent<BoxCollider>()->GetRect();
			isHit = IntersectRayWithBox(rayStart, rayDir, *rect, hitPoint);
		}

		else if (platform->GetComponent<Platform>()->GetType() == LINE_PLATFORM)
		{
			POINT ps = platform->GetComponent<EdgeCollider>()->GetStart();
			POINT pe = platform->GetComponent<EdgeCollider>()->GetEnd();
			Vector2 lineStart = { static_cast<float>(ps.x),static_cast<float>(ps.y) };
			Vector2 lineEnd = { static_cast<float>(pe.x), static_cast<float>(pe.y) };
			isHit = IntersectRayWithLineSegment(rayStart, rayDir, lineStart, lineEnd, hitPoint);
		}

		if (isHit)
		{
			float distance = Vector2::Distance(rayStart, hitPoint);
			if (distance <= mFovLength)
			{
				if (distance < minDistance)
				{
					closestPlatform = platform;
					minDistance = distance;
					intersectionPoint = hitPoint;
				}
			}
		}
	}

	mTargetPlatform = closestPlatform;
	mGrabPoint = intersectionPoint;
}

bool Player::IsEnemyInFOV(Vector2 playerDir, Vector2 enemyPosition)
{
	// 적과 캐릭터 사이의 벡터 계산
	Vector2 toEnemy = {
		enemyPosition.x - mTransform->GetWorldPosition().x,
		enemyPosition.y - mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f)
	};

	// 적까지의 거리 계산
	float lengthToEnemy = toEnemy.Magnitude();
	if (lengthToEnemy > mFovLength) return false;

	toEnemy = toEnemy.Normalized();

	float dotProduct = Vector2::Dot(playerDir, toEnemy);
	float angleToEnemy = acos(dotProduct) * (180.f / 3.14159f);

	return angleToEnemy <= (mFovAngle * 0.5f);
}

bool Player::IsEnemyVisible(Vector2 enemyPosition, GameObject* enemy)
{
	std::vector<Collider*>* colliders = CollisionManager::GetInstance().GetColliders();

	Vector2 dir = {
		enemyPosition.x - mTransform->GetWorldPosition().x,
		enemyPosition.y - mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f)
	};

	for (const auto& collider : *colliders)
	{
		if (!collider->IsEnabled() || collider == mCollider || collider->GetGameObject() == enemy) continue;
		if (collider->GetType() == ColliderType::Box)
		{
			D2D1_RECT_F rect = {
				static_cast<float>(collider->GetRect()->left),
				static_cast<float>(collider->GetRect()->top),
				static_cast<float>(collider->GetRect()->right),
				static_cast<float>(collider->GetRect()->bottom)
			};

			if (LineIntersectsRect({mTransform->GetWorldPosition().x, mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f) }, dir, rect))
			{
				return false;
			}
		}

		else if (collider->GetType() == ColliderType::Edge)
		{
			EdgeCollider* edge = static_cast<EdgeCollider*>(collider);

			Vector2 p1 = {
				static_cast<float>(edge->GetStart().x),
				static_cast<float>(edge->GetStart().y)
			};

			Vector2 p2 = {
				static_cast<float>(edge->GetEnd().x),
				static_cast<float>(edge->GetEnd().y)
			};

			Vector2 start = {
				mTransform->GetWorldPosition().x,
				mTransform->GetWorldPosition().y - (mTransform->GetWorldScale().y * 0.5f)
			};

			if (LineIntersectsLine(start, start + dir, p1, p2))
			{
				return false;
			}
		}
	}

	return true;
}

AnimationInfo* Player::FindAniInfo(const TCHAR* key)
{
	auto iter = std::find_if(AnimationMap.begin(), AnimationMap.end(), tagFinder(key));

	if (iter == AnimationMap.end()) return nullptr;

	return iter->second;
}

bool Player::LineIntersectsRect(Vector2 p1, Vector2 direction, D2D1_RECT_F rect)
{
	// 선분의 끝점을 계산
	Vector2 p2 = {
		p1.x + direction.x,
		p1.y + direction.y
	};

	// 사각형의 각 모서리와 교차 여부 검사
	return (LineIntersectsLine(p1, p2, { rect.left, rect.top }, { rect.right, rect.top }) ||
		LineIntersectsLine(p1, p2, { rect.right, rect.top }, { rect.right, rect.bottom }) ||
		LineIntersectsLine(p1, p2, { rect.right, rect.bottom }, { rect.left, rect.bottom }) ||
		LineIntersectsLine(p1, p2, { rect.left, rect.bottom }, { rect.left, rect.top }));

}

bool Player::LineIntersectsLine(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2)
{
	float d1 = Direction(q1, q2, p1);
	float d2 = Direction(q1, q2, p2);
	float d3 = Direction(p1, p2, q1);
	float d4 = Direction(p1, p2, q2);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return true;
	}

	return (d1 == 0 && OnSegment(q1, q2, p1)) ||
		(d2 == 0 && OnSegment(q1, q2, p2)) ||
		(d3 == 0 && OnSegment(p1, p2, q1)) ||
		(d4 == 0 && OnSegment(p1, p2, q2));
}

bool Player::IntersectRayWithBox(const Vector2& rayStart, const Vector2& rayDir,const RECT& rect, Vector2& intersectionPoint)
{
	Vector2 intersection;
	bool hasIntersection = false;
	float closetDistance = FLT_MAX;

	// 사각형의 네 변을 선분으로 간주하여 각각 검사
	std::vector<std::pair<Vector2, Vector2>> edges = {
		{{static_cast<float>(rect.left), static_cast<float>(rect.top)}, {static_cast<float>(rect.right), static_cast<float>(rect.top)}},   // 위쪽
		{{static_cast<float>(rect.right), static_cast<float>(rect.top)}, {static_cast<float>(rect.right), static_cast<float>(rect.bottom)}}, // 오른쪽
		{{static_cast<float>(rect.right), static_cast<float>(rect.bottom)}, {static_cast<float>(rect.left), static_cast<float>(rect.bottom)}}, // 아래쪽
		{{static_cast<float>(rect.left), static_cast<float>(rect.bottom)}, {static_cast<float>(rect.left), static_cast<float>(rect.top)}}  // 왼쪽
	};

	for (const auto& edge : edges)
	{
		if (IntersectRayWithLineSegment(rayStart, rayDir, edge.first, edge.second, intersection))
		{
			float distance = Vector2::Distance(rayStart, intersection);
			if (distance < closetDistance)
			{
				closetDistance = distance;
				intersectionPoint = intersection;
				hasIntersection = true;
			}
		}
	}

	return hasIntersection;
}

bool Player::IntersectRayWithLineSegment(const Vector2& rayStart, const Vector2& rayDir, const Vector2& lineStart, const Vector2& lineEnd, Vector2& intersection)
{
	float r_px = rayStart.x;
	float r_py = rayStart.y;
	float r_dx = rayDir.x;
	float r_dy = rayDir.y;

	float s_px = lineStart.x;
	float s_py = lineStart.y;
	float s_dx = lineEnd.x - lineStart.x;
	float s_dy = lineEnd.y - lineStart.y;

	// t2는 선분의 시작점부터 교차점까지의 상대적인 위치를 나타내는 값
	// t2의 범위가 0~1 사이에 있어야 교차점이 선분의 범위 내에 있는 것을 의미
	float t2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);

	// t1은 Ray의 시작점에서 교차점까지의 상대적인 위치를 나타내는 값.
	// t1이 0이상이면 Ray의 시작점으로부터 앞으로 나아간 방향에서 교차가 발생한다는 것을 의미
	float t1 = (s_px + s_dx * t2 - r_px) / r_dx;

	if (t1 >= 0 && t2 >= 0 && t2 <= 1) {
		// 교차 지점 계산
		intersection.x = r_px + r_dx * t1;
		intersection.y = r_py + r_dy * t1;
		return true;
	}

	return false;
}


float Player::Direction(Vector2 pi, Vector2 pj, Vector2 pk)
{
	return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
}

bool Player::OnSegment(Vector2 pi, Vector2 pj, Vector2 pk)
{
	return (std::min)(pi.x, pj.x) <= pk.x && pk.x <= (std::max)(pi.x, pj.x) &&
		(std::min)(pi.y, pj.y) <= pk.y && pk.y <= (std::max)(pi.y, pj.y);
}
