//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:39 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Player.h"

/// <summary>
/// 
/// </summary>
/// <param name="texture"></param>
/// <param name="otherTexture"></param>
Player::Player(sf::Texture & texture, sf::Texture & otherTexture) : 
	m_texture(texture),
	m_otherTexture(otherTexture)
{
	initialise();


}

/// <summary>
/// 
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 
/// </summary>
void Player::initialise()
{
	m_gravity = sf::Vector2f(0, -3.5);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(100, 1300);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);

	m_speed = 0.2f;
	m_pullSpeed = 8.0f;

	//m_world = b2World(new b2Vec2(0, 10), true);

	m_jumping = false;
	m_left = false;
	m_right = true;
}

//
void Player::update(sf::Time deltaTime, sf::RenderWindow& window, Ground ground)
{
	movePlayer();
	jump(deltaTime);
	collosionWithGround(ground);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_mousePosition = sf::Mouse::getPosition(window);

		/*std::cout << m_mousePosition.x << std::endl;
		std::cout << m_mousePosition.y << std::endl;*/

		m_mouseX = m_mousePosition.x;
		m_mouseY = m_mousePosition.y;
		m_mouseVector = sf::Vector2f(m_mouseX, m_mouseY);

		m_grapplingLine[0].position = sf::Vector2f(m_position.x, m_position.y);
		m_grapplingLine[0].color = sf::Color::White;
		m_grapplingLine[1].position = sf::Vector2f(m_mouseX, m_mouseY);
		m_grapplingLine[1].color = sf::Color::White;
		
		
		m_pullDirection = normalize(m_position - m_mouseVector);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;

		std::cout << m_directionX << std::endl;
		std::cout << m_directionY << std::endl;

		//m_jumping = true;
		//
		m_position.x -= m_pullDirection.x * m_pullSpeed;
		m_position.y -= m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);

		
	}

	
}

/// <summary>
/// 
/// </summary>
void Player::movePlayer()
{
	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::A))
	{
		//std::cout << "Moving Left!" << std::endl;
		m_left = true;
		m_right = false;

		m_position.x -= 7;
		m_sprite.setTexture(m_otherTexture);
		//
		m_sprite.setPosition(m_position);
	}

	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::D))
	{
		//std::cout << "Moving Right!" << std::endl;
		m_left = false;
		m_right = true;

		m_position.x += 7;
		m_sprite.setTexture(m_texture);
		//
		m_sprite.setPosition(m_position);
	}

	
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void Player::jump(sf::Time deltaTime)
{
	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::Space) && m_jumping == false)
	{
		//std::cout << "Jumping!" << std::endl;

		m_velocity.y = -250;
		m_jumping = true;
	}

	//
	if (m_jumping == true)
	{
		m_velocity.y -= m_gravity.y;
		m_position.y = m_position.y + ((m_velocity.y * deltaTime.asSeconds()) + (0.5 * m_gravity.y) * (deltaTime.asSeconds() * deltaTime.asSeconds()));
		//m_position.y = m_position.y + ((m_velocity.y * deltaTime.asSeconds()) + (0.5 * m_gravity.y) * (deltaTime.asSeconds() * deltaTime.asSeconds()));
		//
		m_sprite.setPosition(m_position);
	}
}

//
void Player::collosionWithGround(Ground ground)
{
	if (m_sprite.getGlobalBounds().intersects(ground.getSprite().getGlobalBounds()))
	{
		m_jumping = false;
	}
	else
	{
		//m_jumping = true;
	}
}

//
sf::Vector2f Player::normalize(sf::Vector2f vector)
{
	float lenght = sqrt((vector.x * vector.x) + (vector.y * vector.y));

	//
	if (lenght != 0)
	{
		return sf::Vector2f(vector.x / lenght, vector.y / lenght);
	}
	//
	else
	{
		return vector;
	}


	
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow& window)
{
	window.draw(m_grapplingLine, 2, sf::Lines);
	window.draw(m_sprite);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPosition()
{
	return m_position;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
sf::Vector2i Player::getMousePosition()
{
	return m_mousePosition;
}
