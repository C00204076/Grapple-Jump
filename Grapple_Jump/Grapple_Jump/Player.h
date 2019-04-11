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

#include "HookPoint.h"
#include "Ground.h"


#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846


//SFML - Move object towards coord
/*
The direction to move your enemy into is simply the difference between the player position and the enemy position. However, you want the enemies to move with constant speed, so you need to normalize the result. This will give you the direction as a vector of length 1.

Vector2u direction = normalize(player.getPosition() - enemy.getPosition());
You can now multiply this direction by the speed constant of that enemy's type. The result is a vector with it's length depending on the speed factor instead of the distance to the player. Just use the result to move your enemy.

enemy.move(speed * direction);
However, you perform that once a frame and framerates can vary between machines and configurations. Therefore, you should add a the elapsed time since the last move call, which might be your frame time, as factor to the equation. This way, if a frame takes a longer than usual, the enemy will be moved further to comprehend this, and vice versa.

// Initialize a timer
sf::Clock clock;

// Get elapsed time at the beginning of a frame
// I multiply this by target framerate to get a value around one
float delta = clock.restart().asSeconds() * 60;

// Move all objects based on elapsed time
Vector2u direction = normalize(player.getPosition() - enemy.getPosition());
enemy.move(delta * speed * direction);
By the way, basic knowledge of linear algebra is needed very often in game development, so you might pay out to attend an online course.
*/


//Extending a line to a certain length from 2 points
/*
The maths are pretty simple. Consider the following line, A and B being your known points (A is the origin of the segment, ie. your player) and C being the third point you're looking for:

A-----------B------------C
(Xa,Ya)     (Xb,Yb)      (Xc,Yc)
Now the distances:

AB = sqrt( (Xb - Xa)� + (Yb - Ya)� )
AC = 1000
Cross-multiply to get Xc:

AB -> Xb - Xa
AC -> Xc - Xa

Xc - Xa = AC * (Xb - Xa) / AB
Xc = Xa + (AC * (Xb - Xa) / AB)
Similarly, Yc = Ya + (AC * (Yb - Ya) / AB)

Note that this also works if C is between A and B, the only (obvious) restriction is if A and B are the same point (AB = 0, conveys no direction information and rightly yields a division by zero).
*/

//Moving an object in a circular path
/*
X := originX + cos(angle)*radius;
Y := originY + sin(angle)*radius;

(originX, originY) is the center of your circle. radius is its radius. That's it.

This works because the sine and cosine are mathematically related to the unit circle.
*/

class Game; //Forward delaration for cyclical reference

// Player class
class Player
{
public:
	Player();
	~Player();
	
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void initialise();
	void loadTextures();

	void collosionWithGround(Ground ground);
	void grapplePointCollision(HookPoint hookPoint);

	sf::Vector2f getPosition();

	sf::Vector2i getMousePosition();

private:
	void movePlayer();
	void boundaryCheck();
	void jump(sf::Time deltaTime);
	void grapplingHook();
	void resetHook();
	
	sf::Vector2f normalize(sf::Vector2f vector);


	sf::Keyboard m_keyboard;

	sf::Sprite m_sprite, m_windowSprite, m_hookSprite;
	sf::Texture m_texture, m_otherTexture, m_hookTexture;
	sf::Vertex m_grapplingLine[2];

	sf::Vector2f m_gravity, m_velocity, m_acceleration, m_position, m_hookPosition, m_mouseVector, m_tempMouseVec;
		
	sf::Vector2i m_mousePosition;
	float m_mouseX, m_mouseY;

	sf::Vector2f m_pullDirection, m_cablePullDir;
	float m_directionX, m_directionY; 
	float m_pullSpeed; 
	float m_length, m_maxLength, m_maxHeight;
	float  m_cablePullX, m_cablePullY;
	float  m_angle, m_aAccel, m_aVel, m_rLength, m_damping;

	bool m_jumping, m_falling; 
	bool m_left, m_right; 
	bool m_line, m_fired, m_hookLatched, m_cableAdjust, m_pulled, m_extend;
};

#include "Game.h"
#endif // !PLAYER_H
