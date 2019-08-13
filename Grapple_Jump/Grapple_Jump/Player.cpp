// Sets the methods, functions and changes of the variables related to Player header file
// C00204076
// Brandon Seah-Dempsey
// Started at 10:39 7 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 6 hours 24 minutes
// Known Bugs: Grappling Hook may get stuck in place if it is not 
// latched onto a Hook Point

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
	//
	if (!m_idleRightText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-idle(right-small).png"))
	{
		std::cout << "Error! Unable to load Player-idle(right-small).png from game files!" << std::endl;
	}
	//
	if (!m_idleLeftText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-idle(left-small).png"))
	{
		std::cout << "Error! Unable to load Player-idle(left-small).png from game files!" << std::endl;
	}
	//
	if (!m_idleRightTextTwo.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-idle(right-small-2).png"))
	{
		std::cout << "Error! Unable to load Player-idle(right-small-2).png from game files!" << std::endl;
	}
	//
	if (!m_idleLeftTextTwo.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-idle(left-small-2).png"))
	{
		std::cout << "Error! Unable to load Player-idle(left-small-2).png from game files!" << std::endl;
	}
	//

	//
	if (!m_moveRightText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-move(right-small).png"))
	{
		std::cout << "Error! Unable to load Player-move(right-small).png from game files!" << std::endl;
	}
	//
	if (!m_moveLeftText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-move(left-small).png"))
	{
		std::cout << "Error! Unable to load Player-move(left-small).png from game files!" << std::endl;
	}
	//

	//
	/*if (!m_jumpRightText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-preparing-to-jump(right-small).png"))
	{
		std::cout << "Error! Unable to load Player-preparing-to-jump(right-small).png from game files!" << std::endl;
	}
	//
	if (!m_jumpLeftText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-preparing-to-jump(left-small).png"))
	{
		std::cout << "Error! Unable to load Player-preparing-to-jump(left-small).png from game files!" << std::endl;
	}*/
	//
	if (!m_jumpRightText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-jumping(right-small).png"))
	{
		std::cout << "Error! Unable to load Player-jumping(right-small).png from game files!" << std::endl;
	}
	//
	if (!m_jumpLeftText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-jumping(left-small).png"))
	{
		std::cout << "Error! Unable to load Player-jumping(left-small).png from game files!" << std::endl;
	}
	//

	//
	if (!m_landRightText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-landing(right-small).png"))
	{
		std::cout << "Error! Unable to load Player-landing(right-small).png from game files!" << std::endl;
	}
	//
	if (!m_landLeftText.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Spritesheets/Player-landing(left-small).png"))
	{
		std::cout << "Error! Unable to load Player-landing(left-small).png from game files!" << std::endl;
	}
	//

	//
}

//
void Player::loadAudio()
{
	//
	if (!m_jumpBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Jump.wav"))
	{
		std::cout << "Error! Unable to load Jump.wav from game files!" << std::endl;
	}
	//
	if (!m_landBuffer.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Landing.wav"))
	{
		std::cout << "Error! Unable to load Landing.wav from game files!" << std::endl;
	}
}

/// <summary>
/// Initialises Player and Grappling Hook variables
/// </summary>
void Player::initialise()
{
	loadTextures();
	loadAudio();

	m_fsm = new Animation();
	m_grapplinghook = new GrapplingHook();

	m_gravity = sf::Vector2f(0, 4.0f);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	// Vector2f = (100, 700) for at home work
	m_position = sf::Vector2f(100, 700);//1300);
	m_sourceRectSprite = sf::IntRect(1, 4, 75, 75);

	m_sprite.setTextureRect(m_sourceRectSprite);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(50, 50);
	//
	m_jumpSound.setBuffer(m_jumpBuffer);
	m_landSound.setBuffer(m_landBuffer);

	m_AABB = new AABB(m_position.x, m_position.y, m_sourceRectSprite.width, m_sourceRectSprite.height);

	
	m_ranNumber = 1;
	m_jumpPrep = 0;
	m_maxLength = 500.0f;

	m_moving = false;
	m_jumping = false;
	m_jump = false;
	m_falling = true;
	m_left = false;
	m_right = true;
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Player::update(sf::Time deltaTime, sf::View & v, bool grapple)
{
	m_fsm->update(this);
	//
	if (grapple == true)
	{
		m_grapplinghook->update(this, m_mouseVector);
	}

	movePlayer();
	jump(deltaTime);
	//boundaryCheck();
	changeSpriteSheet();

	v.setCenter(m_sprite.getPosition());
}

//
void Player::mouseCursor(sf::RenderWindow& window, sf::View & v)
{
	// Gets the current position of the mouse cursor, relative to the game window
	m_mousePosition = sf::Mouse::getPosition(window);
	// Set the mouse X and Y to floats, then to Vector2f; as a means of converting Vector2i
	// to Vector2f
	m_mouseX = m_mousePosition.x;
	m_mouseY = m_mousePosition.y;
	m_mouseVector = window.mapPixelToCoords(m_mousePosition, v);
	//m_mouseVector = sf::Vector2f(m_mouseX, m_mouseY);
}

/// <summary>
/// Method used to allow Player to move left or right using a key input
/// </summary>
void Player::movePlayer()
{
	//
	if (m_grapplinghook->getHookLatched() == false)
	{

		// If the A key is pressed and the Player is is jumping, not falling and  the
		// Grappling Hook cable is adjusting itself
		if (m_keyboard.isKeyPressed(sf::Keyboard::A))// && (m_cableAdjust == false))
		{
			m_left = true;
			m_right = false;

			//
			if (m_jumping == false)
			{
				m_moving = true;
			} // End if
			//
			else
			{
				m_moving = false;
			} // End if

			m_position.x -= 7;

			m_sprite.setPosition(m_position);
		} // End if

		// If the D key is pressed and the Player is is jumping, not falling and  the
		// Grappling Hook cable is adjusting itself
		else if (m_keyboard.isKeyPressed(sf::Keyboard::D))// && (m_cableAdjust == false))
		{
			m_left = false;
			m_right = true;

			//
			if (m_jumping == false)
			{
				m_moving = true;
			} // End if
			//
			else
			{
				m_moving = false;
			} // End if

			m_position.x += 7;

			m_sprite.setPosition(m_position);
		} // End if
		//
		else
		{
			m_moving = false;
		} //End if
	} // End if
}

/// <summary>
/// Method used to allow Player to jump using a key input
/// </summary>
/// <param name="deltaTime"></param>
void Player::jump(sf::Time deltaTime)
{
	// If Space key is pressed and Grappling Hook is not latched onto a Hook Point
	if (m_keyboard.isKeyPressed(sf::Keyboard::Space) && m_jumping == false && m_grapplinghook->getHookLatched() == false)
	{
		//
		m_jumpSound.play();
		// Gets the max jumping height using the Player position
		m_maxLength = m_position.y - 450;

		m_jumping = true;
		//m_cableAdjust = true;
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
		m_position.y += 15;

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
/// Detects the collisions between the Player and Ground
/// </summary>
/// <param name="ground"></param>
void Player::collosionWithGround(Ground * ground)
{
	// If the Player Sprite intersects with the Ground Sprite
	/*if (m_sprite.getGlobalBounds().intersects(ground->getSprite().getGlobalBounds()))
	{
		//m_landSound.play();
		m_jumping = false;
		m_falling = false;
		//m_cableAdjust = false;
		//m_position.y = ground->getPosition().y - 25;
		//m_sprite.setPosition(m_position);

		
		//m_falling = false;
		//m_cableAdjust = false;
		//m_position.y = ground->getPosition().y - 25;
		

		//
		if (m_sprite.getGlobalBounds().intersects(ground->getTopBoundingBox().getGlobalBounds()))
		{
			m_falling = false;
			m_position.y = ground->getPosition().y - 26;
		}

		//
		else if (m_sprite.getGlobalBounds().intersects(ground->getBottomBoundingBox().getGlobalBounds()))
		{
			m_position.y = ground->getPosition().y + 26;
		}

		//
		else if (m_sprite.getGlobalBounds().intersects(ground->getLeftBoundingBox().getGlobalBounds()))
		{
			m_position.x = ground->getPosition().x - 26;
		}

		//
		else if (m_sprite.getGlobalBounds().intersects(ground->getRightBoundingBox().getGlobalBounds()))
		{
			m_position.x = ground->getPosition().x + 80;
		}

		m_sprite.setPosition(m_position);
		
		
	}*/

	//
	if (m_sprite.getGlobalBounds().intersects(ground->getTopBoundingBox().getGlobalBounds()))
	{
		if (m_sprite.getGlobalBounds().intersects(ground->getSprite().getGlobalBounds()))
		{
			m_landSound.play();
			m_falling = false;
			m_position.y = ground->getPosition().y - 26;
		}
	}

	//
	else if (m_sprite.getGlobalBounds().intersects(ground->getBottomBoundingBox().getGlobalBounds()))
	{
		if (m_sprite.getGlobalBounds().intersects(ground->getSprite().getGlobalBounds()))
		{
			m_position.y = ground->getPosition().y + (26 * ground->getScaleY());
		}
	}

	//
	else if (m_sprite.getGlobalBounds().intersects(ground->getLeftBoundingBox().getGlobalBounds()))
	{
		if (m_sprite.getGlobalBounds().intersects(ground->getSprite().getGlobalBounds()))
		{
			m_position.x = ground->getPosition().x - 22;
		}
	}

	//
	else if (m_sprite.getGlobalBounds().intersects(ground->getRightBoundingBox().getGlobalBounds()))
	{
		if (m_sprite.getGlobalBounds().intersects(ground->getSprite().getGlobalBounds()))
		{
			m_position.x = ground->getPosition().x + (100 * ground->getScaleX());
		}
	}

	m_sprite.setPosition(m_position);
}

/// <summary>
/// Detects the collisions between the Grappling Hook and a Hook Point
/// </summary>
/// <param name="hookPoint"></param>
void Player::grapplePointCollision(HookPoint hookPoint)
{
	m_grapplinghook->grapplePointCollision(this, hookPoint);
}

//
void Player::checkAABBCollision(AABB * other)
{
	bool collision = false;

	/*if (m_position.x < other->getX() + other->getWidth() &&
		m_position.x + m_AABB->getWidth() > other->getWidth() &&
		m_position.y + m_AABB->getHeight() > other->getY() &&
		m_position.y > other->getY() + other->getHeight())
	{
		std::cout << "AABB Collision!" << std::endl;
	}*/

	//
	float w = (m_AABB->getWidth() + other->getWidth()) / 2.0;
	float h = (m_AABB->getHeight() + other->getHeight()) / 2.0;
	//
	float dx = (m_position.x + (m_AABB->getWidth() / 2.0)) - (other->getX() + (other->getWidth() / 2.0));
	float dy = (m_position.y + (m_AABB->getHeight() / 2.0)) - (other->getY() + (other->getHeight() / 2.0));
	//
	float diff = 0;
	
	//
	if (abs(dx) <= w && abs(dy) <= h)
	{
		//
		collision = true;
		//
		float wy = w * dy;
		float hx = h * dx;

		//
		if (wy < hx)
		{
			// Check collision at right axis of other
			/*if (wy < -hx)
			{
				float diff = abs(m_position.x - (other->getX() + other->getWidth()));
				//m_position.x = diff;
			}*/

			// Check collision at top axis of other
			if (wy > -hx)
			{
				if (m_falling == true)
				{
					m_landSound.play();
					float diff = abs((m_position.y + m_AABB->getHeight()) - other->getY());
					m_position.y -= diff * 1.1;
					m_sprite.setPosition(m_position);
					m_falling = false;
				}
			}

			else 
			{
				m_falling = true;
				m_landSound.stop();
			}
		}

		/*else if (wy > hx)
		{
			// Check collision at bottom axis of other
 			if (wy > -hx)
			{
				//diff = abs(m_position.y - (other->getY() + other->getHeight()));
				//m_position.y += diff;
			}

			// Check collision at left axis of other
			else
			{
				float diff = abs((m_position.x + m_AABB->getWidth()) - other->getX());
				//m_position.x -= diff;
			}
		}*/	
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

//
void Player::changeSpriteSheet()
{
	//
	if (m_left == true && m_right == false)
	{
		//
		if (m_moving == false)
		{
			//
			if (m_ranNumber == 1)
			{
				m_sprite.setTexture(m_idleLeftText);
			}
			//
			if (m_ranNumber == 2)
			{
				m_sprite.setTexture(m_idleLeftTextTwo);
			}
		}

		//
		else if (m_moving == true)
		{
			m_sprite.setTexture(m_moveLeftText);
		}

		//
		if (m_jumping == true)
		{
			m_sprite.setTexture(m_jumpLeftText);
		}

		//
		else if (m_falling == true)
		{
			m_sprite.setTexture(m_landLeftText);
		}

		//
		else if (m_landing == true)
		{

		}
	}

	//
	else if (m_left == false && m_right == true)
	{
		//
		if (m_moving == false)
		{
			//
			if (m_ranNumber == 1)
			{
				m_sprite.setTexture(m_idleRightText);
			}
			//
			else if (m_ranNumber == 2)
			{
				m_sprite.setTexture(m_idleRightTextTwo);
			}
		}

		//
		else if (m_moving == true)
		{
			m_sprite.setTexture(m_moveRightText);
		}

		//
		if (m_jumping == true)
		{
			m_sprite.setTexture(m_jumpRightText);
		}

		//
		else if (m_falling == true)
		{
			m_sprite.setTexture(m_landRightText);
		}

		//
		else if (m_landing == true)
		{

		}
	}
}

/// <summary>
/// Renders and draws Grappling Hook and Player
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow& window, sf::Vector2f scale)
{
	m_grapplinghook->draw(window);

	//
	m_sprite.setScale(scale);
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
sf::Vector2f Player::getMousePosition()
{
	return m_mouseVector;
}

//
sf::Sprite Player::getSprite()
{
	return m_sprite;
}

//
bool Player::getLeft()
{
	return m_left;
}

//
bool Player::getRight()
{
	return m_right;
}

//
bool Player::getMoving()
{
	return m_moving;
}

//
bool Player::getJumping()
{
	return m_jumping;
}

//
bool Player::getFalling()
{
	return m_falling;
}

//
AABB * Player::getAABB()
{
	return m_AABB;
}

//
void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//
void Player::setTexture(sf::Texture texture)
{
	m_sprite.setTexture(texture);
}

//
sf::IntRect Player::getSourceRectSprite() 
{
	return m_sourceRectSprite;
}

//
void Player::setSourceRectSprite(sf::IntRect rectangle)
{
	m_sourceRectSprite = rectangle;
	m_sprite.setTextureRect(m_sourceRectSprite);
}

//
void Player::setFalling(bool falling)
{
	m_falling = falling;
}


