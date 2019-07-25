//
// C00204076
// Brandon Seah-Dempsey
// Started at 12:41 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "Tile.h"

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="sprite"></param>
/// <param name="t"></param>
Tile::Tile(sf::Vector2f position, sf::Sprite sprite, int t)
{
	m_sprite = sprite;
	m_position = position;
	m_type = t;
	m_width = 75;
	m_height = 75;
	m_sprite.setScale(sf::Vector2f(2, 2));
	m_alive = true;

	m_sprite.setPosition(m_position.x * m_sprite.getTextureRect().width * m_cTileSize, 
						 m_position.y * m_sprite.getTextureRect().height * m_cTileSize);
}

//
Tile::~Tile()
{
	//delete this;
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Tile::draw(sf::RenderWindow &window)
{
	
		window.draw(m_sprite);
	
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getPosition()
{
	return m_position;
}

//
sf::Vector2f Tile::getMapTileAtPoint(float x, float y)
{
	return sf::Vector2f((x * m_sprite.getTextureRect().width * m_cTileSize),
						(y * m_sprite.getTextureRect().height * m_cTileSize));
}

//
float Tile::getMapTileXAtPoint(float x)
{
	return float(x * m_sprite.getTextureRect().width * m_cTileSize);
}

//
float Tile::getMapTileYAtPoint(float y)
{
	return float (y * m_sprite.getTextureRect().height * m_cTileSize);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Sprite Tile::getSprite()
{
	return m_sprite;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int Tile::getType()
{
	return m_type;
}

//
bool Tile::getAlive()
{
	return m_alive;
}

//
void Tile::setAlive(bool alive)
{
	m_alive = true;
}