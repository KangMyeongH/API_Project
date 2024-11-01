#pragma once
#include "MonoBehaviour.h"

class ScrollBG : public MonoBehaviour
{
public:
	explicit ScrollBG(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr), mLinkBG{nullptr, nullptr}, mSpeed(0), mWidth(0)
	{
	}

	void Init(Transform* bg1, Transform* bg2, float speed);

	void Awake() override;
	void Start() override;
	void LateUpdate() override;

	// ���� ������ ����� �ʵ��� Ŭ����(����)�ϴ� �Լ�
	float Clamp(float value, float min, float max) const
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

private:
	GameObject* 	mPlayer;
	Transform* 		mLinkBG[2];
	float 			mSpeed;
	float			mWidth;
};