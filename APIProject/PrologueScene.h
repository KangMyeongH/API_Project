#pragma once
#include "Scene.h"
class PrologueScene : public Scene
{
public:
	void Init() override;

	void InsertLinePlatform(const Vector2& start, const Vector2& end, bool grab);
};

