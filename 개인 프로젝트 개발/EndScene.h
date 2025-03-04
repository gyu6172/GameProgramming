#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Number.h"

class EndScene :
	public Scene
{
public:
	EndScene(int score);
	~EndScene();

	int score;
	Sprite* background;
	Sprite* gameoverTitle;
	Sprite* startButton;
	Number scoreArray[3];

	void Render();
	void Update(float dTime);

	D3DXVECTOR2 Lerp(D3DXVECTOR2 p1, D3DXVECTOR2 p2, float power);
};

