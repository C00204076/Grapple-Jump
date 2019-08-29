//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:34 5 July 2019
// Finished at 10:49
// Time taken:
// Known bugs:

#ifndef FALL_H
#define FALL_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class Fall : public State
{
public:
	Fall();
	~Fall();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void falling(Animation * animation);
	void landing(Animation* animation);
	void death(Animation* animation);
};

#endif // !FALL_H
