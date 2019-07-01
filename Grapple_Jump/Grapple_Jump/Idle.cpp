//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:56 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#include "Idle.h"

//
Idle::Idle()
{

}

//
Idle::~Idle()
{

}

//
void Idle::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Idle());
	delete this;
}

//
void Idle::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Idle());
	delete this;
}

//
void Idle::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Idle());
	delete this;
}

//
void Idle::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Idle());
	delete this;
}