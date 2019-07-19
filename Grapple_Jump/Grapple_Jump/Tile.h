//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:51 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

//
class Tile
{
public:
	Tile(sf::Vector2f position, sf::Sprite sprite, int type);
	~Tile();

	void draw(sf::RenderWindow * window);

	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	int getType();
	bool getAlive();

	void setAlive(bool alive);

private:
	sf::Sprite m_sprite;
	int m_type;
	bool m_alive;

	sf::Vector2f m_position;
	//std::vector<Tile*> m_adjacents;
};
#endif // !TILE_H