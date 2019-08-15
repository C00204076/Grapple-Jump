//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:48 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef GRAPPLINGHOOK_H
#define GRAPPLINGHOOK_H

#include "SFML/Audio.hpp"
#include "Player.h"
#include "HookPoint.h"

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

AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
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

/*
x² + y² + ax + by + 1 = 0
x² + ax + a²/4 + y² + by + b²/4 + 1 - a²/4 - b²/4 = 0
(x + a/2)² + (y + b/2)² = (a² + b²)/4 - 1

theta = atan2(sprite.y + b/2, sprite.x + a/2)

newPosition.x = cos(theta) * radius - a/2
newPosition.y = sin(theta) * radius - b/2
*/

//Pendulum
/*
length = player->getPosition().y - origin.y

Setting position
	player.x = m_tempMouseVec.x + length * sin(theta)
	player.y = m_tempMouseVec.y + length * cos(theta)
	
	theta is angle

Angular acceleration
	Force of pendulum
	Force of gravity
	
	angular acceleration = -0.01 * sin(angle)
	
	angle += angular velocity
	angular velocity += angular acceleration
	
	angular velocity *= 0.99

With gravity(realistic)
	gravity = 0.8;

	angular acceleration = (-1 * gravity / length) * sin(angle)

	angular velocity += angular acceleration
	angular velocity *= damping
	angle += angular velocity
*/

//
class GrapplingHook
{
public:
	GrapplingHook();
	~GrapplingHook();

	void loadTexture();
	void initialise();
	
	void update(Player* player, sf::Vector2f mouse);

	void draw(sf::RenderWindow& window);
	
	void resetHook(Player* player);

	void grapplePointCollision(Player *player, HookPoint hookPoint);

	bool getHookLatched();

private:
	void loadAudio();

	void grapplingHook(Player* player);
	void fire(Player * player);
	void detach(Player * player);
	void extend(Player * player);
	void retract(Player * player);
	void swing(Player *  player);

	sf::SoundBuffer m_firedBuffer, m_latchedBuffer, m_swingBuffer, m_extendBuffer, m_retractBuffer, m_detachBuffer;
	sf::Sound m_firedSound, m_latchedSound, m_swingSound, m_extendSound, m_retractSound, m_detachSound;

	sf::Sprite m_hookSprite;
	sf::Texture m_hookTexture;
	sf::Vector2f m_hookPosition, m_mouseVector, m_tempMouseVec, m_position;
	sf::Vertex m_grapplingLine[2];

	sf::Vector2i m_mousePosition;
	float m_mouseX, m_mouseY;

	sf::Vector2f m_pullDirection, m_cablePullDir;
	float m_directionX, m_directionY;
	float m_pullSpeed;
	float m_angle, m_rLength;
	float  m_cablePullX, m_cablePullY;
	float m_angAccel, m_angVel, m_radius;

	bool m_hookLatched, m_fired, m_cableAdjust, m_pulled, m_extend, m_swing, m_retractPlayed, m_extendPlayed, m_leftPlayed, m_rightPlayed;
	
	sf::Vector2f normalize(sf::Vector2f vector);
};
#endif // !GRAPPLINGHOOK_H