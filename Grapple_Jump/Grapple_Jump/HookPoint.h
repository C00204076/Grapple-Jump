//
// C00204076
// Brandon Seah-Dempsey
// Started at 13:43 21 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

//
class HookPoint
{
public:
	HookPoint(sf::Texture & texture);
	~HookPoint();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

	sf::Sprite getSprite();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_position;

};