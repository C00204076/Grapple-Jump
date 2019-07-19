//
// C00204076
// Brandon Seah-Dempsey
// Started at 16:36 26 June 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef STATE_H
#define STATE_H

#include <iostream>
#include "Animation.h"

class Animation;

//
class State
{
public:
	//
	virtual void idle(Animation * animation)
	{
		//std::cout << "Idling" << std::endl;
	}

	//
	virtual void moving(Animation * animation)
	{
		//std::cout << "Moving" << std::endl;
	}

	//
	virtual void jumping(Animation * animation)
	{
		//std::cout << "Jumping" << std::endl;
	}

	//
	virtual void falling(Animation * animation)
	{
		//std::cout << "falling" << std::endl;
	}

	//
	virtual void landing(Animation * animation)
	{
		//std::cout << "Landing" << std::endl;
	}

};

#endif // !STATE_H
