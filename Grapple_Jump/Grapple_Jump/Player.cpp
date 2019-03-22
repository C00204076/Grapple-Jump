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
	initialise();

	//
	/*dynamicBody = m_world->CreateBody(&m_dynamicBody);


	circleShape.m_p.Set(m_position.x, m_position.y);
	circleShape.m_radius = 1;

	m_fixture.shape = &circleShape;*/


}

//
Player::~Player()
{

}

//
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
	m_pullSpeed = 0.5f;

	//m_world = b2World(new b2Vec2(0, 10), true);

	m_jumping = false;
	m_left = false;
	m_right = true;
}

//
/*b2Body Player::addBox()
{
	//
	b2BodyDef m_bodyDef = b2BodyDef();
	m_bodyDef.position.Set(2600, 1600);
	//m_bodyDef.type = m_bodyType;
	//
	b2PolygonShape m_polygonShape = b2PolygonShape();
	m_polygonShape.SetAsBox(2600, 1600);
	//
	b2FixtureDef m_fixtureDef = b2FixtureDef();
	m_fixtureDef.shape = m_polygonShape;
	m_fixtureDef.density = 1;
	m_fixtureDef.restitution = 0.4;
	m_fixtureDef.friction = 0.5;
	//
	b2Body m_body = m_world.CreateBody(m_bodyDef);
	m_playerBody.CreateFixture(m_fixtureDef);

	return m_body;
}*/

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

		/*m_grapplingLine[0].position = sf::Vector2f(m_position.x, m_position.y);
		m_grapplingLine[0].color = sf::Color::White;
		m_grapplingLine[1].position = sf::Vector2f(m_mouseX, m_mouseY);
		m_grapplingLine[1].color = sf::Color::White;
		*/
		
		//m_pullDirection = 

		/*m_position.x = m_mouseX;
		m_position.y = m_mouseY;

		m_jumping = true;*/
	}

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

		m_velocity.y = -250;
		m_jumping = true;
	}

	//
	if (m_jumping == true)
	{
		m_velocity.y -= m_gravity.y;
		m_position.y = m_position.y + ((m_velocity.y * deltaTime.asSeconds()) + (0.5 * m_gravity.y) * (deltaTime.asSeconds() * deltaTime.asSeconds()));
		//m_position.y = m_position.y + ((m_velocity.y * deltaTime.asSeconds()) + (0.5 * m_gravity.y) * (deltaTime.asSeconds() * deltaTime.asSeconds()));
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
		m_jumping = true;
	}
}

//
void Player::render(sf::RenderWindow& window)
{
	//window.draw(m_grapplingLine, 2, sf::Lines);
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
