//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:38 26 June 2019
// Finished at 
// Time taken:
// Known bugs: Player character may appear as green box

#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include "State.h"
#include "Idle.h"
#include "Move.h"
#include "Jump.h"
#include "Land.h"

#include "Player.h"

class State;

//
class Animation
{
public:
	Animation();

	void idle(Player* player);
	void moving(Player* player);
	void jumping(Player* player);
	void falling(Player * player);
	void landing(Player* player);

	void update(Player* player);

	void setCurrent(State* current);
	State* getCurrent();

private:
	State* m_current;
	sf::Clock m_clock;
	int m_idleTimer, m_moveTimer, m_jumpingTimer;
};

#endif // !ANIMATION_H