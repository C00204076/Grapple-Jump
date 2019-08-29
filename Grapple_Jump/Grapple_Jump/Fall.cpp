//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:50 5 July 2019
// Finished at
// Time taken:
// Known bugs:

#include "Fall.h"

//
Fall::Fall()
{

}

//
Fall::~Fall()
{

}

//
void Fall::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}

//
void Fall::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}

//
void Fall::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}

//
void Fall::falling(Animation * animation)
{
	std::cout << "Falling" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}

//
void Fall::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}

//
void Fall::death(Animation * animation)
{
	std::cout << "Dying" << std::endl;
	animation->setCurrent(new Fall());
	delete this;
}