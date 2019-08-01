//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:27 1 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "SplashScreen.h"

//
Splash::Splash()
{
	initialise();
}

//
Splash::~Splash()
{

}

//
void Splash::initialise()
{
	loadTexture();
	//
	m_screenTime = 0;
	//
	m_sprite.setTexture(m_texture);
	//
	m_sprite.setOrigin(sf::Vector2f(375.5f, 152.0f));
	//
	m_sprite.setPosition(750, 450);
	//
	m_sprite.setScale(0.01f, 0.01f);
	//
	m_scaleX = 0.01f;
	m_scaleY = 0.01f;
}

//
void Splash::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Splash.png"))
	{
		std::cout << "Error! Unable to load Splash.png from game files!" << std::endl;
	}
}

//
void Splash::update(sf::Time deltaTime)
{
	if (m_scaleX < 1.0f && m_scaleY < 1.0f)
	{
		m_scaleX += 0.01f;
		m_scaleY += 0.01f;

		m_sprite.setScale(m_scaleX, m_scaleY);
	}
	else
	{
		m_screenTime += 0.01;
	}

	//
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_screenTime = 1.0;
	}
}

//
void Splash::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//
float Splash::getScreenTime()
{
	return m_screenTime;
}