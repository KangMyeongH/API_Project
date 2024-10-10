#pragma once
#include "Behaviour.h"

class MonoBehaviour : public Behaviour
{
public:
	explicit MonoBehaviour(GameObject* owner) : Behaviour(owner) {}
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
	virtual void OnCollisionEnter(Collision* other) {}
	virtual void OnCollisionStay(Collision* other) {}
	virtual void OnCollisionExit(Collision* other) {}
};

