//
// C00204076
// Brandon Seah-Dempsey
// Started at 9:53 7 November 2018
// Finished at
// Time Taken:
// Known Bugs:

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D.h>

#include "Ground.h"


#include <iostream>
#include <string>
#include <vector>
#include <math.h>

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


//
class Game; //Forward delaration for cyclical reference

//
class Player
{
public:
	Player(sf::Texture & texture, sf::Texture & Othertexture);
	~Player();

	void update(sf::Time deltaTime, sf::RenderWindow& window, Ground ground);
	void render(sf::RenderWindow& window);
	void initialise();

	sf::Vector2f getPosition();

	sf::Vector2i getMousePosition();
	
/*protected:
	b2World m_world;
	b2Body m_playerBody;
	b2DistanceJoint m_distanceJoint;*/

private:
	void movePlayer();
	void jump(sf::Time deltaTime);
	void collosionWithGround(Ground ground);

	//
	//
	//b2Body addBox();
	//


	sf::Keyboard m_keyboard;

	sf::Sprite m_sprite;
	sf::Texture m_texture, m_otherTexture;
	sf::Vertex m_grapplingLine[2];

	sf::Vector2f m_gravity, m_velocity, m_acceleration, m_position, m_hookPosition;
		
	sf::Vector2i m_mousePosition;
	float m_mouseX, m_mouseY;

	sf::Vector2u m_pullDirection;
	float m_directionX, m_directionY, m_pullSpeed;

	bool m_jumping, m_left, m_right, m_speed, m_line;

	/*
	// Grappling Rope methods 
	/*b2Body* shootRope(b2Vec2 &intersectPoint, b2Vec2 &intersectNormal);

	void updateRope();

	void makeRopeJoint();
	void removeRopeJoint();

	void makeRopeChain();
	void removeRopeChain();

	void makeRopePrismatic(bool simple, float ix, float iy, sf::Sprite *target, sf::Sprite *player, bool add_point, float speed); //, Map *map);
	bool updateRopePrismatic(bool simple);// , Map *map);
	bool ropeReconnect();// Map *map);
	void removeRopePrismatic(bool objects, bool rest, bool collisions, bool sprites);

	void rope_BeginContact(b2Contact *contact, b2Fixture *fa, b2Fixture *fb);
	void rope_PreSolve(b2Contact *contact, const b2Manifold *oldManifold, b2Fixture *fa, b2Fixture *fb);

	void collisionPointToVertex(float &xx, float &yy, sf::Sprite *a);
	void addRopeEffect(float sx, float sy, float ex, float ey, sf::Sprite *sprite);
	
	void createHook();
	
	//



	//
	// Grappling Rope variables
	/*b2Vec2 m_grav2d = b2Vec2(0, -9.8);

	b2World* m_world = new b2World(m_grav2d, true);

	b2BodyDef* m_dynamicBody;
	m_dynamicBody.type = b2_dynamicBody;
	m_dynamicBody.position.Set(-10, 20);

	b2Body* dynamicBody, m_playerBody;
	b2DistanceJoint m_distanceJoint;

	b2CircleShape circleShape;
	b2FixtureDef m_fixture;

	int m_ropeType;
	float m_ropeLength;

	bool m_isHooked

	sf::Sprite *m_spriteRope; // Grappling rope hook
	sf::Sprite *m_spriteSlider; // Grappling rope body connected to hook
	sf::Sprite *m_spriteRotor; //
	sf::Sprite *m_ropeBreak;

	std::vector<sf::Sprite*> m_ropeSprites;
	std::vector<b2Vec2> m_ropeSpriteVetices;

	std::vector<sf::Vector3f> m_ropePoints;
	std::vector<sf::Vector3f> m_ropeBreakpoints;

	std::vector<b2Fixture*> m_beginFixtures;
	
	/*
	Map				*rope_map;
	EntityJoint		*rope;
	EntityJoint		*rope_revolute_i;
	ParticleEffect	*rope_effect;
	*/

};

#include "Game.h"
#endif // !PLAYER_H
