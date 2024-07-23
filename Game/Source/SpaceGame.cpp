#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"


bool SpaceGame::Initialize() {
	//m_scene = new Scene(this);
	//m_font = new Font();
	//m_font->("narrative.ttf", 20);

	//m_textScore = new Text(m_font);
	//m_textLives = new Text(m_font);
	//m_textTitles = new Text(m_font);


	return true;
}

// add to eState::Game
// new enemy(400, transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetWidth())
//crete pickup


//case eState::PLAYER_DEAD:
// m_stateTimer -= dt;
// if (m_stateTimer <= 0) {
	//m_state = eState::START_LEVEL
//}
//break;


//void SpaceGame::OnPlayerDeath() {
//
//m_lives--;
//m_state = (lives == 0) ? eState::GAME_OVER : eState::PLAYER_DEAD;
// m_statetimer = 3;
//}