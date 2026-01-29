#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	if (!m_playerTex.loadFromFile("gfx/sheep_sheet.png"))
	{
		std::cerr << "Could Not Find The Sheep Sheet File!";
	}
	else
	{
		m_player.setInput(&in);
		m_player.setWindow(&hwnd);
		m_player.setTexture(&m_playerTex);
		m_player.setTextureRect(sf::IntRect({ 0,0 }, { 64,64 }));
		m_player.setSize({ 64, 64 });
		m_player.setPosition({ 0, 0 });
	}
}

// handle user input
void Level::handleInput(float dt)
{
	m_player.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	m_player.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

