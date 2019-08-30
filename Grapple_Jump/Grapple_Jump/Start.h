//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:15 15 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef START_H
#define START_H

#include "SFML/Graphics.hpp"

#include "Player.h"

//
class Start
{
public:
	Start();
	~Start();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window, sf::Vector2f scale);

	bool playerCollision(Player * player);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();

private:
	void loadTexture();
	void initialise();
	void juiciness();

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;

	float m_scaleX, m_scaleY, m_startY;

	int m_alpha;
	bool m_flashIn, m_flashOut, m_moveUp, m_moveDown;
};

#endif // !START_H
