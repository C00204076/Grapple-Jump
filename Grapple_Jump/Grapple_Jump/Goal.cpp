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

	//
	m_alpha = 255;
	//
	m_flashOut = true;
	m_flashIn = false;
	//
	m_moveUp = false;
	m_moveDown = true;

	m_scaleX = 1;
	m_scaleY = 1;

	m_sprite.setOrigin(37.5, 37.5);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_scaleX, m_scaleY);
	//
	m_goalY = m_sprite.getPosition().y;
}

//
void Goal::update(sf::Time deltaTime)
{
	//juiciness();
}

//
void Goal::juiciness()
{
	//
	if (m_goalY >= m_sprite.getPosition().y + 10)
	{
		m_moveUp = true;
		m_moveDown = false;
	}
	else if (m_goalY <= m_sprite.getPosition().y - 10)
	{
		m_moveUp = false;
		m_moveDown = true;
	}

	//
	if (m_moveUp == true)
	{
		m_goalY -= 0.5;
	}

	if (m_moveDown == true)
	{
		m_goalY += 0.5;
	}

	//
	if (m_alpha >= 215)
	{
		m_flashOut = true;
		m_flashIn = false;
	}
	else if (m_alpha <= 40)
	{
		m_flashOut = false;
		m_flashIn = true;
	}

	//
	if (m_flashIn == true)
	{
		m_alpha += 2;
	}
	//
	if (m_flashOut == true)
	{
		m_alpha -= 2;
	}

	//
	m_sprite.setPosition(m_sprite.getPosition().x, m_goalY);
	//
	m_sprite.setColor(sf::Color(255, 255, 255, m_alpha));
}

//
void Goal::render(sf::RenderWindow& window, sf::Vector2f scale)
{
	//
	m_sprite.setScale(scale);
	//
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
