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
	//
	if (!m_groundTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Ground-(small).png"))
	{
		std::cout << "Error! Unable to load Ground-(small).png from game files!" << std::endl;
	}
	//
	if (!m_hookTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Block-(small).png"))
	{
		std::cout << "Error! Unable to load Block-(small).png from game files!" << std::endl;
	}

	
	//
	if (!m_boundaryTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Boundary-(small).png"))
	{
		std::cout << "Error! Unable to load Boundary-(small).png from game files!" << std::endl;
	}
}

//
void TileMap::initialise()
{
	loadTexture();


	m_groundSprite.setTexture(m_groundTexture);
	m_hookSprite.setTexture(m_hookTexture);

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			determineTile(m_mapLayoutOne[i][j], j, i);
		}
	}
}

//
void TileMap::update(sf::Time deltaTime, Player *player, GrapplingHook *hook)
{
	playerCollision(player);
	hookCollision(hook);
}

//
void TileMap::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < m_tileMap.size(); i++)
	{
		m_tileMap[i].draw(window);
	}
}

//
void TileMap::playerCollision(Player *player)
{

}

//
void TileMap::hookCollision(GrapplingHook *hook)
{

}

//
void TileMap::determineTile(int type, int x, int y)
{
	// Ground tile
	if (type == 1) 
	{
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_groundSprite, 1));
	}
	//Hook Point tile
	if (type == 2) 
	{
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_hookSprite, 2));
	}

	//Start tile
	if (type == 3)
	{
		//m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_startSprite, 3));
	}

	// Goal tile
	if (type == 4)
	{
		//m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_goalSprite, 4));
	}

	// Power-up 1 tile
	if (type == 5)
	{
		//m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_powerOneSprite, 5));
	}

	// Power-up 2 tile
	if (type == 6)
	{
		//m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_powerTwoSprite, 6));
	}

	// Boundary tile
	if (type == 7)
	{
		//m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_boundarySprite, 7));
	}

}