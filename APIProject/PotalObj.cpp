#include "pch.h"
#include "PotalObj.h"

#include "BoxCollider.h"
#include "Potal.h"

void PotalObj::Init()
{
	AddComponent<BoxCollider>();
	AddComponent<Potal>();
}
