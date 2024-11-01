#pragma once
#include <string>

#include "Camera.h"
#include "Renderer.h"
#include "Transform.h"

// 매개변수로 int layer, vector offset, vector scale, ColorF color, wchar text, wchar font, float fontSize를 받는다. 
class TextRenderer : public Renderer
{
public:
	TextRenderer(GameObject* owner, int layer)
		: Renderer(owner, layer), mIndex(0), mColor(1.f, 1.f, 1.f, 1.f), mText{}, mFont{}, mOpacity(0), mFontSize(0),
		  mCenter(false)
	{
	}

	TextRenderer(GameObject* owner, int layer, const Vector2& offset, const Vector2& scale, const ColorF& color, WCHAR const* text, WCHAR const* font, const float fontSize):
		Renderer(owner, layer), mOffset(offset), mScale(scale), mIndex(0),
		mColor(color), mText{}, mFont{}, mOpacity(1.f), mFontSize(fontSize), mCenter(false)
	{
		swprintf_s(mText, 32, text);
		swprintf_s(mFont, 64, font);
	}

	void Render(ID2D1DeviceContext* render) override
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
			mFontSize * Camera::GetInstance().GetZoom(),
			L"ko-kr",
			&textFormat
		);

		if (mCenter)
		{
			// 수평, 수직 가운데 정렬 설정
			textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}

		render->CreateSolidColorBrush(mColor, &brush);

		D2D1_RECT_F rect = {
			GetTransform()->GetWorldPosition().x - mScale.x * 0.5f + mOffset.x,
			GetTransform()->GetWorldPosition().y - mScale.y * 0.5f + mOffset.y,
			GetTransform()->GetWorldPosition().x + mScale.x * 0.5f + mOffset.x,
			GetTransform()->GetWorldPosition().y + mScale.y * 0.5f + mOffset.y
		};

		D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(rect);

		// 텍스트를 그리기
		render->DrawText(
			mText,
			wcslen(mText) - mIndex,
			textFormat,
			screenRect,
			brush
		);

		textFormat->Release();
	}

	void SetOffset(const Vector2& offset) { mOffset = offset; }
	void SetScale(const Vector2& scale) { mScale = scale; }
	void SetColor(const ColorF& color) { mColor = color; }
	void SetText(WCHAR const* text) { swprintf_s(mFont, 32, text); }
	void SetFont(WCHAR const* font) { swprintf_s(mFont, 64, font); }
	void SetOpacity(const float opacity) { mOpacity = opacity; }
	void SetFontSize(const float size) { mFontSize = size; }
	void SetIndex(const size_t index) { mIndex = index; }
	void SetCenter(const bool center) { mCenter = center; }

private:
	Vector2 mOffset;
	Vector2 mScale;
	size_t mIndex;
	ColorF mColor;
	wchar_t mText[32];
	wchar_t mFont[64];
	float mOpacity;
	float mFontSize;
	bool mCenter;
};

