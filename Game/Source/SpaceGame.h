#pragma once

class SpaceGame {
public:
	enum class eState {
		TITLE,
		START_LEVEL,
		GAME,
		PLAYER_DEAD,
		GAME_OVER,
	};
public:
	//SpaceGame(Engine* engine) : Game{ engine } {}
	bool Initialize();
	void Shutdown();
	//void Draw(Renderer& renderer);
	//void Update();

	//void OnPlayerDeath();

private:
	float m_stateTimer{ 0 };
};