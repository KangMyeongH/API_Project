#include "pch.h"
#include "ImageManager.h"

#include "Image.h"

ImageManager::ImageManager() = default;

ImageManager::~ImageManager()
{
	Release();
}

void ImageManager::InsertBmp(const wchar_t* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(mImageMap.begin(), mImageMap.end(), tagFinder(pImgKey));

	if (iter == mImageMap.end())
	{
		Image* image = new Image;

		image->LoadMyImage(pFilePath);

		mImageMap.insert({ pImgKey, image });
	}
}

ID2D1Bitmap* ImageManager::FindImage(const TCHAR* pImgKey)
{
	auto iter = find_if(mImageMap.begin(), mImageMap.end(), tagFinder(pImgKey));

	if (iter == mImageMap.end()) return nullptr;

	return iter->second->GetImage();
}

void ImageManager::Release()
{
	for (auto& image : mImageMap)
	{
		delete image.second;
	}

	mImageMap.clear();
}
