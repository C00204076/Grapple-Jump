//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Ground.h"

//
Ground::Ground(sf::Texture & texture) :
	m_texture(texture)
{
	// Y = 850 for at home work
	m_position = sf::Vector2f(0, 1400);
	scaleX = 50;
	scaleY = 1;


	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(scaleX, scaleY);

}

//
Ground::~Ground()
{

}

//
void Ground::update(sf::Time deltaTime)
{

}

//
void Ground::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//
void Ground::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//
sf::Sprite Ground::getSprite()
{
	return m_sprite;
}
