//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:50 19 August 2019
// Finished at 
// Time Taken: 
// Known Bugs:

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "MusicManager.h"

#include <iostream>

//
class GameOver
{
public:
	GameOver();
	~GameOver();

	void update(sf::Time deltaTime, Player * player, sf::RenderWindow& window, MusicManager * music, sf::View & v);
	void render(sf::RenderWindow& window);

	bool getPlayTime();
	void setPlayTime(bool playTime);

	bool getMainMenu();
	void setMainMenu(bool mainMenu);

	bool getWin();
	void setWin(bool win);

	bool getLose();
	void setLose(bool lose);

	void setPlayTrack(bool track);

private:
	void initialise();
	void loadTexture();
	void loadAudio();

	void mouseButtonInteraction(Player * player, sf::RenderWindow& window, MusicManager * music);
	void changeButtonColour();
	void juicyGameOverTitle();
	void setTitle(MusicManager * music);

	sf::Texture m_titleTexture, m_titleTwoTexture, m_mainTexture, m_replayTexture, m_quitTexture;
	sf::Sprite m_titleSprite, m_mainSprite, m_replaySprite, m_quitSprite;

	sf::Vector2f m_titlePosition;

	sf::SoundBuffer m_buttonClick, m_buttonCollide;
	sf::Sound m_btnClick, m_btnCollide;

	float m_alpha, m_titleAlpha, m_titleX, m_titleY;
	bool m_flashIn, m_flashOut, m_flashTitleIn, m_flashTitleOut, m_moveUp, m_moveDown;
	bool m_playTime, m_mainMenu, m_win, m_lose;
	bool m_playReplay, m_playMain, m_playQuit, m_playTrack;
};

#endif // !GAMEOVER_H
