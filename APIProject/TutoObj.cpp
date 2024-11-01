#include "pch.h"
#include "TutoObj.h"

#include "BoxCollider.h"
#include "ImageManager.h"
#include "Tuto.h"

void TutoObj::Init()
{
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_Move.png", L"Tuto_Move");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_Jump.png", L"Tuto_Jump");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_Climb.png", L"Tuto_Climb");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_ClimbJump.png", L"Tuto_ClimbJump");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_Swing.png", L"Tuto_Swing");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_SwingDash.png", L"Tuto_SwingDash");
	ImageManager::GetInstance().InsertBmp(L"./Sprite/Tuto_SwingRush.png", L"Tuto_SwingRush");


	AddComponent<BoxCollider>();
	AddComponent<Tuto>();
	AddComponent<SpriteRenderer>(6);
	AddComponent<Animator>()->SetSprite(GetComponent<SpriteRenderer>());
}
