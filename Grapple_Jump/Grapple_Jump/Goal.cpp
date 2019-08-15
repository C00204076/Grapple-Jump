//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:39 15 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "Goal.h"

//
Goal::Goal()
{
	initialise();
}

//
Goal::~Goal()
{

}

//
void Goal::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Goal-(small).png"))
	{
		std::cout << "Error! Unable to load Goal-(small).png from game files!" << std::endl;
	}
}

//
void Goal::initialise()
{
	loadTexture();

	m_scaleX = 1;
	m_scaleY = 1;

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_scaleX, m_scaleY);
}

//
void Goal::update(sf::Time deltaTime)
{

}

//
void Goal::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//
bool Goal::playerCollision(Player * player)
{
	bool collision;

	if (m_sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
	{
		collision = true;
	}
	//
	else
	{
		collision = false;
	}

	return collision;
}

//
void Goal::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//
sf::Vector2f Goal::getPosition()
{
	return m_position;
}

//
sf::Sprite Goal::getSprite()
{
	return m_sprite;
}
