//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:14 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef JUMP_H
#define JUMP_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class Jump : public State
{
public:
	Jump();
	~Jump();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void falling(Animation * animation);
	void landing(Animation* animation);
	void death(Animation* animation);
};

#endif // !JUMP_H
