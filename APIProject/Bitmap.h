#pragma once
class Bitmap
{
public:
	Bitmap();
	~Bitmap();

	HDC		GetMemDC() { return mMemDc; }

	void	LoadBmp(const TCHAR* pFilePath);
	void	Release();

private:
	HDC		mMemDc;

	HBITMAP mBitmap;
	HBITMAP mOldBitmap;
};

