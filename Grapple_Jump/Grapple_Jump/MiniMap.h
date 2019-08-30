//
// C00204076
// Brandon Seah-Dempsey
// Started at 15:39 23 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef MINIMAP_H
#define MINIMAP_H

#include <vector>


#include "Ground.h"
#include "HookPoint.h"
#include "Start.h"
#include "Goal.h"

class Player;

//
class MiniMap
{
public:
	MiniMap(Player * player);
	~MiniMap();

	void loadTexture();
	void initialise();

	void update(sf::Time deltaTime, sf::RenderWindow& window, sf::View view);
	void draw(sf::RenderWindow& window, sf::View view, Ground *ground, HookPoint *point, Start *start, Goal *goal);

private:
	sf::Texture m_borderTexture;
	sf::Sprite m_borderSprite;

	Player * m_player;
};

#include "Player.h"
#endif // !MINIMAP_H
