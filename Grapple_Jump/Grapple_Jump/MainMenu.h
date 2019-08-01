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

#include <iostream>

//
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void update(sf::Time deltaTime, Player * player, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	bool getPlayTime();
	void setPlayTime(bool playTime);

private:
	void initialise();
	void loadTexture();

	void changeButtonColour();

	sf::Texture m_titleTexture, m_playTexture, m_quitTexture;
	sf::Sprite m_titleSprite, m_playSprite, m_quitSprite;

	sf::Vector2f m_titlePosition;

	float m_alpha;
	bool m_flashIn, m_flashOut;
	bool m_playTime;
};

#endif // !MAINMENU_H