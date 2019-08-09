//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:48 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "GrapplingHook.h"

//
GrapplingHook::GrapplingHook() 
{
	initialise();
}

//
GrapplingHook::~GrapplingHook()
{
	delete this;
}

//
void GrapplingHook::loadTexture()
{
	if (!m_hookTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Hook.png"))
	{
		std::cout << "Error! Unable to load Hook.png from game files!" << std::endl;
	}
}

//
void GrapplingHook::loadAudio()
{
	//
	if (!m_firedBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Grappling_Hook_Fired.wav"))
	{
		std::cout << "Error! Unable to load Grappling_Hook_Fired.wav from game files!" << std::endl;
	}
	//
	if (!m_latchedBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Grappling_Hook_Latch.wav"))
	{
		std::cout << "Error! Unable to load Grappling_Hook_Latch.wav from game files!" << std::endl;
	}
	//
	if (!m_swingBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Rope_Swing.wav"))
	{
		std::cout << "Error! Unable to load Rope_Swing.wav from game files!" << std::endl;
	}
	//
	if (!m_extendBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Extend.wav"))
	{
		std::cout << "Error! Unable to load Extend.wav from game files!" << std::endl;
	}
	//
	if (!m_retractBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Retract.wav"))
	{
		std::cout << "Error! Unable to load Retract.wav from game files!" << std::endl;
	}
	//
	if (!m_detachBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Detach.wav"))
	{
		std::cout << "Error! Unable to load Detach.wav from game files!" << std::endl;
	}
}

//
void GrapplingHook::initialise()
{
	loadTexture();
	loadAudio();
	//
	m_hookSprite.setTexture(m_hookTexture);
	m_hookSprite.setOrigin(5, 5);
	//
	m_firedSound.setBuffer(m_firedBuffer); 
	m_latchedSound.setBuffer(m_latchedBuffer); 
	m_swingSound.setBuffer(m_swingBuffer);
	//
	m_extendSound.setBuffer(m_extendBuffer);
	m_extendSound.setVolume(115);

	m_retractSound.setBuffer(m_retractBuffer);
	m_detachSound.setBuffer(m_detachBuffer);
	//
	m_hookLatched = false;
	m_fired = false;
	m_cableAdjust = false;
	m_pulled = false;
	m_extend = false;
	m_swing = false;
	m_retractPlayed = false;
	m_extendPlayed = false;
	m_leftPlayed = false; 
	m_rightPlayed = false;
	//
	m_pullSpeed = 30;
	m_angle = 40;
	m_radius = 0;
	//
	m_angAccel = 0.0f;
	m_angVel = 0.0f;
}

//
void GrapplingHook::grapplingHook(Player* player)
{
	//
	fire(player);
	//
	detach(player);


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

	
	retract(player);
	extend(player);
	swing(player);

	// If cable is extended or retracted then m_cableAdjust is set to true and adjusts the 
	//player's position, thus adjusting the cable
	if (m_cableAdjust == true && m_hookLatched == true)
	{
		// If the Grappling Hook cable is not retracting or extending
		if (m_pulled == false && m_extend == false)
		{
			// If player is above grappling hook
			if (player->getPosition().y < m_tempMouseVec.y + 100)
			{
				m_position.y += 10;

				// Right side of grappling hook
				if (player->getPosition().x > m_tempMouseVec.x - 5)
				{
					m_position.x -= 10;
				}
				// Left side of grappling hook
				else if (player->getPosition().x < m_tempMouseVec.x + 5)
				{
					m_position.x += 10;
				}

				player->getSprite().setPosition(m_position);
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

				player->getSprite().setPosition(m_position);
			}// End if
		} // End if
	}// End if

	// Sets the start and end positions; and colours of the Grappling Hooks cable
	m_grapplingLine[0].position = sf::Vector2f(player->getPosition().x, player->getPosition().y);
	m_grapplingLine[0].color = sf::Color::White;
	m_grapplingLine[1].position = sf::Vector2f(m_hookPosition.x, m_hookPosition.y);
	m_grapplingLine[1].color = sf::Color::White;
}

//
void GrapplingHook::fire(Player * player)
{
	// Launches the Grappling Hook if the Left Mouse button is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Fires Grappling Hook only if m_fired is false
		if (m_fired == false)
		{
			// Plays Firing sound effect
			m_firedSound.play();
			// Sets the hooks position to the Player's and it's destination position to the mouse's
			m_hookSprite.setPosition(player->getSprite().getPosition());
			m_hookPosition = player->getSprite().getPosition();
			m_tempMouseVec = m_mouseVector;

			m_fired = true;
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
		if (m_hookPosition.x >= m_tempMouseVec.x - 10 &&
			m_hookPosition.x <= m_tempMouseVec.x + 10 &&
			m_hookPosition.y >= m_tempMouseVec.y - 10 &&
			m_hookPosition.y <= m_tempMouseVec.y + 10 &&
			m_hookLatched == false)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_extend = false;
		}// End if
	}// End if
}

//
void GrapplingHook::detach(Player * player)
{
	// Detaches the Grappling Hook if the Right Mouse button is pressed...
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//...but only if Grappling Hook is latched onto a Hook Point
		if (m_hookLatched == true)
		{
			// Plays detach sound effect
			m_detachSound.play();

			m_hookSprite.setPosition(player->getSprite().getPosition());
			m_hookPosition = player->getSprite().getPosition();
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			m_extend = false;
			player->setFalling(true);
		}
	}
}

//
void GrapplingHook::extend(Player * player)
{
	// The S key is pressed to extend the grappling hook
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_hookLatched == true)
	{
		if (m_extendPlayed == false)
		{
			// Plays extend sound effect
			m_extendSound.play();
			m_extendPlayed = true;
		}

		m_extend = true;
		m_cableAdjust = true;
		// While is uses the same variable, the extend direction is acquired by 
		//normalising the player position minus the destination position
		m_pullDirection = normalize(m_position - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;

		m_position.x += m_pullDirection.x * m_pullSpeed;
		m_position.y += m_pullDirection.y * m_pullSpeed;
		player->setPosition(m_position);
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
		// Stops playing sound effect
		m_extendSound.stop();

		m_extend = false;
		m_extendPlayed = false;
	}
}

//
void GrapplingHook::retract(Player * player)
{
	// The W key is press to retract the grappling hook
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_hookLatched == true)
	{
		if (m_retractPlayed == false)
		{
			// Plays retract sound effect
			m_retractSound.play();
			m_retractPlayed = true;
		}

		// Pull and cable adjust are true
		m_pulled = true;
		m_cableAdjust = true;
		// The pull direction is acquired by normalising the player position minus the destination
		// position
		m_pullDirection = normalize(player->getPosition() - m_tempMouseVec);
		m_directionX = m_pullDirection.x;
		m_directionY = m_pullDirection.y;
		// The new Player's is found and set, making it look as though the Grappling Hook is 
		// pulling them towards their destination
		m_position.x -= m_pullDirection.x * m_pullSpeed;
		m_position.y -= m_pullDirection.y * m_pullSpeed;
		player->setPosition(m_position);
		// If the Player reaches the destination position, Grappling Hook is reset and 
		// Player is set to fall
		if (player->getPosition().x >= m_tempMouseVec.x - 20 &&
			player->getPosition().x <= m_tempMouseVec.x + 20 &&
			player->getPosition().y >= m_tempMouseVec.y - 20 &&
			player->getPosition().y <= m_tempMouseVec.y + 20)
		{
			m_hookLatched = false;
			m_fired = false;
			m_cableAdjust = false;
			m_pulled = false;
			player->setFalling(true);
		}// End if
	}// End if
	// Else if W key is not pressed
	else
	{
		// Stops playing sound effect
		m_retractSound.stop();

		m_pulled = false;
		m_retractPlayed = false;
	}
}

//
void GrapplingHook::swing(Player * player)
{
	//
	if (m_hookLatched == true)
	{

		//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//
			if (m_rightPlayed == false)
			{ 
				// Plays swing sound effect
				m_swingSound.play();
				m_rightPlayed = true;
				//m_radius = player->getPosition().y - m_tempMouseVec.y;
			}
			m_swing = true;
		}

		//
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//
			if (m_leftPlayed == false)
			{
				m_swingSound.play();
				m_leftPlayed = true;
			}
			m_swing = true;

		}

		//
		else
		{
			// Stops playing sound effect
			m_swingSound.stop();

			m_leftPlayed = false;
			m_rightPlayed = false;
		}

		//
		if (m_swing == true)
		{
			m_angAccel = -0.01 * sin(m_angle);

			m_angle += m_angVel;
			m_angVel += m_angAccel;

			m_angVel *= 0.99;

			m_position.x += m_tempMouseVec.x + m_radius * sin(m_angle);
			m_position.y += m_tempMouseVec.y + m_radius * cos(m_angle);
			player->setPosition(m_position);
		}
	}
}

//
void GrapplingHook::update(Player* player, sf::Vector2f mouse)
{
	m_mouseVector = mouse;

	grapplingHook(player);
	resetHook(player);

	m_position = player->getPosition();
	m_radius = player->getPosition().y - m_tempMouseVec.y;
}

/// <summary>
/// Detects the collisions between the Grappling Hook and a Hook Point
/// </summary>
/// <param name="hookPoint"></param>
void GrapplingHook::grapplePointCollision(Player *player, HookPoint hookPoint)
{
	// If the Grappling Hook Sprite intersects with any Hook Point Sprite
	if (m_hookSprite.getGlobalBounds().intersects(hookPoint.getSprite().getGlobalBounds()) && m_fired == true)
	{
		m_hookLatched = true;
		player->setFalling(false);
	}
}

//
void GrapplingHook::draw(sf::RenderWindow& window)
{
	if (m_fired == true)
	{
		// The Grappling Hook cable and...
		window.draw(m_grapplingLine, 2, sf::Lines);
		// ...hook are drawn
		window.draw(m_hookSprite);
	}
}

/// <summary>
/// Used to return a normalise vector
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
sf::Vector2f GrapplingHook::normalize(sf::Vector2f vector)
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
/// Resets the Grappling Hook in case any errors occur
/// </summary>
void GrapplingHook::resetHook(Player* player)
{
	// Resets Grappling Hook if the R key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_fired == true)
	{
		if (m_hookLatched == true)
		{
			// Plays detach sound effect
			m_detachSound.play();
		}

		m_hookSprite.setPosition(player->getSprite().getPosition());
		m_hookPosition = player->getSprite().getPosition();
		m_hookLatched = false;
		m_fired = false;
		m_cableAdjust = false;
		m_pulled = false;
		m_extend = false;
		player->setFalling(true);
	}
}

//
bool GrapplingHook::getHookLatched()
{
	return m_hookLatched;
}