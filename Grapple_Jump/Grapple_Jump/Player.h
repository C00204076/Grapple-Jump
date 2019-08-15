// Player header file used for methods and functions related to Player and Grappling Hook
// C00204076
// Brandon Seah-Dempsey
// Started at 9:53 7 November 2018
// Finished at 15:07 11 April 2019
// Time Taken: 6 hours 24 minutes
// Known Bugs: Grappling Hook may get stuck in place if it is not 
// latched onto a Hook Point

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "HookPoint.h"
#include "Ground.h"
#include "AABB.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

class Game; //Forward delaration for cyclical reference
class Animation;
class GrapplingHook;

// Player class
class Player
{
public:
	Player();
	~Player();
	
	void update(sf::Time deltaTime, sf::View & v, bool grapple);
	void render(sf::RenderWindow& window, sf::Vector2f scale);


	void mouseCursor(sf::RenderWindow& window, sf::View & v);

	void collosionWithGround(Ground * ground);
	void grapplePointCollision(HookPoint hookPoint);

	void checkAABBCollision(AABB * other);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	sf::Vector2f getMousePosition();

	sf::Sprite getSprite();
	void setTexture(sf::Texture texture);

	sf::IntRect getSourceRectSprite();
	void setSourceRectSprite(sf::IntRect rectangle);

	bool getLeft(), getRight();
	bool getMoving(), getJumping(), getFalling();
	void setFalling(bool falling);

	void reset();

	AABB * getAABB();

private:
	void initialise();
	void loadTextures();
	void loadAudio();

	void movePlayer();
	void boundaryCheck();
	void jump(sf::Time deltaTime);
	void changeSpriteSheet();
	
	sf::Vector2f normalize(sf::Vector2f vector);

	Animation *m_fsm;
	GrapplingHook *m_grapplinghook;

	AABB * m_AABB;

	sf::Keyboard m_keyboard;

	sf::IntRect m_sourceRectSprite;
	sf::Sprite m_sprite, m_windowSprite;
	sf::Texture m_idleRightText, m_idleLeftText, m_idleRightTextTwo, 
		m_idleLeftTextTwo, m_moveRightText,m_moveLeftText, 
		m_jumpRightText, m_jumpLeftText, m_landRightText, m_landLeftText;
	sf::Texture m_JumpTexture, m_otherTexture;
	
	sf::SoundBuffer m_jumpBuffer, m_landBuffer;
	sf::Sound m_jumpSound, m_landSound;

	sf::Vector2f m_gravity, m_velocity, m_acceleration, m_position, m_hookPosition, m_mouseVector, m_tempMouseVec;
		
	sf::Vector2i m_mousePosition;
	float m_mouseX, m_mouseY;

	int m_ranNumber, m_jumpPrep;

	float m_pullSpeed; 
	float m_length, m_maxLength, m_maxHeight;
	float  m_cablePullX, m_cablePullY;
	float  m_angle, m_aAccel, m_aVel, m_rLength, m_damping;

	bool m_jumping, m_falling, m_moving, m_landing, m_jump, m_jumpPlayed; 
	bool m_left, m_right; 
};

#include "Game.h"
#include "Animation.h"
#include "GrapplingHook.h"
#endif // !PLAYER_H
