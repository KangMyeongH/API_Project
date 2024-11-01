#pragma once
#include "MonoBehaviour.h"
class PrologueCloud final : public MonoBehaviour
{
public:
	explicit PrologueCloud(GameObject* owner)
		: MonoBehaviour(owner), mPlayer(nullptr)
	{
	}

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
	GameObject* mPlayer;
};

