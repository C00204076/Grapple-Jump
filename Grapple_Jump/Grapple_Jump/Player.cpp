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
Player::Player()
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
void Player::loadTextures()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Player.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_otherTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/OtherPlayer.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_hookTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Hook.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}
}

/// <summary>
/// 
/// </summary>
void Player::initialise()
{
	loadTextures();

	m_gravity = sf::Vector2f(0, -3.5);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_position = sf::Vector2f(100, 1300);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);

	//
	m_hookSprite.setTexture(m_hookTexture);
	m_hookSprite.setOrigin(5, 5);
	

	m_speed = 0.2f;
	m_pullSpeed = 8.0f;

	//m_world = b2World(new b2Vec2(0, 10), true);

	m_jumping = false;
	m_left = false;
	m_right = true;
	m_fired = false; 
	m_hookLatched = false;
}

//
void Player::update(sf::Time deltaTime, sf::RenderWindow& window, Ground ground)
{
	m_mousePosition = sf::Mouse::getPosition(window);

	m_mouseX = m_mousePosition.x;
	m_mouseY = m_mousePosition.y;
	m_mouseVector = sf::Vector2f(m_mouseX, m_mouseY);

	movePlayer();
	jump(deltaTime);
	collosionWithGround(ground);

	//
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		m_grapplingLine[0].position = sf::Vector2f(m_position.x, m_position.y);
		m_grapplingLine[0].color = sf::Color::White;
		m_grapplingLine[1].position = sf::Vector2f(m_hookPosition.x, m_hookPosition.y);
		m_grapplingLine[1].color = sf::Color::White;

		//
		if (m_fired == false)
		{
			m_hookSprite.setPosition(m_sprite.getPosition());
			m_hookPosition = m_sprite.getPosition();

			/*m_hookSprite.setPosition(m_mouseVector);
			m_hookPosition = m_mouseVector;*/

			m_fired = true;
		}
		
		
		m_pullDirection = normalize(m_position - m_mouseVector);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;

		std::cout << m_directionX << std::endl;
		std::cout << m_directionY << std::endl;


		//
		if (m_hookLatched == false && m_hookPosition != m_mouseVector)
		{
			m_cablePullDir = normalize(m_hookPosition - m_mouseVector);
			m_cablePullX = m_cablePullDir.x;
			m_cablePullY = m_cablePullDir.y;

			std::cout << m_cablePullX << std::endl;
			std::cout << m_cablePullY << std::endl;

			m_hookPosition.x -= m_cablePullDir.x * m_pullSpeed;
			m_hookPosition.y -= m_cablePullDir.y * m_pullSpeed;
			m_hookSprite.setPosition(m_hookPosition);



			if (m_hookPosition.x >= m_mouseVector.x && 
				m_hookPosition.y >= m_mouseVector.y)
			{
				m_hookLatched = true;
			}
		}

		//
		if (m_hookLatched == true)
		{
			m_position.x -= m_pullDirection.x * m_pullSpeed;
			m_position.y -= m_pullDirection.y * m_pullSpeed;
			m_sprite.setPosition(m_position);
		}

		
	}
	else
	{
		m_hookLatched = false;
		m_fired = false;
	}

	//
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_hookLatched == true)
	{
		//
		if (m_hookLatched == true)
		{
			m_position.x -= m_pullDirection.x * m_pullSpeed;
			m_position.y -= m_pullDirection.y * m_pullSpeed;
			m_sprite.setPosition(m_position);
		}
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
	//
	window.draw(m_grapplingLine, 2, sf::Lines);

	//
	if (m_fired == true)
	{
		window.draw(m_hookSprite);
	}

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
