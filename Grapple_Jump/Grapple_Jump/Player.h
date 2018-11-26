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



//
class Game; //Forward delaration for cyclical reference

//
class Player
{
public:
	Player(sf::Texture & texture, sf::Texture & Othertexture);
	~Player();

	void update(sf::Time deltaTime, Ground ground);
	void render(sf::RenderWindow& window);
	void initialise();

	sf::Vector2f getPosition();

	sf::Vector2i getMousePosition();
	

private:
	void movePlayer();
	void jump(sf::Time deltaTime);
	void collosionWithGround(Ground ground);



	sf::Keyboard m_keyboard;

	sf::Sprite m_sprite;
	sf::Texture m_texture, m_otherTexture;

	sf::Vector2f m_gravity, m_velocity, m_acceleration, m_position;
		
	sf::Vector2i m_mousePosition;

	bool m_jumping, m_left, m_right, m_speed;

	//
	// Grappling Rope methods 
	b2Body* shootRope(b2Vec2 &intersectPoint, b2Vec2 &intersectNormal);

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
	//

	//
	// Grappling Rope variables
	int m_ropeType;
	float m_ropeLength;

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

	//

};

#include "Game.h"
#endif // !PLAYER_H
