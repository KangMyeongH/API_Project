#pragma once
#include "MonoBehaviour.h"
class Bubble final : public MonoBehaviour
{
public:
	explicit Bubble(GameObject* owner)
		: MonoBehaviour(owner), mLeft(nullptr), mRight(nullptr), mText{}, mTextLength(0), mColor(0, 0, 0, 1.f),
		  mTimeScale(1.f),
		  mCurrentTime(0)
	{
	}

	void Awake() override;
	void Start() override;
	void Update() override;

	void InitText(const wchar_t* text)
	{
		wcsncpy_s(mText, text, sizeof(mText) / sizeof(wchar_t) - 1); // 안전하게 문자열 복사
		mText[sizeof(mText) / sizeof(wchar_t) - 1] = L'\0'; // 널 문자 추가
		mTextLength = wcslen(mText); // 문자열 길이 저장
	}

	void SetTimeScale(float scale) { mTimeScale = scale; }

private:
	GameObject* mLeft;
	GameObject* mRight;
	wchar_t 	mText[32];
	int 		mTextLength;
	ColorF		mColor;
	Vector2		mOffset;
	Vector2		mScale;
	float		mTimeScale;
	float		mCurrentTime;
};

