#pragma once
#include "MonoBehaviour.h"

class ScrollBG : public MonoBehaviour
{
public:
	explicit ScrollBG(GameObject* owner)
	: MonoBehaviour(owner), mLinkBG{ nullptr,nullptr }, mSpeed(0), mWidth(0) {}

	void Init(Transform* bg1, Transform* bg2, float speed);

	void Awake() override;
	void Start() override;
	void LateUpdate() override;


private:
	Transform* 		mLinkBG[2];
	float 			mSpeed;
	float			mWidth;
};