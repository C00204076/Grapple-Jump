//
// C00204076
// Brandon Seah-Dempsey
// Started at 15:40 23 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "MiniMap.h"

//
MiniMap::MiniMap(Player * player) :
	m_player(player)
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
void MiniMap::update(sf::Time deltaTime, sf::RenderWindow& window, sf::View view)
{
	m_player->update(deltaTime, view, false);
}

//
void MiniMap::draw(sf::RenderWindow& window, sf::View view, Ground *ground, HookPoint *point)
{
	//
	window.setView(view);
	//
	m_player->render(window, sf::Vector2f(3.0f, 3.0f));
	//
	window.draw(ground->getSprite());
	//
	window.draw(point->getSprite());
}