#pragma once
#include <unordered_map>
class Image;

class ImageManager
{
private:
	ImageManager();
	~ImageManager();
public:
	ImageManager(const ImageManager&) = delete;
	ImageManager(ImageManager&&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	ImageManager& operator=(ImageManager&&) = delete;

	static ImageManager& GetInstance() { static ImageManager sMgr; return sMgr; }

public:
	void InsertBmp(const wchar_t* pFilePath, const TCHAR* pImgKey);
	ID2D1Bitmap* FindImage(const TCHAR* pImgKey);
	void Release();


private:
	std::unordered_map<const TCHAR*, Image*> mImageMap;
};