//
// C00204076
// Brandon Seah-Dempsey
// Started at 15:40 23 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "MiniMap.h"

//
MiniMap::MiniMap()
{
	initialise();
}

//
MiniMap::~MiniMap()
{

}

//
void MiniMap::initialise()
{
	loadTexture();

	m_borderSprite.setTexture(m_borderTexture);

}

//
void MiniMap::loadTexture()
{
	if (!m_borderTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Border.png"))
	{
		std::cout << "Error! Unable to load Block.png from game files!" << std::endl;
	}
}

//
void MiniMap::update(sf::Time deltaTime, Player * player)
{

}

//
void MiniMap::draw(sf::RenderWindow& window, sf::View view, Player *player, Ground *ground, HookPoint *point)
{
	//
	window.setView(view);
	//
	window.draw(player->getSprite());
	//
	window.draw(ground->getSprite());
	//
	window.draw(point->getSprite());
}