#include "pch.h"
#include "BitMapManager.h"

#include "Bitmap.h"

BitMapManager::BitMapManager() = default;

BitMapManager::~BitMapManager()
{
	Release();
}

void BitMapManager::InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		Bitmap* pBmp = new Bitmap;

		pBmp->LoadBmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

HDC BitMapManager::FindImage(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end()) return nullptr;

	return iter->second->GetMemDC();
}

void BitMapManager::Release()
{
	for (auto& obj : m_mapBit)
	{
		delete obj.second;
	}
	m_mapBit.clear();
}
