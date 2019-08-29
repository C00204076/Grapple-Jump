//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:34 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#include "Land.h"

//
Land::Land()
{

}

//
Land::~Land()
{

}

//
void Land::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}

//
void Land::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}

//
void Land::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}

//
void Land::falling(Animation * animation)
{
	std::cout << "Falling" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}

//
void Land::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}

//
void Land::death(Animation * animation)
{
	std::cout << "Dying" << std::endl;
	animation->setCurrent(new Land());
	delete this;
}