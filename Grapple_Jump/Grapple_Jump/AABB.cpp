//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:35 4 July 2019
// Finished at 
// Time taken: 
// Known bugs: None

#include "AABB.h"

/// <summary>
/// Constructor of AABB
/// </summary>
/// <param name="X"></param>
/// <param name="Y"></param>
/// <param name="W"></param>
/// <param name="H"></param>
AABB::AABB(float x, float y, float width, float height) :
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height)
{
	initialise();
}

/// <summary>
/// Deconstructor of AABB
/// </summary>
/// <returns></returns>
AABB::~AABB()
{

}

//
void AABB::initialise()
{
	m_extends = sf::Vector2f(m_width / 2, m_height / 2);
	m_center = sf::Vector2f(m_x + m_extends.x, m_y + m_extends.y);
	m_size = sf::Vector2f(m_extends.x * 2, m_extends.y * 2);
	
	m_min = sf::Vector2f(m_x, m_y);
	m_max = sf::Vector2f(m_x + m_width, m_y + m_height);
}

//
sf::Vector2f AABB::closestPointOnBoundsToPoint(sf::Vector2f boundingBox)
{
	float minDist = abs(boundingBox.x - m_min.x);
	sf::Vector2f boundsPoints = sf::Vector2f(m_min.x, boundingBox.y);

	
	if(abs(m_max.x - boundingBox.x) < minDist)
	{
		minDist = abs(m_max.x - boundingBox.x);
		boundsPoints = sf::Vector2f(m_max.x, boundingBox.y);
	}

	if(abs(m_max.y - boundingBox.y) < minDist)
	{
		minDist = abs(m_max.y - boundingBox.y);
		boundsPoints = sf::Vector2f(boundingBox.x, m_max.y);
	}

	if (abs(m_min.y - boundingBox.y) < minDist)
	{
		minDist = abs(m_min.y - boundingBox.y);
		boundsPoints = sf::Vector2f(boundingBox.x, m_min.y);
	}

	return boundsPoints;
}

//
AABB AABB::minkowskiDifference(AABB *other)
{
	sf::Vector2f topLeft = m_min - other->getMax();
	sf::Vector2f fullSize = m_size + other->getSize();

	float newX, newY, newW, newH;

	newX = topLeft.x + (fullSize.x / 2);
	newY = topLeft.y + (fullSize.y / 2);
	newW = fullSize.x / 2;
	newH = fullSize.y / 2;

	return AABB(newX, newY, newW, newH);
}

//
sf::Vector2f AABB::getMin()
{
	return sf::Vector2f(m_center.x - m_extends.x, m_center.y - m_extends.y);
}

//
sf::Vector2f AABB::getMax()
{
	return sf::Vector2f(m_center.x + m_extends.x, m_center.y + m_extends.y);
}



/// <summary>
/// Returns the X of AABB
/// </summary>
/// <returns></returns>
float AABB::getX()
{
	return m_x;
}

/// <summary>
/// Returns the Y of AABB
/// </summary>
/// <returns></returns>
float AABB::getY()
{
	return m_y;
}

/// <summary>
/// Returns the width of AABB
/// </summary>
/// <returns></returns>
float AABB::getWidth()
{
	return m_width;
}

/// <summary>
/// Returns the height of AABB
/// </summary>
/// <returns></returns>
float AABB::getHeight()
{
	return m_height;
}

//
sf::Vector2f AABB::getSize()
{
	return m_size;
}

//
sf::Vector2f AABB::getCenter()
{
	return m_center;
}

//
void AABB::setCenter(sf::Vector2f center)
{
	m_center = center;
}