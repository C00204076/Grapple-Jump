// Sets the methods, functions and changes of the variables related to Hook Point header file
// C00204076
// Brandon Seah-Dempsey
// Started at 13:50 21 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 30 minutes
// Known Bugs: None

#include "HookPoint.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="texture"></param>
HookPoint::HookPoint()
{
	loadTexture();
	// Y = 50 for at home work
	//m_position = sf::Vector2f(700, 600);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.45f, 0.45f);
}

//
HookPoint::HookPoint(int x, int y)
{
	loadTexture();

	m_sprite.setPosition(m_position.x * m_sprite.getTextureRect().width * m_sprite.getScale().x,
						 m_position.y * m_sprite.getTextureRect().height * m_sprite.getScale().y);
	
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.45f, 0.45f);
}

/// <summary>
/// Default deconstructor
/// </summary>
HookPoint::~HookPoint()
{

}

//
void HookPoint::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Block.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}
}

/// <summary>
/// Call and updates the Hook Points methods and variables
/// </summary>
/// <param name="deltaTime"></param>
void HookPoint::update(sf::Time deltaTime)
{

}

/// <summary>
/// Renders and draws Hook Point Sprites
/// </summary>
/// <param name="window"></param>
void HookPoint::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

/// <summary>
/// Set the Hook Point's position with the given arguement
/// </summary>
/// <param name="position"></param>
void HookPoint::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//
void HookPoint::setTilePosition(int x, int y)
{
	m_position = sf::Vector2f(x, y);

	m_sprite.setPosition(m_position.x * m_sprite.getTextureRect().width * m_sprite.getScale().x,
						 m_position.y * m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

/// <summary>
/// Gets the current value of the Hook Point Sprite
/// </summary>
/// <returns></returns>
sf::Sprite HookPoint::getSprite()
{
	return m_sprite;
}