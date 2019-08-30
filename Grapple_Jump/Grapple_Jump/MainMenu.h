//
// C00204076
// Brandon Seah-Dempsey
// Started at 12:09 1 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef MAINMENU_H
#define MAINMENU_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "MusicManager.h"

#include <iostream>

//
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void update(sf::Time deltaTime, Player * player, sf::RenderWindow& window, MusicManager * music, sf::View & v);
	void render(sf::RenderWindow& window);

	bool getPlayTime();
	void setPlayTime(bool playTime);

private:
	void initialise();
	void loadTexture();
	void loadAudio();
	void loadFont();

	void mouseButtonInteraction(Player * player, sf::RenderWindow& window, MusicManager * music);
	void changeButtonColour();
	void juicyMainTitle();
	void trackDisplay();

	sf::Texture m_titleTexture, m_playTexture, m_quitTexture, 
		m_titleMusicTexture, m_bgmTexture;
	sf::Sprite m_titleSprite, m_playSprite, m_quitSprite, 
		m_titleMusicSprite, m_bgmSprite;

	sf::SoundBuffer m_buttonClick, m_trackButtonClick;
	sf::Sound m_btnClick, m_trackBtnClick;

	sf::Font m_font;
	sf::Text m_titleText, m_bgmText;

	sf::Vector2f m_titlePosition;

	int m_trackDisplay, m_otherTrackDisplay;
	float m_alpha, m_titleAlpha, m_titleX, m_titleY;
	bool m_flashIn, m_flashOut, m_flashTitleIn, m_flashTitleOut, m_moveUp, m_moveDown;
	bool m_playTime;
	bool m_playPlay, m_playQuit, m_playTitle, m_playBGM; 

};

#endif // !MAINMENU_H