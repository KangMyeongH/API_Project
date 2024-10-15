#pragma once
#include <vector>

class Animator;

class AnimatorManager
{
private:
	AnimatorManager() = default;
	~AnimatorManager();
public:
	AnimatorManager(const AnimatorManager&) = delete;
	AnimatorManager(AnimatorManager&&) = delete;
	AnimatorManager& operator=(const AnimatorManager&) = delete;
	AnimatorManager& operator=(AnimatorManager&&) = delete;

public:
	static AnimatorManager& GetInstance() { static AnimatorManager sMgr; return sMgr; }

	void RegisterForUpdate();

	void ClearDestroyAnimatorQueue();

	void AddAnimator(Animator* animator);

	void RemoveAnimator(Animator* animator);

	void UpdateAnimator();

private:
	std::vector<Animator*> 		mAnimators;
	std::list<Animator*>		mPendingAnimatorQueue;
	std::list<Animator*>		mDestroyAnimatorQueue;
};

