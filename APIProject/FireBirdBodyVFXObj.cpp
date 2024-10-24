#include "pch.h"
#include "FireBirdBodyVFXObj.h"

#include "FireBirdBodyVFX.h"
#include "ImageManager.h"

void FireBirdBodyVFXObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"Sprite/04. Boss/00. FireBird/vfx/FireBirdVFX_BodyslapAlert.png", L"FireBirdVFX_BodyslapAlert");
	AddComponent<FireBirdBodyVFX>();
}
