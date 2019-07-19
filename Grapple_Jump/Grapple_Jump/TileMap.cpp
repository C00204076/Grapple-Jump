//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:48 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "TileMap.h"

//
TileMap::TileMap()
{
	initialise();
}

//
TileMap::~TileMap()
{

}

//
void TileMap::loadTexture()
{

}

//
void TileMap::initialise()
{
	loadTexture();

	m_groundSprite.setTexture(m_groundTexture);
	m_hookSprite.setTexture(m_hookTexture);
}

//
void TileMap::playerCollision(Player *player)
{

}

//
void TileMap::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < m_tileMap.size(); i++)
	{
		m_tileMap[i].draw(window);
	}
}

//
void TileMap::determindTile(int type, int x, int y)
{
	// Ground tile
	if (type == 0) 
	{
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_groundSprite, 0));
	}
	//Hook Point tile
	if (type == 1) 
	{
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_hookSprite, 1));
	}

	//
	if (type == 2)
	{

	}
	//
	if (type == 3)
	{

	}
}