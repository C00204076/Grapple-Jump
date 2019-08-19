// Ground header file used for methods and functions related to Ground
// C00204076
// Brandon Seah-Dempsey
// Started at 13:44 7 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 30 minutes
// Known Bugs: None

#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "AABB.h"

// Ground class
class Ground
{
public:
	Ground();
	Ground(int x, int y, float scaleX, float scaleY);
	~Ground();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	
	sf::Sprite getSprite();
	sf::Sprite getTopBoundingBox();
	sf::Sprite getBottomBoundingBox();
	sf::Sprite getLeftBoundingBox();
	sf::Sprite getRightBoundingBox();
	sf::Sprite getTopLeftBoundingBox();
	sf::Sprite getTopRightBoundingBox();

	float getScaleX(); 
	float getScaleY();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	AABB *getAABB();
	

private:
	void loadTexture();

	sf::Sprite m_sprite, m_topBorderBox, m_bottomBorderBox, 
		m_leftBorderBox, m_rightBorderBox, m_topLeftBox, m_topRightBox;
	sf::Texture m_texture, m_boundingBoxTexture;

	sf::Vector2f m_position;
	sf::IntRect m_sourceRectSprite;

	AABB * m_AABB;

	float m_scaleX, m_scaleY;
};

#endif // !GROUND_H