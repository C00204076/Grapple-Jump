//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:12 29 August 2019
// Finished at
// Time taken:
// Known bugs:

#include "Death.h"

//
Death::Death()
{

}

//
Death::~Death()
{
	
}

//
void Death::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}

//
void Death::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}

//
void Death::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}

//
void Death::falling(Animation * animation)
{
	std::cout << "Falling" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}

//
void Death::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}

//
void Death::death(Animation * animation)
{
	std::cout << "Dying" << std::endl;
	animation->setCurrent(new Death());
	delete this;
}