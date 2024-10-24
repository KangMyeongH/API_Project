#pragma once
#include "Renderer.h"
#include "Transform.h"

// 매개변수로 int layer, vector offset, vector scale, ColorF color, wchar text, wchar font, float fontSize를 받는다. 
class TextRenderer : public Renderer
{
public:
	TextRenderer(GameObject* owner, int layer)
		: Renderer(owner, layer), mColor(1.f,1.f,1.f,1.f), mText{}, mFont{}, mOpacity(0), mFontSize(0) {}

	TextRenderer(GameObject* owner, int layer, const Vector2& offset, const Vector2& scale, ColorF color, WCHAR const* text, WCHAR const* font, float fontSize):
		Renderer(owner, layer), mOffset(offset), mScale(scale),
		mColor(color), mText{}, mFont{}, mOpacity(1.f), mFontSize(fontSize)
	{
		swprintf_s(mText, 32, text);
		swprintf_s(mFont, 64, font);
	}

	void Render(ID2D1HwndRenderTarget* render) override
	{
		mColor.a = mOpacity;
		// 텍스트 서식 설정
		IDWriteTextFormat* textFormat = nullptr;
		ID2D1SolidColorBrush* brush = nullptr;

		gWriteFactory->CreateTextFormat(
			mFont,
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			mFontSize,
			L"ko-kr",
			&textFormat
		);

		render->CreateSolidColorBrush(mColor, &brush);

		D2D1_RECT_F rect = {
			GetTransform()->GetWorldPosition().x - mScale.x * 0.5f + mOffset.x,
			GetTransform()->GetWorldPosition().y - mScale.y * 0.5f + mOffset.y,
			GetTransform()->GetWorldPosition().x + mScale.x * 0.5f + mOffset.x,
			GetTransform()->GetWorldPosition().y + mScale.y * 0.5f + mOffset.y
		};

		// 텍스트를 그리기
		render->DrawText(
			mText,
			wcslen(mText),
			textFormat,
			rect,
			brush
		);

		textFormat->Release();
	}

	void SetOffset(const Vector2& offset) { mOffset = offset; }
	void SetScale(const Vector2& scale) { mScale = scale; }
	void SetColor(ColorF color) { mColor = color; }
	void SetText(WCHAR const* text) { swprintf_s(mFont, 32, text); }
	void SetFont(WCHAR const* font) { swprintf_s(mFont, 64, font); }
	void SetOpacity(float opacity) { mOpacity = opacity; }
	void SetFontSize(float size) { mFontSize = size; }


private:
	Vector2 mOffset;
	Vector2 mScale;
	ColorF mColor;
	wchar_t mText[32];
	wchar_t mFont[64];
	float mOpacity;
	float mFontSize;
};

