#pragma once
#include "Camera.h"
#include "GameObject.h"
#include "Renderer.h"

// �Ű� ������ hdc, width, height, layer�� �޴´�
class SpriteRenderer : public Renderer
{
public:
	explicit SpriteRenderer(GameObject* owner, int layer);
	SpriteRenderer(GameObject* owner, ID2D1Bitmap* image, float width, float height, int layer);

	void Render(ID2D1DeviceContext* render) override
	{
		D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(mRenderRect);

		// ȸ�� �߽� (mRenderRect�� �߽��� �������� ȸ���Ѵٰ� ����)
		D2D1_POINT_2F center = D2D1::Point2F(
			(screenRect.left + screenRect.right) / 2.0f,
			(screenRect.top + screenRect.bottom) / 2.0f
		);

		// ���� ��ȯ ���� ����
		D2D1_MATRIX_3X2_F oldTransform;
		render->GetTransform(&oldTransform);

		D2D1_MATRIX_3X2_F scaleMatrix;

		// ������ ��ȯ ����
		if (mFlip)
		{
			scaleMatrix = Matrix3x2F::Scale(-mScale.x, mScale.y, center);
		}

		else
		{
			scaleMatrix = Matrix3x2F::Scale(mScale.x, mScale.y, center);
		}

		// ȸ�� ��ȯ ����
		D2D1_MATRIX_3X2_F rotationMatrix = Matrix3x2F::Rotation(mAngle, center);

		// ��ȯ ����
		render->SetTransform(scaleMatrix * rotationMatrix * oldTransform);

		render->DrawBitmap(
			mImage,
			screenRect,	// ȭ�鿡 �׷��� ��ǥ ����
			mOpacity,			// ����
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // ���� ���
			mTargetRect		// ���� ��������Ʈ ��Ʈ�� Ư�� ����
		);

		// ���� ��ȯ ���� ����
		render->SetTransform(oldTransform);
	}

	void 	ChangeSprite(ID2D1Bitmap* image, float width, float height, int startFrame);

	void 	SetFrame(int frame);

	void	SetAngle(float angle) { mAngle = angle; }

	void	SetScale(float scale) { mScale *= scale; }

	void	SetXScale(float scale) { mScale.x *= scale; }

	void	SetYScale(float scale) { mScale.y *= scale; }

	void	SetOpacity(float opacity) { mOpacity = opacity; }

	void	SetOffset(const Vector2& offset) { mOffset = offset; }

	void	SetParallaxFactor(const Vector2& vel) { mParallaxFactor = vel; }

	D2D1_RECT_F GetRenderRect() const { return mRenderRect; }

	D2D1_RECT_F GetTargetRect() const { return mTargetRect; }

	float	GetWidth() const { return mWidth; }

	void 	Flip(bool flip)	{mFlip = flip;}

	bool	GetFlip() const { return mFlip; }

	void 	Destroy() override;

	void	IsPivotDown(const bool down) { mPivotDown = down; }

	ID2D1Bitmap* GetBitmap() const { return mImage; }

private:
	Transform* 		mTransform;
	ID2D1Bitmap* 	mImage;
	D2D1_RECT_F		mTargetRect;	// ��������Ʈ ��Ʈ�� Ư�� ����
	D2D1_RECT_F		mRenderRect;	// ȭ���� �׷��� ��ġ
	Vector2			mParallaxFactor; // �з����� ����, �⺻���� 1.0 ������ �ְ� ũ�� ������
	Vector2			mOffset;
	Vector2			mScale;
	float			mAngle;
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	int				mFrame;
	//int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

