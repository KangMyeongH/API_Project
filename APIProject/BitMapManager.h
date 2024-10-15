#pragma once
#include <map>

class Bitmap;
class BitMapManager
{
private:
	BitMapManager();
	~BitMapManager();
public:
	BitMapManager(const BitMapManager&) = delete;
	BitMapManager(BitMapManager&&) = delete;
	BitMapManager& operator=(const BitMapManager&) = delete;
	BitMapManager& operator=(BitMapManager&&) = delete;

	static BitMapManager& GetInstance() { static BitMapManager sMgr; return sMgr; }

public:
	void InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC  FindImage(const TCHAR* pImgKey);
	void Release();

private:
	std::map<const TCHAR*, Bitmap*> m_mapBit;
};

