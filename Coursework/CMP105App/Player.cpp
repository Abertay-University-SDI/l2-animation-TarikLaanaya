#include "Player.h"
#include <iostream>

Player::Player()
{
	// --- Animations --- //
	
	// Walk Down //
	for (int i = 0; i < 2; i++)
	{
		m_walkDown.addFrame(sf::IntRect({ i * playerSize, 0 }, { playerSize, playerSize }));
	}

	m_walkDown.setFrameSpeed(frameSpeed);
	m_walkDown.setLooping(true);

	// Walk Up //
	for (int i = 4; i < 8; i++)
	{
		m_up.addFrame(sf::IntRect({ i * playerSize, 0 }, { playerSize, playerSize }));
	}
	
	m_up.setFrameSpeed(frameSpeed);
	m_up.setLooping(true);

	// Up Right //
	for (int i = 0; i < 4; i++)
	{
		m_upRight.addFrame(sf::IntRect({ i * playerSize, playerSize }, { playerSize, playerSize }));
	}

	m_upRight.setFrameSpeed(frameSpeed);
	m_upRight.setLooping(true);

	// Right //
	for (int i = 4; i < 8; i++)
	{
		m_right.addFrame(sf::IntRect({ i * playerSize, playerSize }, { playerSize, playerSize }));
	}

	m_right.setFrameSpeed(frameSpeed);
	m_right.setLooping(true);

	// Down Right //
	for (int i = 0; i < 4; i++)
	{
		m_downRight.addFrame(sf::IntRect({ i * playerSize, playerSize * 2 }, { playerSize, playerSize }));
	}

	m_downRight.setFrameSpeed(frameSpeed);
	m_downRight.setLooping(true);

	m_currentAnim = &m_walkDown;
}

void Player::handleInput(float dt)
{
	if (m_gameOver) return;

	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}

	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir)
		m_inputBuffer = INPUT_BUFFER_LENGTH;
}

void Player::update(float dt)
{
	// --- Game Over Logic --- //

	if (m_gameOver) return;

	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		move({ 0, -orthog_speed });
		m_up.animate(dt);
		setTextureRect(m_up.getCurrentFrame());
		break;
	case Direction::UP_RIGHT:
		move({ diagonal_speed, -diagonal_speed });
		m_upRight.animate(dt);
		setTextureRect(m_upRight.getCurrentFrame());
		m_upRight.setFlipped(false);
		break;
	case Direction::RIGHT:
		move({ orthog_speed,0 });
		m_right.animate(dt);
		setTextureRect(m_right.getCurrentFrame());
		m_right.setFlipped(false);
		break;
	case Direction::DOWN_RIGHT:
		move({ diagonal_speed, diagonal_speed });
		m_downRight.animate(dt);
		setTextureRect(m_downRight.getCurrentFrame());
		m_downRight.setFlipped(false);
		break;
	case Direction::DOWN:
		move({ 0, orthog_speed });
		m_walkDown.animate(dt);
		setTextureRect(m_walkDown.getCurrentFrame());
		break;
	case Direction::DOWN_LEFT:
		move({ -diagonal_speed, diagonal_speed });
		m_downRight.animate(dt);
		setTextureRect(m_downRight.getCurrentFrame());
		m_downRight.setFlipped(true);
		break;
	case Direction::LEFT:
		move({ -orthog_speed,0 });
		m_right.animate(dt);
		setTextureRect(m_right.getCurrentFrame());
		m_right.setFlipped(true);
		break;
	case Direction::UP_LEFT:
		move({ -diagonal_speed, -diagonal_speed });
		m_upRight.animate(dt);
		setTextureRect(m_upRight.getCurrentFrame());
		m_upRight.setFlipped(true);
		break;
	}

	// check wall collision
	sf::Vector2f pos = getPosition();
	float radius = playerSize / 2;

	if (pos.x < 0 || pos.x + radius > m_window->getSize().x || pos.y < 0 || pos.y + radius > m_window->getSize().y)
	{
		m_gameOver = true;
		std::cout << "Game over";
	}
}