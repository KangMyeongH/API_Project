#include "pch.h"
#include "Bitmap.h"

Bitmap::Bitmap() = default;

Bitmap::~Bitmap()
{
	Release();
}

void Bitmap::LoadBmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(gHwnd);

	mMemDc = CreateCompatibleDC(hDC);

	ReleaseDC(gHwnd, hDC);

	mBitmap = static_cast<HBITMAP>(LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));

	mOldBitmap = static_cast<HBITMAP>(SelectObject(mMemDc, mBitmap));
}

void Bitmap::Release()
{
	SelectObject(mMemDc, mOldBitmap);

	DeleteObject(mBitmap);

	DeleteDC(mMemDc);
}
