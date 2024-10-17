#pragma once
#include "MonoBehaviour.h"
class Platform : public MonoBehaviour
{
public:
	Platform(GameObject* owner) : MonoBehaviour(owner) {}



protected:
	bool mIsHit;

};