#include "pch.h"
#include "MouseObj.h"

#include "BoxCollider.h"
#include "Mouse.h"

void MouseObj::Init()
{
	AddComponent<BoxCollider>();
	AddComponent<Mouse>();
}
