#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	Particle::Data date{m_transform.position,Vector2(1, 0).Rotate(randomf(Math::TwoPi)) * 50,randomf(0.5f,2.0f),255,255,255,255};
	m_velocity = Vector2{ 1,0 }.Rotate(m_transform.rotation) * m_sped;
	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
}
