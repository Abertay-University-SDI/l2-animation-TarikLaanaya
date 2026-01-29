#pragma once

#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player : public GameObject
{
public:

	Player();
	virtual ~Player() = default;

	void handleInput(float dt);
	void update(float dt);

private:
	Animation m_walkDown;
	Animation* m_currentAnim = nullptr;

	float frameSpeed = 1.f / 6.f;
};

