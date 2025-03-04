#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include "Number.h"
#include "Player.h"
#include "Background.h"
#include <list>

class GameScene :
	public Scene
{
private:

	int score;
	bool backgroundInstatics;

	std::list<Background*> backgroundList;
	std::list<Sprite*> bridgeList;
	std::list<Sprite*> obstacleList;
	std::list<Sprite*> coinList;

	Number numArray[4];
	Player* player;

public:
	GameScene();
	~GameScene();

	void Render();
	void Update(float dTime);


};

