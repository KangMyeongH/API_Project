#pragma once

class Image
{
public:
	Image();
	~Image();

	void		LoadMyImage(const wchar_t* filepath);
	ID2D1Bitmap* GetImage() const { return mImage; }

private:
	ID2D1Bitmap* mImage;
};

