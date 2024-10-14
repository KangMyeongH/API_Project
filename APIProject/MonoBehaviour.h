#pragma once
#include "Behaviour.h"
#include "Collision.h"

enum UpdateType
{
	NO_UPDATE = 0,
	FIXED_UPDATE = 1 << 0,	// 001
	UPDATE = 1 << 1,		// 010
	LATE_UPDATE = 1 << 2		// 100
};

class MonoBehaviour : public Behaviour
{
public:
	explicit MonoBehaviour(GameObject* owner) : Behaviour(owner), mUpdateType(NO_UPDATE)
	{
	}

	~MonoBehaviour() override = default;

	virtual void Awake() {}
	virtual void OnEnable() {}
	virtual void Start() {}
	virtual void FixedUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void OnDestroy() {}
	virtual void OnGUI() {}
	virtual void OnDisable() {}
	virtual void OnCollisionEnter(Collision other) {}
	virtual void OnCollisionStay(Collision other) {}
	virtual void OnCollisionExit(Collision other) {}

	UpdateType GetUpdateType() const { return mUpdateType; }
	void  SetEnable(const bool enabled) final
	{
		if (mEnabled != enabled)
		{
			if (enabled) OnEnable();
			else OnDisable();

			mEnabled = enabled;
		}
	}

	void Destroy() override;

protected:
	UpdateType mUpdateType;
};