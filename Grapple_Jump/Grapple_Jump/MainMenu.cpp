//
// C00204076
// Brandon Seah-Dempsey
// Started at 12:09 1 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "MainMenu.h"

//
MainMenu::MainMenu()
{
	initialise();
}

//
MainMenu::~MainMenu()
{

}

//
void MainMenu::initialise()
{
	loadTexture();
	//
	m_alpha = 255;
	//
	m_flashOut = true;
	m_flashIn = false;
	//
	m_playTime = false;

	//
	m_titlePosition = sf::Vector2f(750, 250);

	//
	m_titleSprite.setTexture(m_titleTexture);
	m_playSprite.setTexture(m_playTexture);
	m_quitSprite.setTexture(m_quitTexture);
	//
	m_titleSprite.setOrigin(sf::Vector2f(302.5f, 140.0f));
	m_playSprite.setOrigin(sf::Vector2f(66.5f, 19.0f));
	m_quitSprite.setOrigin(sf::Vector2f(66.5f, 19.0f));
	//
	m_titleSprite.setPosition(m_titlePosition);
	m_playSprite.setPosition(sf::Vector2f(750, 550));
	m_quitSprite.setPosition(sf::Vector2f(750, 750));
	
}

//
void MainMenu::loadTexture()
{
	if (!m_titleTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Main-Menu.png"))
	{
		std::cout << "Error! Unable to load Main-Menu.png from game files!" << std::endl;
	}

	if (!m_playTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Play.png"))
	{
		std::cout << "Error! Unable to load Play.png from game files!" << std::endl;
	}

	if (!m_quitTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Quit.png"))
	{
		std::cout << "Error! Unable to load Quit.png from game files!" << std::endl;
	}
}

//
void MainMenu::update(sf::Time deltaTime, Player * player, sf::RenderWindow& window)
{
	
	//
	if (m_playSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		changeButtonColour();
		//
		m_playSprite.setScale(sf::Vector2f(2.0f, 2.0f));
		//
		m_quitSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_playSprite.setColor(sf::Color(255, 255, 255, m_alpha));

		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_playTime = true;
		}
	}
	//
	else if (m_quitSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		changeButtonColour();
		//
		m_playSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_quitSprite.setScale(sf::Vector2f(2.0f, 2.0f));
		//
		m_quitSprite.setColor(sf::Color(255, 255, 255, m_alpha));

		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
	}
	else
	{
		//
		m_alpha = 255;
		//
		m_playSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_quitSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_playSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_quitSprite.setColor(sf::Color(255, 255, 255, m_alpha));
	}
}

//
void MainMenu::changeButtonColour()
{
	//
	if (m_alpha >= 255)
	{
		m_flashOut = true;
		m_flashIn = false;
	}
	else if (m_alpha <= 0)
	{
		m_flashOut = false;
		m_flashIn = true;
	}

	//
	if (m_flashIn == true)
	{
		m_alpha += 3;
	}

	//
	if (m_flashOut == true)
	{
		m_alpha -= 3;
	}
}

//
void MainMenu::render(sf::RenderWindow& window)
{
	//
	window.draw(m_titleSprite);
	//
	window.draw(m_playSprite);
	//
	window.draw(m_quitSprite);
}

//
bool MainMenu::getPlayTime()
{
	return m_playTime;
}

//
void MainMenu::setPlayTime(bool playTime)
{
	m_playTime = playTime;
}