//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Ground.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="texture"></param>
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

/// <summary>
/// Default deconstructor
/// </summary>
Ground::~Ground()
{

}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void Ground::update(sf::Time deltaTime)
{

}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Ground::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
void Ground::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Sprite Ground::getSprite()
{
	return m_sprite;
}
