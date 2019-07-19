//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:47 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Player.h"

//
class TileMap
{
public:
	TileMap();
	~TileMap();

	void loadTexture();
	void initialise();

	void draw(sf::RenderWindow *window);
	void determindTile(int type, int x, int y);

	void playerCollision(Player *player);
	//void hookCollision();

private:
	sf::Texture m_groundTexture, m_hookTexture;
	sf::Sprite m_groundSprite, m_hookSprite;

	std::vector<Tile> m_tileMap;
	int m_maps, m_mapLayout;
};
#endif // !TILEMAP_H