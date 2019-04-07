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
	m_position = sf::Vector2f(100, 800);//sf::Vector2f(100, 1300);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);
	//
	m_sprite.setScale(0.7f, 0.7f);
	//

	//
	m_hookSprite.setTexture(m_hookTexture);
	m_hookSprite.setOrigin(5, 5);
	

	m_speed = 0.2f;
	m_pullSpeed = 8.0f;
	m_maxLength = 600.0f;

	m_jumping = false;
	m_left = false;
	m_right = true;
	m_fired = false; 
	m_hookLatched = false;
	m_cableAdjust = false;
	m_pulled = false;
	m_extend = false;
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
	grapplingHook();
	collosionWithGround(ground);

	m_grapplingLine[0].position = sf::Vector2f(m_position.x, m_position.y);
	m_grapplingLine[0].color = sf::Color::White;
	m_grapplingLine[1].position = sf::Vector2f(m_hookPosition.x, m_hookPosition.y);
	m_grapplingLine[1].color = sf::Color::White;

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
void Player::grapplingHook()
{
	// Launches the grappling hook if the Left Mouse button is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//
		if (m_fired == false)
		{
			m_hookSprite.setPosition(m_sprite.getPosition());
			m_hookPosition = m_sprite.getPosition();
			m_tempMouseVec = m_mouseVector;

			/*m_hookSprite.setPosition(m_mouseVector);
			m_hookPosition = m_mouseVector;*/

			m_fired = true;
		}
	}

	// Detaches the grappling hook if the Right Mouse button is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//
		if (m_hookLatched == true)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_extend = false;
		}
	}

	//
	if (m_fired == true && m_hookLatched == false)
	{
		//
		m_cablePullDir = normalize(m_hookPosition - m_tempMouseVec);
		m_cablePullX = m_cablePullDir.x;
		m_cablePullY = m_cablePullDir.y;
		//
		m_hookPosition.x -= m_cablePullDir.x * m_pullSpeed;
		m_hookPosition.y -= m_cablePullDir.y * m_pullSpeed;
		m_hookSprite.setPosition(m_hookPosition);
		//
		if (m_hookPosition.x >= m_tempMouseVec.x - 15 &&
			m_hookPosition.x <= m_tempMouseVec.x + 15 &&
			m_hookPosition.y >= m_tempMouseVec.y - 15 &&
			m_hookPosition.y <= m_tempMouseVec.y + 15)
		{
			m_hookLatched = true;
		}
	}

	//
	if (m_hookLatched == true)
	{
		//
		/*m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;
		//
		m_position.x -= m_pullDirection.x * m_pullSpeed;
		m_position.y -= m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);
		//
		if (m_position.x >= m_tempMouseVec.x - 10 &&
			m_position.x <= m_tempMouseVec.x + 10 &&
			m_position.y >= m_tempMouseVec.y - 10 &&
			m_position.y <= m_tempMouseVec.y + 10)
		{
			m_hookLatched = false;
			m_fired = false;
		}*/
	}

	// The W key is press to retract the grappling hook
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_hookLatched == true)
	{
		//
		m_pulled = true;
		m_cableAdjust = true;
		//
		m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;
		//
		m_position.x -= m_pullDirection.x * m_pullSpeed;
		m_position.y -= m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);
		//
		if (m_position.x >= m_tempMouseVec.x - 10 &&
			m_position.x <= m_tempMouseVec.x + 10 &&
			m_position.y >= m_tempMouseVec.y - 10 &&
			m_position.y <= m_tempMouseVec.y + 10)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
		}
	}
	// Else if W key is not pressed
	else
	{
		m_pulled = false;
	}

	// The S key is pressed to extend the grappling hook
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_hookLatched == true)
	{
		//
		m_extend = true;
		m_cableAdjust = true;
		//
		m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;
		//
		m_position.x += m_pullDirection.x * m_pullSpeed;
		m_position.y += m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);
		//
		if (m_position.x >= m_tempMouseVec.x - 10 &&
			m_position.x <= m_tempMouseVec.x + 10 &&
			m_position.y >= m_tempMouseVec.y - 10 &&
			m_position.y <= m_tempMouseVec.y + 10)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_extend = false;
		}// End if
	}// End if
	// Else if S key is not pressed
	else
	{
		m_extend = false;
	}

	//
	if (m_cableAdjust == true)
	{
		//
		if (m_pulled == false && m_extend == false)
		{
			// If player is above grappling hook
			if (m_position.y < m_tempMouseVec.y + 100)
			{
				m_position.y += 10;
				
				// Right side of grappling hook
				if (m_position.x >= m_tempMouseVec.x - 10)
				{
					m_position.x -= 4;
				}
				// Left side of grappling hook
				else if (m_position.x <= m_tempMouseVec.x + 10)
				{
					m_position.x += 4;
				}

				m_sprite.setPosition(m_position);
			} // End if

			// If player is below grappling hook
			if (m_position.y > m_tempMouseVec.y)
			{
				//  Right side of grappling hook
				if (m_position.x > m_tempMouseVec.x + 10)
				{
					m_position.x -= 2;
				}
				// Left side of grappling hook
				else if (m_position.x < m_tempMouseVec.x - 10)
				{
					m_position.x += 2;
				}
				else if (m_position == m_tempMouseVec)
				{ 

				}

				m_sprite.setPosition(m_position);
			}// End if
		} // End if
	}// End if
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
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));

	//
	if (length != 0)
	{
		//std::cout << length << std::endl;
		return sf::Vector2f(vector.x / length, vector.y / length);
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
	if (m_fired == true)
	{
		//
		window.draw(m_grapplingLine, 2, sf::Lines);
		//
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
