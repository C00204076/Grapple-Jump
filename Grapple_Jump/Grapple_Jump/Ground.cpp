// Sets the methods, functions and changes of the variables related to Ground header file
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 30 minutes
// Known Bugs: None

#include "Ground.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="texture"></param>
Ground::Ground(sf::Texture & texture) :
	m_texture(texture)
{
	// Y = 850 for at home work
	m_position = sf::Vector2f(0, 875);//1400);
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
/// Call and updates the Ground methods and variables
/// </summary>
/// <param name="deltaTime"></param>
void Ground::update(sf::Time deltaTime)
{

}

/// <summary>
/// Renders and draws the Ground Sprites
/// </summary>
/// <param name="window"></param>
void Ground::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

/// <summary>
/// Sets the value of position with the given arguement
/// </summary>
/// <param name="position"></param>
void Ground::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// Gets the current value of the Ground Sprite
/// </summary>
/// <returns></returns>
sf::Sprite Ground::getSprite()
{
	return m_sprite;
}
