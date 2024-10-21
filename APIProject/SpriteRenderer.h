#pragma once
#include "Behaviour.h"
#include "Camera.h"
#include "GameObject.h"

// �Ű� ������ hdc, width, height, layer�� �޴´�
class SpriteRenderer : public Behaviour
{
public:
	explicit SpriteRenderer(GameObject* owner, int layer);
	SpriteRenderer(GameObject* owner, ID2D1Bitmap* image, float width, float height, int layer);

	void Render(ID2D1HwndRenderTarget* render) const
	{
		D2D1_RECT_F screenRect = Camera::GetInstance().WorldToScreen(mRenderRect);

		/*
		// ī�޶��� �����ӿ� ���� ��� ��ġ�� ����
		screenRect.left += (Camera::GetInstance().GetPosition().x * mParallaxFactor.x);
		screenRect.right += (Camera::GetInstance().GetPosition().x * mParallaxFactor.x);
		screenRect.top += (Camera::GetInstance().GetPosition().y * mParallaxFactor.y);
		screenRect.bottom += (Camera::GetInstance().GetPosition().y * mParallaxFactor.y);
		*/
		// ȸ�� �߽� (mRenderRect�� �߽��� �������� ȸ���Ѵٰ� ����)
		D2D1_POINT_2F center = D2D1::Point2F(
			(screenRect.left + screenRect.right) / 2.0f,
			(screenRect.top + screenRect.bottom) / 2.0f
		);

		// ���� ��ȯ ���� ����
		D2D1_MATRIX_3X2_F oldTransform;
		render->GetTransform(&oldTransform);

		// ������ ��ȯ ����
		D2D1_MATRIX_3X2_F scaleMatrix = Matrix3x2F::Scale(mScale, mScale, center);

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

	void	SetScale(float scale) { mScale = scale; }

	void	SetParallaxFactor(const Vector2& vel) { mParallaxFactor = vel; }

	int		GetLayer() const { return mLayer; }

	float	GetWidth() const { return mWidth; }

	void 	Flip(bool flip) { mFlip = flip; }

	void 	Destroy() override;

	void	IsPivotDown(const bool down) { mPivotDown = down; }

	ID2D1Bitmap* GetBitmap() const { return mImage; }

private:
	Transform* 		mTransform;
	ID2D1Bitmap* 	mImage;
	D2D1_RECT_F		mTargetRect;	// ��������Ʈ ��Ʈ�� Ư�� ����
	D2D1_RECT_F		mRenderRect;	// ȭ���� �׷��� ��ġ
	Vector2			mParallaxFactor; // �з����� ����, �⺻���� 1.0 ������ �ְ� ũ�� ������
	float			mAngle;
	float			mOpacity;
	float 			mWidth;
	float 			mHeight;
	float			mScale;
	int				mFrame;
	int				mLayer;
	bool			mFlip;
	bool			mPivotDown;
};

