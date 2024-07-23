#pragma once
#include "Engine.h"

class Game {
public:
	Game() = default;
	//Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual void ShutDown() = 0;

	virtual void Update(float dt);
	virtual void Draw();
};