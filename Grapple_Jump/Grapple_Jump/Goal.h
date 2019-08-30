//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:39 15 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef GOAL_H
#define GOAL_H

#include "SFML/Graphics.hpp"

#include "Player.h"

//
class Goal
{
public:
	Goal();
	~Goal();

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

	float m_scaleX, m_scaleY, m_goalY;

	int m_alpha;
	bool m_flashIn, m_flashOut, m_moveUp, m_moveDown;
};

#endif // !GOAL_H
