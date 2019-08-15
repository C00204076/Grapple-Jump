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
	loadAudio();
	loadFont();

	//
	m_alpha = 255;
	m_titleAlpha = 255;
	//
	m_flashOut = true;
	m_flashIn = false;
	m_flashTitleIn = false;
	m_flashTitleOut = true;
	m_moveUp = false;
	m_moveDown = true;
	//
	m_playTime = false;

	//
	m_titlePosition = sf::Vector2f(750, 250);
	m_titleX = m_titlePosition.x;
	m_titleY = m_titlePosition.y;
	//
	m_titleSprite.setTexture(m_titleTexture);
	m_playSprite.setTexture(m_playTexture);
	m_quitSprite.setTexture(m_quitTexture);
	m_titleMusicSprite.setTexture(m_titleMusicTexture);
	m_bgmSprite.setTexture(m_bgmTexture);
	//
	m_titleSprite.setOrigin(sf::Vector2f(302.5f, 140.0f));
	m_playSprite.setOrigin(sf::Vector2f(66.5f, 19.0f));
	m_quitSprite.setOrigin(sf::Vector2f(66.5f, 19.0f));
	m_titleMusicSprite.setOrigin(sf::Vector2f(352.0f, 25.0f));
	m_bgmSprite.setOrigin(sf::Vector2f(229.5f, 25.0f));
	//
	m_titleSprite.setPosition(m_titlePosition);
	m_playSprite.setPosition(sf::Vector2f(750, 550));
	m_quitSprite.setPosition(sf::Vector2f(750, 750));
	m_titleMusicSprite.setPosition(sf::Vector2f(175, 750));
	m_bgmSprite.setPosition(sf::Vector2f(145, 850));
	//
	m_titleMusicSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	m_bgmSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	//
	m_btnClick.setBuffer(m_buttonClick);
	m_trackBtnClick.setBuffer(m_trackButtonClick);

	//
	m_titleText.setFont(m_font);
	m_titleText.setCharacterSize(14);
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setPosition(sf::Vector2f(20, 20));
	m_titleText.setStyle(sf::Text::Bold);
	//
	m_bgmText.setFont(m_font);
	m_bgmText.setCharacterSize(14);
	m_bgmText.setFillColor(sf::Color::White);
	m_bgmText.setPosition(sf::Vector2f(20, 50));
	m_bgmText.setStyle(sf::Text::Bold);
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

	if (!m_titleMusicTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Change_Title.png"))
	{
		std::cout << "Error! Unable to load Change_Title.png from game files!" << std::endl;
	}

	if (!m_bgmTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Change_BGM.png"))
	{
		std::cout << "Error! Unable to load Change_BGM.png from game files!" << std::endl;
	}
}

//
void MainMenu::loadAudio()
{
	//
	if (!m_buttonClick.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Click_On.wav"))
	{
		std::cout << "Error! Unable to load Click_On.wav from game files!" << std::endl;
	}
	//
	if (!m_trackButtonClick.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/SOUNDEFFECTS/Click_2.wav"))
	{
		std::cout << "Error! Unable to load Click_On.wav from game files!" << std::endl;
	}
}

//
void MainMenu::loadFont()
{
	if (!m_font.loadFromFile("../Grapple_Jump/ASSETS/FONTS/corbel.ttf"))
	{
		std::cout << "Error! Unable to load corbel.ttf from game files!" << std::endl;
	}
}

//
void MainMenu::update(sf::Time deltaTime, Player * player, sf::RenderWindow& window, MusicManager * music, sf::View & v)
{
	//
	m_trackDisplay = music->getTrackNum();
	m_otherTrackDisplay = music->getOtherTrack();
	trackDisplay();

	//
	juicyMainTitle();
	mouseButtonInteraction(player, window, music);

	v.setCenter(750.0f, 450.0f);
}

//
void MainMenu::mouseButtonInteraction(Player * player, sf::RenderWindow& window, MusicManager * music)
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
			//
			m_btnClick.play();
			//
			m_playTime = true;
			music->setTrackNum(music->getOtherTrack());
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
			//
			m_btnClick.play();
			//
			window.close();
		}
	}
	//
	else if (m_titleMusicSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		changeButtonColour();
		//
		m_titleMusicSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		//
		m_titleMusicSprite.setScale(sf::Vector2f(0.5f, 0.5f));
		//
		m_titleMusicSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		
		//
		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//
			m_trackBtnClick.play();

			//
			int trackNum = music->getTrackNum() + 1;

			//
			if (trackNum < 1)
			{
				trackNum = 1;
			}
			//
			else if (trackNum > 2)
			{
				trackNum = 1;
			}

			music->setTitleTrack(trackNum);
			music->setTrackNum(trackNum);
		}
	}
	//
	else if (m_bgmSprite.getGlobalBounds().contains(player->getMousePosition()))
	{
		//
		changeButtonColour();
		//
		m_bgmSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		//
		m_bgmSprite.setScale(sf::Vector2f(0.5f, 0.5f));
		//
		m_bgmSprite.setColor(sf::Color(255, 255, 255, m_alpha));

		//
		//
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//
			m_trackBtnClick.play();

			//
			int otherTrack = music->getOtherTrack() + 1;
			
			//
			if (otherTrack < 3)
			{
				otherTrack = 3;
			}
			//
			else if (otherTrack > 5)
			{
				otherTrack = 3;
			}

			//
			music->setOtherTrack(otherTrack);
		}
	}
	//
	else
	{
		//
		m_alpha = 255;
		//
		m_playSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_quitSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		//
		m_titleMusicSprite.setScale(sf::Vector2f(0.25f, 0.25f));
		//
		m_bgmSprite.setScale(sf::Vector2f(0.25f, 0.25f));

		//
		m_playSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_quitSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_titleMusicSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		//
		m_bgmSprite.setColor(sf::Color(255, 255, 255, m_alpha));
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
void MainMenu::juicyMainTitle()
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
void MainMenu::trackDisplay()
{
	//
	if (m_trackDisplay == 1)
	{
		m_titleText.setString("Title Music: Touhou Luna Nights OST:04 - Child of Are");
	}
	//
	if (m_trackDisplay == 2)
	{
		m_titleText.setString("Title Music: Touhou Luna Nights OST:21 - The Chaotic Space");
	}


	//
	if (m_otherTrackDisplay == 3)
	{
		m_bgmText.setString("BGM: Touhou Luna Nights OST: 12 - The Young Descendent of Tepes");
	}
	//
	if (m_otherTrackDisplay == 4)
	{
		m_bgmText.setString("BGM: Touhou Luna Nights OST: 22 - A Dream More Scarlet than Red");
	}
	//
	if (m_otherTrackDisplay == 5)
	{
		m_bgmText.setString("BGM: Touhou Luna Nights OST: 11 - Locked Girl ~ The Girl's Secret Room");
	}
}

//
void MainMenu::render(sf::RenderWindow& window)
{
	//
	window.draw(m_titleText);
	//
	window.draw(m_bgmText);

	//
	window.draw(m_titleSprite);
	//
	window.draw(m_playSprite);
	//
	window.draw(m_quitSprite);
	//
	window.draw(m_titleMusicSprite);
	//
	window.draw(m_bgmSprite);
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