//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:25 29 August 2019
// Finished at 
// Time Taken: 
// Known Bugs:

#include "LoadingScreen.h"

//
Loading::Loading()
{
	initialise();
}

//
Loading::~Loading()
{

}

//
void Loading::initialise()
{
	loadTexture();
	loadFont();

	//
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(750, 450));
	m_sprite.setOrigin(50, 50);

	//
	m_levelText.setFont(m_font);
	m_levelText.setCharacterSize(72);
	m_levelText.setFillColor(sf::Color::White);
	m_levelText.setPosition(sf::Vector2f(450.0f, 140.0f));
	m_levelText.setStyle(sf::Text::Bold);

	//
	m_timer = 0;
	m_angle = 0;
	m_alpha = 255;
	//
	m_play = false;
	m_mainMenu = false;
	m_gameOver = false;
	m_flashOut = true;
	m_flashIn = false;
}

//
void Loading::loadTexture()
{
	if (!m_texture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Player.png"))
	{
		std::cout << "Error! Unable to load Player.png from game files!" << std::endl;
	}
}

//
void Loading::loadFont()
{
	if (!m_font.loadFromFile("../Grapple_Jump/ASSETS/FONTS/corbel.ttf"))
	{
		std::cout << "Error! Unable to load corbel.ttf from game files!" << std::endl;
	}
}

//
void Loading::update(sf::Time deltaTime, sf::View & v)
{
	m_timer++;
	m_angle += 5;


	m_sprite.setRotation(m_angle);

	setTextMessage();
	juicyText();

	//
	if (m_angle > 360)
	{
		m_angle = 0;
	}
	//
	else if (m_angle < 0)
	{
		m_angle = 360;
	}

	
	v.setCenter(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

//
void Loading::setTextMessage()
{
	//
	if (m_play == true)
	{
		m_levelText.setString("Loading Game Level");
		//m_levelText.setPosition(sf::Vector2f(450.0f, 140.0f));
	}

	//
	else if (m_mainMenu == true)
	{
		m_levelText.setString("Loading Main Menu");
		//m_levelText.setPosition(sf::Vector2f(450.0f, 140.0f));
	}

	//
	else if (m_gameOver == true)
	{
		m_levelText.setString("Loading Game Over");
		//m_levelText.setPosition(sf::Vector2f(450.0f, 140.0f));
	}
}

//
void Loading::juicyText()
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

	m_levelText.setFillColor(sf::Color(255, 255, 255, m_alpha));
}

//
void Loading::render(sf::RenderWindow& window)
{
	//
	window.draw(m_levelText);
	//
	window.draw(m_sprite);
}

//
int Loading::getTimer()
{
	return m_timer;
}

//
void Loading::setTimer(int timer)
{
	m_timer = timer;
}

//
bool Loading::getPlay()
{
	return m_play;
}

//
void Loading::setPlay(bool play)
{
	m_play = play;
}

//
bool Loading::getMainMenu() 
{
	return m_mainMenu;
}

//
void Loading::setMainMenu(bool mainMenu)
{
	m_mainMenu = mainMenu;
}

//
bool Loading::getGameOver()
{
	return m_gameOver;
}

//
void Loading::setGameOver(bool gameOver)
{
	m_gameOver = gameOver;
}