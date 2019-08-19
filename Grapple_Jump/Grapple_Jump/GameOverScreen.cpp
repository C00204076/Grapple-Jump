//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:06 19 August 2019
// Finished at 
// Time Taken: 
// Known Bugs:

#include "GameOverScreen.h"

//
GameOver::GameOver()
{
	initialise();
}

//
GameOver::~GameOver()
{

}

//
void GameOver::initialise()
{
	loadTexture();
	loadAudio();

	//
	m_alpha = 255;
	m_titleAlpha = 255;
	//
	m_titlePosition = sf::Vector2f(750, 250);
	m_titleX = m_titlePosition.x;
	m_titleY = m_titlePosition.y;
	//
	m_flashOut = true;
	m_flashIn = false;
	m_flashTitleIn = false;
	m_flashTitleOut = true;
	m_moveUp = false;
	m_moveDown = true;
	//
	m_playTime = false;
	m_mainMenu = false;
	m_win = false;
	m_lose = true;
	m_playTrack = true;

	//
	m_titlePosition = sf::Vector2f(750, 200);
	m_titleX = m_titlePosition.x;
	m_titleY = m_titlePosition.y;
	//
	//m_titleSprite.setTexture(m_titleTexture);
	m_replaySprite.setTexture(m_replayTexture);
	m_mainSprite.setTexture(m_mainTexture);
	m_quitSprite.setTexture(m_quitTexture);
	//
	//m_titleSprite.setOrigin(sf::Vector2f(302.5f, 140.0f));
	m_replaySprite.setOrigin(sf::Vector2f(81.5f, 27.0f));
	m_mainSprite.setOrigin(sf::Vector2f(264.5f, 21.0f));
	m_quitSprite.setOrigin(sf::Vector2f(59.5f, 22.5f));
	//
	//m_titleSprite.setPosition(m_titlePosition);
	m_replaySprite.setPosition(sf::Vector2f(750, 550));
	m_mainSprite.setPosition(sf::Vector2f(750, 675));
	m_quitSprite.setPosition(sf::Vector2f(750, 800));
	//
	//
	m_replaySprite.setScale(sf::Vector2f(0.75f, 0.75f));
	m_mainSprite.setScale(sf::Vector2f(0.75f, 0.75f));
	m_quitSprite.setScale(sf::Vector2f(0.75f, 0.75f));

	//
	m_btnClick.setBuffer(m_buttonClick);
	m_btnCollide.setBuffer(m_buttonCollide);
}

//
void GameOver::loadTexture()
{
	if (!m_titleTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Gameover.png"))
	{
		std::cout << "Error! Unable to load Gameover.png from game files!" << std::endl;
	}

	if (!m_titleTwoTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/You_win.png"))
	{
		std::cout << "Error! Unable to load You_win.png from game files!" << std::endl;
	}

	if (!m_mainTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Return_To_Title.png"))
	{
		std::cout << "Error! Unable to load Return_To_Title.png from game files!" << std::endl;
	}

	if (!m_replayTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Replay.png"))
	{
		std::cout << "Error! Unable to load Play.png from game files!" << std::endl;
	}

	if (!m_quitTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Quit_Gameover.png"))
	{
		std::cout << "Error! Unable to load Quit_Gameover.png from game files!" << std::endl;
	}

	
}

//
void GameOver::loadAudio()
{
	//
	if (!m_buttonClick.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Click_On.wav"))
	{
		std::cout << "Error! Unable to load Click_On.wav from game files!" << std::endl;
	}

	//
	//
	if (!m_buttonCollide.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Click_2.wav"))
	{
		std::cout << "Error! Unable to load Click_2.wav from game files!" << std::endl;
	}
}

//
void GameOver::update(sf::Time deltaTime, Player * player, sf::RenderWindow& window, MusicManager * music, sf::View & v)
{
	//
	setTitle(music);
	juicyGameOverTitle();
	mouseButtonInteraction(player, window, music);

	v.setCenter(750.0f, 450.0f);
}

//
void GameOver::mouseButtonInteraction(Player * player, sf::RenderWindow& window, MusicManager * music)
{
	//
	if (m_replaySprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		if (m_playReplay == true)
		{
			//
			m_btnCollide.play();
			//
			m_playReplay = false;
		}
		//
		m_playMain = true;
		m_playQuit = true;

		//
		changeButtonColour();
		
		//
		m_replaySprite.setScale(sf::Vector2f(1.50f, 1.50f));
		//
		m_mainSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_quitSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_replaySprite.setColor(sf::Color(255, 255, 255, m_alpha));


		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//
			m_btnClick.play();
			//
			m_playTime = true;
		}
	}
	//
	else if (m_mainSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		if (m_playMain == true)
		{
			//
			m_btnCollide.play();
			//
			m_playMain = false;
		}
		//
		m_playReplay = true;
		m_playQuit = true;


		//
		changeButtonColour();
		
		//
		m_replaySprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_mainSprite.setScale(sf::Vector2f(1.50f, 1.50f));
		//
		m_quitSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_mainSprite.setColor(sf::Color(255, 255, 255, m_alpha));

		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//
			m_btnClick.play();
			//
			m_mainMenu = true;
		}
	}
	//
	else if (m_quitSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		if (m_playQuit == true)
		{
			//
			m_btnCollide.play();
			//
			m_playQuit = false;
		}
		//
		m_playMain = true;
		m_playReplay = true;


		//
		changeButtonColour();
		
		//
		m_replaySprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_mainSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_quitSprite.setScale(sf::Vector2f(1.50f, 1.50f));
		//
		m_replaySprite.setColor(sf::Color(255, 255, 255, m_alpha));

		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//
			m_btnClick.play();
			//
			window.close();
		}
	}
	//
	else
	{
		//
		m_playMain = true;
		m_playReplay = true;
		m_playQuit = true;

		//
		m_alpha = 255;
		//
		m_replaySprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_mainSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		//
		m_quitSprite.setScale(sf::Vector2f(0.75f, 0.75f));
		

		//
		m_replaySprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_mainSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_quitSprite.setColor(sf::Color(255, 255, 255, m_alpha));
	}
}

//
void GameOver::changeButtonColour()
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
void GameOver::juicyGameOverTitle()
{
	//
	if (m_titleY >= m_titlePosition.y + 10)
	{
		m_moveUp = true;
		m_moveDown = false;
	}
	else if (m_titleY <= m_titlePosition.y - 10)
	{
		m_moveUp = false;
		m_moveDown = true;
	}

	//
	if (m_moveUp == true)
	{
		m_titleY -= 0.5;
	}

	if (m_moveDown == true)
	{
		m_titleY += 0.5;
	}


	//
	if (m_titleAlpha >= 255)
	{
		m_flashTitleOut = true;
		m_flashTitleIn = false;
	}
	else if (m_titleAlpha <= 50)
	{
		m_flashTitleOut = false;
		m_flashTitleIn = true;
	}

	//
	if (m_flashTitleIn == true)
	{
		m_titleAlpha += 1;
	}
	//
	if (m_flashTitleOut == true)
	{
		m_titleAlpha -= 1;
	}

	//
	m_titleSprite.setColor(sf::Color(255, 255, 255, m_titleAlpha));
	//
	m_titleSprite.setPosition(m_titleX, m_titleY);
}

//
void GameOver::setTitle(MusicManager * music)
{
	//
	if (m_win == true)
	{
		//
		if (m_playTrack == true)
		{
			//
			m_titleSprite.setTexture(m_titleTwoTexture);
			m_titleSprite.setOrigin(sf::Vector2f(220.0f, 39.0f));
			m_titleSprite.setPosition(m_titlePosition);
			//
			music->setGameOverTrack(7);
			music->setTrackNum(music->getGameOverTrack());
			m_playTrack = false;
		}
	}
	//
	else if (m_lose == true)
	{
		//
		if (m_playTrack == true)
		{
			//
			m_titleSprite.setTexture(m_titleTexture);
			m_titleSprite.setOrigin(sf::Vector2f(287.0f, 39.0f));
			m_titleSprite.setPosition(m_titlePosition);
			//
			music->setGameOverTrack(6);
			music->setTrackNum(music->getGameOverTrack());
			m_playTrack = false;
		}
	}
}

//
void GameOver::render(sf::RenderWindow& window)
{
	//
	window.draw(m_titleSprite);
	
	//
	window.draw(m_mainSprite);
	//
	window.draw(m_replaySprite);
	//
	window.draw(m_quitSprite);
}

//
bool GameOver::getPlayTime()
{
	return m_playTime;
}

//
bool GameOver::getMainMenu()
{
	return m_mainMenu;
}

//
bool GameOver::getWin()
{
	return m_win;
}

//
bool GameOver::getLose()
{
	return m_lose;
}

//
void GameOver::setPlayTime(bool playTime)
{
	m_playTime = playTime;
}

//
void GameOver::setMainMenu(bool mainMenu)
{
	m_mainMenu = mainMenu;
}

//
void GameOver::setWin(bool win)
{
	m_win = win;
}

// 
void GameOver::setLose(bool lose)
{
	m_lose = lose;
}

//
void GameOver::setPlayTrack(bool track)
{
	m_playTrack = track;
}