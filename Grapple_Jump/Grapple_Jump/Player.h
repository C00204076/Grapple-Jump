//
// C00204076
// Brandon Seah-Dempsey
// Started at 9:53 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <math.h>


//
class Game; //Forward delaration for cyclical reference

//
class Player
{
public:
	Player(sf::Texture & texture, sf::Texture & Othertexture);
	~Player();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void initialise();

	sf::Vector2f getPosition();

private:
	void movePlayer();
	void jump(sf::Time deltaTime);

	sf::Keyboard m_keyboard;

	sf::Sprite m_sprite;
	sf::Texture m_texture, m_otherTexture;

	sf::Vector2f m_gravity, m_velocity, m_acceleration, m_position;

	bool m_jumping, m_left, m_right;
};

#include "Game.h"
#endif // !PLAYER_H
