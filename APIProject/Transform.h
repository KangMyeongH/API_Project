#pragma once
class GameObject;
class Transform
{
public:
	Transform() : mOwner(nullptr), mPosition(0, 0), mScale(1, 1) {}

	void Init(GameObject* owner);
	void Update();

	Vector2& Position() { return mPosition; }
	Vector2& Scale() { return mScale; }

private:
	GameObject* 	mOwner;
	Vector2 		mPosition;
	Vector2 		mScale;
};