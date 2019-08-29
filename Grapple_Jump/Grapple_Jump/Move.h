//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:08 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class Move : public State
{
public:
	Move();
	~Move();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void falling(Animation * animation);
	void landing(Animation* animation);
	void death(Animation* animation);
};

#endif // !MOVE_H