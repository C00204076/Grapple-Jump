//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

//
class Ground
{
public:
	Ground(sf::Texture & texture);
	~Ground();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

	sf::Sprite getSprite();
	void setPosition(sf::Vector2f position);

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;

	float scaleX, scaleY;
};

#endif // !GROUND_H