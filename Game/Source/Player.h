#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) : Actor{ transform,model } {}
	Player(float speed, const Transform& transform, Model* model) : Actor{ transform,model }, m_sped{speed} {}

	void Update(float dt);

private:
	float m_sped = 0;
};