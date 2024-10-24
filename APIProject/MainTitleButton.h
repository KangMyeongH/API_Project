#pragma once
#include "MonoBehaviour.h"

enum TitleButtonType
{
	GAME_START,
	SPEED_RUN,
	SETTING,
	END_GAME
};
class MainTitleButton : public MonoBehaviour
{
public:
	explicit MainTitleButton(GameObject* owner) : MonoBehaviour(owner), mType(),
	                                              mColor(0.f, 0.9725f, 1.f, 0.f), mArray{},
	                                              mOpacity(0), mCurrentTime(0), mSelected(false)
	{
	}

	void Awake() override;
	void Start() override;
	void Update() override;
	void OnCollisionEnter(Collision other) override;
	void OnCollisionExit(Collision other) override;
	void SetButton(TitleButtonType type) { mType = type; }

private:
	TitleButtonType mType;
	ColorF mColor;
	wchar_t mArray[32];
	float mOpacity;
	float mCurrentTime;
	bool mSelected;
};
