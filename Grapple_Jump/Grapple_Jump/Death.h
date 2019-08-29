//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:12 29 August 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef DEATH_H
#define DEATH_H

#include <iostream>
#include "Animation.h"

class Death : public State
{
public:
	Death();
	~Death();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void falling(Animation * animation);
	void landing(Animation* animation);
	void death(Animation* animation);
};

#endif // !DEATH_H