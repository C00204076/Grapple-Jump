//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:27 1 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef LICENSE_H
#define LICENSE_H

#include "SFML/Graphics.hpp"

#include <iostream>

//
class License
{
public:
	License();
	~License();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

	float getScreenTime();

private:
	void initialise();
	void loadTexture();

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;

	float m_screenTime;
	float m_alpha;

	bool m_fadeIn, m_fadeOut;
};

#endif // !LICENSE_H
