#pragma once

class GameObjectManager;
class Scene
{
public:
	Scene() 						= default;
	virtual ~Scene() 				= default;
	Scene(const Scene&) 			= delete;
	Scene(Scene&&) 					= delete;
	Scene& operator=(const Scene&) 	= delete;
	Scene& operator=(Scene&&) 		= delete;

	virtual void	Init() 			= 0;

protected:
	GameObjectList 			mGameObjects;
};