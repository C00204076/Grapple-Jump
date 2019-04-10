//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:39 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Player.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="texture"></param>
/// <param name="otherTexture"></param>
Player::Player()
{
	initialise();
}

/// <summary>
/// Default deconstructor
/// </summary>
Player::~Player()
{

}

/// <summary>
/// Loads the Player and Grappling Hook textures
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
/// Initialises Player and Grappling Hook variables
/// </summary>
void Player::initialise()
{
	loadTextures();

	m_gravity = sf::Vector2f(0, 4.0f);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	// Vector2f = (100, 800) for at home work
	m_position = sf::Vector2f(100, 1300);

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50, 50);
	//
	//m_sprite.setScale(0.7f, 0.7f);
	//

	m_hookSprite.setTexture(m_hookTexture);
	m_hookSprite.setOrigin(5, 5);
	
	m_pullSpeed = 30.0f;
	m_maxLength = 500.0f;

	m_jumping = false;
	m_falling = true;
	m_left = false;
	m_right = true;
	m_fired = false; 
	m_hookLatched = false;
	m_cableAdjust = false;
	m_pulled = false;
	m_extend = false;
}

//
void Player::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	// Gets the current position of the mouse cursor, relative to the game window
	m_mousePosition = sf::Mouse::getPosition(window);
	// Set the mouse X and Y to floats, then to Vector2f; as a means of converting Vector2i
	// to Vector2f
	m_mouseX = m_mousePosition.x;
	m_mouseY = m_mousePosition.y;
	m_mouseVector = sf::Vector2f(m_mouseX, m_mouseY);

	movePlayer();
	jump(deltaTime);
	grapplingHook();
	boundaryCheck();
	resetHook();
}

/// <summary>
/// Method used to allow Player to move left or right using a key input
/// </summary>
void Player::movePlayer()
{
	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::A) && (m_cableAdjust == false || m_jumping == true || m_falling == false))
	{
		m_left = true;
		m_right = false;

		m_position.x -= 7;
		m_sprite.setTexture(m_otherTexture);

		m_sprite.setPosition(m_position);
	}

	//
	if (m_keyboard.isKeyPressed(sf::Keyboard::D) && (m_cableAdjust == false || m_jumping == true || m_falling == false))
	{
		m_left = false;
		m_right = true;

		m_position.x += 7;
		m_sprite.setTexture(m_texture);

		m_sprite.setPosition(m_position);
	}

}

/// <summary>
/// Method used to allow Player to jump using a key input
/// </summary>
/// <param name="deltaTime"></param>
void Player::jump(sf::Time deltaTime)
{
	// If Space key is pressed and Grappling Hook is not latched onto a Hook Point
	if (m_keyboard.isKeyPressed(sf::Keyboard::Space) && m_jumping == false && m_hookLatched == false)
	{
		// Gets the max jumping height using the Player position
		m_maxLength = m_position.y - 450;

		m_jumping = true;
		m_cableAdjust = true;
	}

	// While Player is jumping
	if (m_jumping == true)
	{
		m_position.y -= 12;

		// If Player reaches max jump height
		if (m_position.y <= m_maxLength)
		{
			m_jumping = false;
			m_falling = true;
		}

		m_sprite.setPosition(m_position);
	}

	if (m_falling == true)
	{
		//
		m_position.y += 15;
		//
		m_sprite.setPosition(m_position);
	}
	
}

/// <summary>
/// Boundary check to keep Player within Game window
/// </summary>
void Player::boundaryCheck()
{
	// If Player moves too far off the left side of the window
	if (m_position.x < -5)
	{
		m_position.x = 0;
		m_sprite.setPosition(m_position);
	}
	// Or if the Player move too far off the right side of the window
	else if (m_position.x > 2600)
	{
		m_position.x = 2600;
		m_sprite.setPosition(m_position);
	}
	// If Player somehow manages to fall through the Ground and into the void
	if (m_position.y > 1630)
	{
		m_position.y = 1300;
		m_sprite.setPosition(m_position);
	}
}

/// <summary>
/// Method used to fire and control the Player's Grappling Hook
/// </summary>
void Player::grapplingHook()
{
	// Launches the Grappling Hook if the Left Mouse button is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Fires Grappling Hook only if m_fired is false
		if (m_fired == false)
		{
			// Sets the hooks position to the Player's and it's destination position to the mouse's
			m_hookSprite.setPosition(m_sprite.getPosition());
			m_hookPosition = m_sprite.getPosition();
			m_tempMouseVec = m_mouseVector;;

			m_fired = true;
		}
	}

	// Detaches the Grappling Hook if the Right Mouse button is pressed...
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//...but only if Grappling Hook is latched onto a Hook Point
		if (m_hookLatched == true)
		{
			m_hookSprite.setPosition(m_sprite.getPosition());
			m_hookPosition = m_sprite.getPosition();
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_extend = false;
			m_falling = true;
		}
	}

	// If Grappling Hook is fired, but latched onto a Hook Point
	if (m_fired == true && m_hookLatched == false)
	{
		// Normalises vector used for direction the Grappling Hook cable is pulled in
		m_cablePullDir = normalize(m_hookPosition - m_tempMouseVec);
		m_cablePullX = m_cablePullDir.x;
		m_cablePullY = m_cablePullDir.y;
		// Gets the new position of the hook on the Grappling Hook an sets it's new position
		m_hookPosition.x -= m_cablePullDir.x * m_pullSpeed;
		m_hookPosition.y -= m_cablePullDir.y * m_pullSpeed;
		m_hookSprite.setPosition(m_hookPosition);
		// If the Grappling Hook gets to the position of the Hook Point but doesn't latch onto it
		if (m_hookPosition.x >= m_tempMouseVec.x - 7 &&
			m_hookPosition.x <= m_tempMouseVec.x + 7 &&
			m_hookPosition.y >= m_tempMouseVec.y - 7 &&
			m_hookPosition.y <= m_tempMouseVec.y + 7 &&
			m_hookLatched == false)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_extend = false;
		}// End if
	}// End if

	// Can be used to automatically pull Player towards Hook Point without hold retract key;
	// code within statement must be uncommented
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
		// Pull and cable adjust are true
		m_pulled = true;
		m_cableAdjust = true;
		// The pull direction is acquired by normalising the player position minus the destination
		// position
		m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;
		// The new Player's is found and set, making it look as though the Grappling Hook is 
		// pulling them towards their destination
		m_position.x -= m_pullDirection.x * m_pullSpeed;
		m_position.y -= m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);
		// If the Player reaches the destination position, Grappling Hook is reset and 
		// Player is set to fall
		if (m_position.x >= m_tempMouseVec.x - 12 &&
			m_position.x <= m_tempMouseVec.x + 12 &&
			m_position.y >= m_tempMouseVec.y - 12 &&
			m_position.y <= m_tempMouseVec.y + 12)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_falling = true;
		}// End if
	}// End if
	// Else if W key is not pressed
	else
	{
		m_pulled = false;
	}

	// The S key is pressed to extend the grappling hook
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_hookLatched == true)
	{
		m_extend = true;
		m_cableAdjust = true;
		// While is uses the same variable, the extend direction is acquired by 
		//normalising the player position minus the destination position
		m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;

		m_position.x += m_pullDirection.x * m_pullSpeed;
		m_position.y += m_pullDirection.y * m_pullSpeed;
		m_sprite.setPosition(m_position);
		// If, somehow, the Player reaches the destination position 
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

	// If cable is extended or retracted then m_cableAdjust is set to true and adjusts the 
	//player's position, thus adjusting the cable
	if (m_cableAdjust == true && m_hookLatched == true)
	{
		// If the Grappling Hook cable is not retracting or extending
		if (m_pulled == false && m_extend == false)
		{
			// If player is above grappling hook
			if (m_position.y < m_tempMouseVec.y + 100)
			{
				m_position.y += 10;
				
				// Right side of grappling hook
				if (m_position.x > m_tempMouseVec.x - 5)
				{
					m_position.x -= 10;
				}
				// Left side of grappling hook
				else if (m_position.x < m_tempMouseVec.x + 5)
				{
					m_position.x += 10;
				}

				m_sprite.setPosition(m_position);
			} // End if

			// If player is below grappling hook
			if (m_position.y > m_tempMouseVec.y)
			{
				
				//  Right side of grappling hook
				if (m_position.x > m_tempMouseVec.x + 8)
				{
					m_position.y += 4;
					m_position.x -= 12;
				}
				// Left side of grappling hook
				else if (m_position.x < m_tempMouseVec.x - 8)
				{
					m_position.y += 4;
					m_position.x += 12;
				}

				m_sprite.setPosition(m_position);
			}// End if
		} // End if
	}// End if

	// Sets the start and end positions; and colours of the Grappling Hooks cable
	m_grapplingLine[0].position = sf::Vector2f(m_position.x, m_position.y);
	m_grapplingLine[0].color = sf::Color::White;
	m_grapplingLine[1].position = sf::Vector2f(m_hookPosition.x, m_hookPosition.y);
	m_grapplingLine[1].color = sf::Color::White;
}

/// <summary>
/// Detects the collisions between the Player and Ground
/// </summary>
/// <param name="ground"></param>
void Player::collosionWithGround(Ground ground)
{
	if (m_sprite.getGlobalBounds().intersects(ground.getSprite().getGlobalBounds()))
	{
		m_jumping = false;
		m_falling = false;
		m_cableAdjust = false;
		m_position.y = 1350;
		m_sprite.setPosition(m_position);
	}
}

/// <summary>
/// Detects the collisions between the Grappling Hook and a Hook Point
/// </summary>
/// <param name="hookPoint"></param>
void Player::grapplePointCollision(HookPoint hookPoint)
{
	if (m_hookSprite.getGlobalBounds().intersects(hookPoint.getSprite().getGlobalBounds()) && m_fired == true)
	{
		m_hookLatched = true;
		m_falling = false;
	}
}

/// <summary>
/// Used to return a normalise vector
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
sf::Vector2f Player::normalize(sf::Vector2f vector)
{
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	m_rLength = length;

	// If calulated length is not equal to 0
	if (length != 0)
	{
		return sf::Vector2f(vector.x / length, vector.y / length);
	}

	else
	{
		return vector;
	}


	
}

/// <summary>
/// Renders and draws Grappling Hook and Player
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow& window)
{
	// If the Grappling Hook is fired
	if (m_fired == true)
	{
		// The Grappling Hook cable and...
		window.draw(m_grapplingLine, 2, sf::Lines);
		// ...hook are drawn
		window.draw(m_hookSprite);
	}

	// Draws Player Sprite
	window.draw(m_sprite);
}

/// <summary>
/// Returns the Player's current position
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPosition()
{
	return m_position;
}

/// <summary>
/// Returns the Mouse's current position
/// </summary>
/// <returns></returns>
sf::Vector2i Player::getMousePosition()
{
	return m_mousePosition;
}

/// <summary>
/// Resets the Grappling Hook in case any errors occur
/// </summary>
void Player::resetHook()
{
	// Resets Grappling Hook if the R key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_hookSprite.setPosition(m_sprite.getPosition());
		m_hookPosition = m_sprite.getPosition();
		m_hookLatched = false;
		m_fired = false;
		m_cableAdjust = false;
		m_pulled = false;
		m_extend = false;
		m_falling = true;
	}
}
