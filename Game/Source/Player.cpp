#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "SpaceGame.h"

#include <iostream>


void Player::Update(float dt)
{
	//movement
	Vector2 direction{ 0,0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.y = -1;
			if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.y = 1;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_sped;
	
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire
	m_fireTimer -= dt;
	if (g_engine.GetInput().getMouseButtonDown(0) && m_fireTimer <= 0) {
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) {// && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
		m_fireTimer = .2f * m_fireModifier;

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5,0 });
		points.push_back(Vector2{ -5,-5 });
		points.push_back(Vector2{ -5,5 });
		points.push_back(Vector2{ 5,0 });

		Model* model = new Model{ points, Color(1,0,1,0) };
		Transform transform{m_transform.position,angle,1.0f };

		

		Bullet* bullet = new Bullet{ 400,transform,model };
		bullet->SetLifespan(1);
		bullet->SetTag("Player");
		m_scene->AddActor(bullet);
		
	}


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
		//dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
	
}
