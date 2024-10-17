#pragma once
#include <list>

#include "framework.h"

class GameObject;

enum { WIN_WIDTH = 1504, WIN_HEIGHT = 992 };
enum Tag
{
	UNTAGGED,
	PLAYER,
	MONSTER,
	ITEM,
	END_TAG
};

enum CollisionDirection
{
	NONE = 0,
	LEFT = 1 << 0,       // 0001
	RIGHT = 1 << 1,    // 0010
	TOP = 1 << 2,       // 0100
	BOTTOM = 1 << 3    // 1000
};

enum PlayerState
{
	IDLE,
	RUN,
	JUMP,
	CHARGEDASH
};

struct AnimationInfo
{
	AnimationInfo(ID2D1Bitmap* image, int start, int end, float width, float height, float speed, bool loop)
		: Image(image), Start(start), End(end), Width(width), Height(height), Speed(speed), Loop(loop)
	{
	}

	ID2D1Bitmap* Image;
	int Start;
	int End;
	float Width;
	float Height;
	float Speed;
	bool Loop;
};

struct tagFinder
{
public:
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool	operator()(T& MyPair)
	{
		return !lstrcmp(m_pTag, MyPair.first);
	}

private:
	const TCHAR* m_pTag;
};

#define VK_MAX			0xff

extern HWND gHwnd;
extern ID2D1Factory* gFactory;
extern ID2D1HwndRenderTarget* gRenderTarget;

using GameObjectList = std::list<GameObject*>;