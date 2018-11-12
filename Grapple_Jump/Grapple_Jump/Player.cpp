//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:39 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Player.h"

//
Player::Player(sf::Texture & texture, sf::Texture & otherTexture) : 
	m_texture(texture),
	m_otherTexture(otherTexture)
{
	m_position = sf::Vector2f(100, 1300);


	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);
}

//
Player::~Player()
{

}

//
void Player::initialise()
{

}

//
void Player::update(sf::Time deltaTime)
{
	movePlayer();
	jump();


}

//
void Player::movePlayer()
{
	if (m_keyboard.isKeyPressed(sf::Keyboard::Left))
	{
		std::cout << "Moving Left!" << std::endl;

		m_position.x -= 6;
		m_sprite.setTexture(m_otherTexture);
	}

	if (m_keyboard.isKeyPressed(sf::Keyboard::Right))
	{
		std::cout << "Moving Right!" << std::endl;

		m_position.x += 6;
		m_sprite.setTexture(m_texture);
	}

	m_sprite.setPosition(m_position);
}

//
void Player::jump()
{

}

//
void Player::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//
sf::Vector2f Player::getPosition()
{
	return m_position;
}
