#pragma once
#include "MonoBehaviour.h"
class PRLG final : public MonoBehaviour
{
public:
	explicit PRLG(GameObject* owner)
		: MonoBehaviour(owner), mCurrentTime(0), mIndex(0), mKeyDown(false)
	{
	}

	void Awake() override;

	void Update() override;

	void Scene01();
	void InsertLinePlatform(const Vector2& start, const Vector2& end, bool grab);

	void OnCollisionEnter(Collision other) override;

private:
	float mCurrentTime;
	int mIndex;
	bool mKeyDown;
};

