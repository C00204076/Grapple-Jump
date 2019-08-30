//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:15 15 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "Start.h"

//
Start::Start()
{
	initialise();
}

//
Start::~Start()
{

}

//
void Start::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Start-(small).png"))
	{
		std::cout << "Error! Unable to load Start-(small).png from game files!" << std::endl;
	}
}

//
void Start::initialise()
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
	m_startY = m_sprite.getPosition().y;
}

//
void Start::update(sf::Time deltaTime)
{
	//juiciness();
}

//
void Start::juiciness()
{
	//
	if (m_startY >= m_sprite.getPosition().y + 10)
	{
		m_moveUp = true;
		m_moveDown = false;
	}
	else if (m_startY <= m_sprite.getPosition().y - 10)
	{
		m_moveUp = false;
		m_moveDown = true;
	}

	//
	if (m_moveUp == true)
	{
		m_startY -= 0.5;
	}

	if (m_moveDown == true)
	{
		m_startY += 0.5;
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
	m_sprite.setPosition(m_sprite.getPosition().x, m_startY);
	//
	m_sprite.setColor(sf::Color(255, 255, 255, m_alpha));
}

//
void Start::render(sf::RenderWindow& window, sf::Vector2f scale)
{
	//
	m_sprite.setScale(scale);
	//
	window.draw(m_sprite);
}

//
bool Start::playerCollision(Player * player)
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
void Start::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//
sf::Vector2f Start::getPosition()
{
	return m_position;
}

//
sf::Sprite Start::getSprite()
{
	return m_sprite;
}