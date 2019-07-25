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

class Player;

//
class MiniMap
{
public:
	MiniMap();
	~MiniMap();

	void loadTexture();
	void initialise();

	void update(sf::Time deltaTime, Player * player);
	void draw(sf::RenderWindow& window, sf::View view, Player *player, Ground *ground, HookPoint *point);

private:
	sf::Texture m_borderTexture;
	sf::Sprite m_borderSprite;
};

#include "Player.h"
#endif // !MINIMAP_H
