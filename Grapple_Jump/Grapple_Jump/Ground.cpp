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
Ground::Ground()
{
	loadTexture();
	// Y = 850 for at home work
	m_position = sf::Vector2f(50, 800);//1400);
	m_scaleX = 2;
	m_scaleY = 1;

	//
	m_sprite.setTexture(m_texture);
	m_topBorderBox.setTexture(m_boundingBoxTexture);
	m_bottomBorderBox.setTexture(m_boundingBoxTexture);
	m_leftBorderBox.setTexture(m_boundingBoxTexture);
	m_rightBorderBox.setTexture(m_boundingBoxTexture);
	//
	m_topBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_bottomBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_leftBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_rightBorderBox.setColor(sf::Color(255, 255, 255, 0));
	//
	m_sprite.setScale(m_scaleX, m_scaleY);
	m_topBorderBox.setScale(m_scaleX, 1);
	m_bottomBorderBox.setScale(m_scaleX, 1);
	m_leftBorderBox.setScale(1, m_scaleY);
	m_rightBorderBox.setScale(1, m_scaleY);
	//
	m_sprite.setPosition(m_position);
	m_topBorderBox.setPosition(m_position.x, m_position.y - 75);
	m_bottomBorderBox.setPosition(m_position.x, m_position.y + (75 * m_scaleY));
	m_leftBorderBox.setPosition(m_position.x - 75, m_position.y);
	m_rightBorderBox.setPosition(m_position.x + (75 * m_scaleX), m_position.y);

	m_AABB = new AABB(m_position.x, m_position.y, m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
}

//
Ground::Ground(int x, int y, float scaleX, float scaleY)
{
	loadTexture();

	m_position = sf::Vector2f(x, y);
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	//
	m_sprite.setTexture(m_texture);
	m_topBorderBox.setTexture(m_boundingBoxTexture);
	m_bottomBorderBox.setTexture(m_boundingBoxTexture);
	m_leftBorderBox.setTexture(m_boundingBoxTexture);
	m_rightBorderBox.setTexture(m_boundingBoxTexture);
	m_topLeftBox.setTexture(m_boundingBoxTexture);
	m_topRightBox.setTexture(m_boundingBoxTexture);
	//
	m_topBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_bottomBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_leftBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_rightBorderBox.setColor(sf::Color(255, 255, 255, 0));
	m_topLeftBox.setColor(sf::Color(255, 255, 255, 0));
	m_topRightBox.setColor(sf::Color(255, 255, 255, 0));
	//
	m_sprite.setScale(m_scaleX, m_scaleY);
	m_topBorderBox.setScale(m_scaleX, 1);
	m_bottomBorderBox.setScale(m_scaleX, 1);
	m_leftBorderBox.setScale(1, m_scaleY);
	m_rightBorderBox.setScale(1, m_scaleY);
	//
	m_sprite.setPosition(m_position);
	m_topBorderBox.setPosition(m_position.x, m_position.y - 75);
	m_bottomBorderBox.setPosition(m_position.x, m_position.y + (75 * m_scaleY));
	m_leftBorderBox.setPosition(m_position.x - 75, m_position.y);
	m_rightBorderBox.setPosition(m_position.x + (75 * m_scaleX), m_position.y);
	m_topLeftBox.setPosition(m_position.x - 75, m_position.y - 75);
	m_topRightBox.setPosition(m_position.x + (75 * m_scaleX), m_position.y -75);
}

/// <summary>
/// Default deconstructor
/// </summary>
Ground::~Ground()
{

}

//
void Ground::loadTexture()
{
	//
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Ground-(small).png"))
	{
		std::cout << "Error! Unable to load Ground-(small).png from game files!" << std::endl;
	}
	//
	if (!m_boundingBoxTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Block-(small).png"))
	{
		std::cout << "Error! Unable to load Block-(small).png from game files!" << std::endl;
	}
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
	//
	window.draw(m_topBorderBox);
	window.draw(m_bottomBorderBox);
	window.draw(m_leftBorderBox);
	window.draw(m_rightBorderBox);
	window.draw(m_topLeftBox);
	window.draw(m_topRightBox);
	//
	window.draw(m_sprite);
}

/// <summary>
/// Sets the value of position with the given arguement
/// </summary>
/// <param name="position"></param>
void Ground::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_AABB = new AABB(position.x, position.y, m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
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

//
sf::Sprite Ground::getTopBoundingBox()
{
	return m_topBorderBox;
}

//
sf::Sprite Ground::getBottomBoundingBox()
{
	return m_bottomBorderBox;
}

//
sf::Sprite Ground::getLeftBoundingBox()
{
	return m_leftBorderBox;
}

//
sf::Sprite Ground::getRightBoundingBox()
{
	return m_rightBorderBox;
}

//
sf::Sprite Ground::getTopLeftBoundingBox()
{
	return m_topLeftBox;
}

//
sf::Sprite Ground::getTopRightBoundingBox()
{
	return m_topRightBox;
}

//
float Ground::getScaleX()
{
	return m_scaleX;
}

//
float Ground::getScaleY()
{
	return m_scaleY;
}

//
sf::Vector2f Ground::getPosition()
{
	return m_position;
}

//
AABB *Ground::getAABB()
{
	return m_AABB;
}