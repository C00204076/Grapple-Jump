//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:48 18 July 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef GRAPPLINGHOOK_H
#define GRAPPLINGHOOK_H

#include "Player.h"
#include "HookPoint.h"

class GrapplingHook
{
public:
	GrapplingHook();
	~GrapplingHook();

	void loadTexture();
	void initialise();
	
	void update(Player* player, sf::Vector2f mouse);

	void draw(sf::RenderWindow& window);
	
	void grapplePointCollision(Player *player, HookPoint hookPoint);

	


private:
	sf::Sprite m_hookSprite;
	sf::Texture m_hookTexture;
	sf::Vector2f m_hookPosition, m_mouseVector, m_tempMouseVec, m_position;;
	sf::Vertex m_grapplingLine[2];

	sf::Vector2i m_mousePosition;
	float m_mouseX, m_mouseY;

	sf::Vector2f m_pullDirection, m_cablePullDir;
	float m_directionX, m_directionY;
	float m_pullSpeed;
	float m_length, m_rLength;
	float  m_cablePullX, m_cablePullY;

	bool m_hookLatched, m_fired, m_cableAdjust, m_pulled, m_extend;
	
	sf::Vector2f normalize(sf::Vector2f vector);

	void grapplingHook(Player* player);
	void fire(Player * player);
	void detach(Player * player);
	void extend(Player * player);
	void retract(Player * player);
	void swing(Player *  player);
	void resetHook(Player* player);
};
#endif // !GRAPPLINGHOOK_H