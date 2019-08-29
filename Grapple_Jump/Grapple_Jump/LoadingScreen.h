//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:00 29 August 2019
// Finished at 
// Time Taken: 
// Known Bugs:

#ifndef LOADING_H
#define LOADING_H

#include "SFML/Graphics.hpp"

#include <iostream>

//
class Loading
{
public:
	Loading();
	~Loading();

	void update(sf::Time deltaTime, sf::View & v);
	void render(sf::RenderWindow& window);

	int getTimer();
	void setTimer(int timer);

	bool getPlay();
	void setPlay(bool play);

	bool getMainMenu();
	void setMainMenu(bool mainMenu);

	bool getGameOver();
	void setGameOver(bool gameOver);


private:
	void initialise();
	void loadTexture();
	void loadFont();
	void setTextMessage();

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Font m_font;
	sf::Text m_levelText;


	int m_timer, m_angle;
	bool m_play, m_mainMenu, m_gameOver;
};

#endif // !LOADING_H