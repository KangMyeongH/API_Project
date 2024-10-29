#pragma once
#include "MonoBehaviour.h"
class Enemy : public MonoBehaviour
{
public:
	Enemy(GameObject* owner, EnemyType type) : MonoBehaviour(owner), mType(type), mIsFront(false), mIsBack(false),
	                                           mIsNeu(false),
	                                           mIsExc(false),
	                                           mIsKnockBack(false)
	{
	}

	~Enemy() override = default;

	EnemyType GetType() const { return mType; }

	void SetFront()
	{
		mIsFront = true;
		mIsBack = false;
		mIsNeu = false;
	}
	void SetBack()
	{
		mIsFront = false;
		mIsBack = true;
		mIsNeu = false;
	}
	void SetNeu()
	{
		mIsFront = false;
		mIsBack = false;
		mIsNeu = true;
	}
	void SetKnockBack(const bool front) { mIsFront = front; }

	bool GetFront() const { return mIsFront; }
	bool GetBack() const { return mIsFront; }
	bool GetNeu() const { return mIsFront; }
	bool GetKnockBack() const { return mIsFront; }

protected:
	EnemyType	mType;
	bool		mIsFront;
	bool		mIsBack;
	bool		mIsNeu;
	bool		mIsExc;
	bool		mIsKnockBack;
};

