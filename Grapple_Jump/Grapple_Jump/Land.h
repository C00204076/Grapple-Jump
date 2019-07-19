//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:34 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef LAND_H
#define LAND_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class Land : public State
{
public:
	Land();
	~Land();

	void idle(Animation* animation);
	void moving(Animation* animation);
	void jumping(Animation* animation);
	void falling(Animation * animation);
	void landing(Animation* animation);
};

#endif // !LAND_H
