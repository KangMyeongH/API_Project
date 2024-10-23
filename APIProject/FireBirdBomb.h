#pragma once
#include <unordered_map>

#include "MonoBehaviour.h"
class FireBirdBomb final : public MonoBehaviour
{
public:
	FireBirdBomb(GameObject* owner) : MonoBehaviour(owner), mIsBoom(false), mIsFire(false)
	{
	}

	~FireBirdBomb() override;

	void Awake() override;
	void Start() override;
	void Update() override;
	void OnCollisionEnter(Collision other) override;

	void Pending();
	void Fire(Vector2 position);
	void Boom();

	AnimationInfo* FindAniInfo(const TCHAR* key);

private:
	std::unordered_map<const TCHAR*, AnimationInfo*> mAnimationMap;
	bool mIsBoom;
	bool mIsFire;
};

