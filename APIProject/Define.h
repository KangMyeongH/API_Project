#pragma once
#include <list>

#include "framework.h"

class GameObject;

enum { WIN_WIDTH = 1920, WIN_HEIGHT = 1080 };
enum Tag
{
	UNTAGGED,
	PLAYER,
	ENEMY,
	BOSS,
	PLATFORM,
	BULLET,
	ITEM,
	END_TAG
};

enum CHANNELID
{
	SOUND_EFFECT,
	SOUND_PLAYER,
	SOUND_PLAYER_EFFECT,
	SOUND_BUTTON_EFFECT,
	SOUND_BOSS,
	SOUND_BOSS_EFFECT,
	SOUND_BGM,
	SOUND_INTRO_BGM,
	SOUND_TEXT,
	MAXCHANNEL
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
	CLIMBING,
	CHARGEDASH,
	CHARGEATTACK,
	SWING,
	SWINGJUMP,
	EXC,
	EXCDASH,
	EXCATTACK,
	CEILING
};

enum EnemyType
{
	EXC_GROUND,
	EXC_FLY,
	EXC_STATIC,
	NORMAL
};

enum PlatformType
{
	RECT_PLATFORM,
	LINE_PLATFORM
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

extern float gBGMVolume;
extern float gEffectVolume;
extern HWND gHwnd;
extern ID2D1Factory1* gFactory;
//extern ID2D1HwndRenderTarget* gRenderTarget;
extern IDWriteFactory* gWriteFactory;

extern IWICImagingFactory2* gWICFactory;
extern ID2D1Device* gDevice;
extern ID2D1DeviceContext* gDeviceContext;
extern IDXGISwapChain* gSwapChain;

using GameObjectList = std::list<GameObject*>;