// Ground header file used for methods and functions related to Ground
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 30 minutes
// Known Bugs: None

#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "AABB.h"

// Ground class
class Ground
{
public:
	Ground(sf::Texture & texture);
	~Ground();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
 	
	sf::Sprite getSprite();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	AABB *getAABB();
	

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;
	sf::IntRect m_sourceRectSprite;

	AABB * m_AABB;

	float scaleX, scaleY;
};

#endif // !GROUND_H