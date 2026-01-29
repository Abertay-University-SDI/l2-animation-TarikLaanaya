#include "Player.h"

Player::Player()
{
	m_walkDown.addFrame(sf::IntRect({ 64,0 }, { 64,64 }));
	m_walkDown.addFrame(sf::IntRect({ 0,0 }, { 64,64 }));

	m_walkDown.setFrameSpeed(frameSpeed); // 1 sixth of a frame
	m_currentAnim = &m_walkDown;
}

void Player::handleInput(float dt)
{

}

void Player::update(float dt)
{
	m_walkDown.animate(dt);
	setTextureRect(m_walkDown.getCurrentFrame());
}