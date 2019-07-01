//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:47 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef IDLE_H
#define IDLE_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class Idle : public State
{
public:
	Idle();
	~Idle();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void landing(Animation* animation);
};

#endif // !IDLE_H
