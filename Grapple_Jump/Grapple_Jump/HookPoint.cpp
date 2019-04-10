//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:50 21 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "HookPoint.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="texture"></param>
HookPoint::HookPoint(sf::Texture & texture) :
	m_texture(texture)
{
	// Y = 50 for at home work
	//m_position = sf::Vector2f(700, 600);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3f, 0.3f);
}

/// <summary>
/// Default deconstructor
/// </summary>
HookPoint::~HookPoint()
{

}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void HookPoint::update(sf::Time deltaTime)
{

}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void HookPoint::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
void HookPoint::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Sprite HookPoint::getSprite()
{
	return m_sprite;
}