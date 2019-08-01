//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:27 1 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "LicenseScreen.h"

//
License::License()
{
	initialise();
}

//
License::~License()
{

}

//
void License::initialise()
{
	loadTexture();

	//
	m_alpha = 0.0f;

	//
	m_fadeIn = false;
	m_fadeOut = false;

	//
	m_sprite.setTexture(m_texture);
	//
	m_sprite.setOrigin(sf::Vector2f(500.5f, 161.5f));
	//
	m_sprite.setPosition(750, 450);
	//
	m_sprite.setColor(sf::Color(255, 255, 255, m_alpha));
}

//
void License::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/License.png"))
	{
		std::cout << "Error! Unable to load License.png from game files!" << std::endl;
	}
}

//
void License::update(sf::Time deltaTime)
{
	//
	if (m_fadeIn == false & m_fadeOut == false)
	{
		m_alpha += 1;

		if (m_alpha >= 255)
		{
			m_fadeIn = true;
		}
	}
	//
	else if(m_fadeIn == true & m_fadeOut == false)
	{
		m_alpha -= 1;

		if (m_alpha < 0)
		{
			m_fadeOut = true;
			m_fadeIn = false;
			m_alpha = 0;
		}
	}
	//
	if (m_fadeOut == true)
	{
		m_screenTime = 1.0;
	}

	//
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_screenTime = 1.0;
	}

	m_sprite.setColor(sf::Color(255, 255, 255, m_alpha));
}

//
void License::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//
float License::getScreenTime()
{
	return m_screenTime;
}