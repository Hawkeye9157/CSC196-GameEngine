#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player) {
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_sped * dt;
		m_transform.rotation = direction.Angle();
	}
	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player" || actor->GetTag() == "PlayerBullet") {
		//m_scene->GetGame()->AddPoints(100);
		m_destroyed = true;

		for (int i = 0; i < 100; i++) {
			Particle::Data data{ m_transform.position,Vector2(1, 0).Rotate(randomf(Math::TwoPi)) * 50,randomf(0.5f,2.0f),255,255,255,255 };
			g_engine.GetPS().AddParticle(data);
		}
	}
}