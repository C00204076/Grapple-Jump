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
	m_gravity = sf::Vector2f(0, -2.5);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(100, 1300);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);

	m_jumping = false;
	m_left = false;
	m_right = true;
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
	jump(deltaTime);


}

//
void Player::movePlayer()
{
	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Moving Left!" << std::endl;
		m_left = true;
		m_right = false;

		m_position.x -= 7;
		m_sprite.setTexture(m_otherTexture);
	}

	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "Moving Right!" << std::endl;
		m_left = false;
		m_right = true;

		m_position.x += 7;
		m_sprite.setTexture(m_texture);
	}

	//
	m_sprite.setPosition(m_position);
}

//
void Player::jump(sf::Time deltaTime)
{
	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::Space) && m_jumping == false)
	{
		std::cout << "Jumping!" << std::endl;

		m_velocity.y = -100;
		m_jumping = true;
	}

	//
	if (m_jumping == true)
	{
		m_velocity.y -= m_gravity.y;
		m_position.y = m_position.y + ((m_velocity.y * deltaTime.asSeconds()) + (0.5 * m_gravity.y) * (deltaTime.asSeconds() * deltaTime.asSeconds()));
	}
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
