// Hook Point header file used for methods and functions related to Hook Point
// C00204076
// Brandon Seah-Dempsey
// Started at 13:43 21 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 30 minutes
// Known Bugs: None

#ifndef HOOKPOINT_H
#define HOOKPOINT_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

// HookPoint class
class HookPoint
{
public:
	HookPoint();
	HookPoint(int x, int y);
	~HookPoint();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window, sf::Vector2f scale);
	sf::Sprite getSprite();
	void setPosition(sf::Vector2f position);

	void setTilePosition(int x, int y);

private:
	void loadTexture();
	void juiciness();

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;

	int m_alpha;
	bool m_flashIn, m_flashOut;
};

#endif // !HOOKPOINT_H