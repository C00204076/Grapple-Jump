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

	m_scaleX = 1;
	m_scaleY = 1;

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_scaleX, m_scaleY);
}

//
void Start::update(sf::Time deltaTime)
{

}

//
void Start::render(sf::RenderWindow& window)
{
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