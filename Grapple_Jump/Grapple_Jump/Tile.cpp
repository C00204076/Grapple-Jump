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
	m_sprite.setScale(sf::Vector2f(2, 2));
	m_alive = true;

	m_sprite.setPosition(m_position.x * m_sprite.getTextureRect().width * m_sprite.getScale().x, m_position.y * m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

//
Tile::~Tile()
{
	delete this;
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Tile::draw(sf::RenderWindow *window)
{
	if (m_alive == true)
	{
		window->draw(m_sprite);
	}
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getPosition()
{
	return m_position;
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