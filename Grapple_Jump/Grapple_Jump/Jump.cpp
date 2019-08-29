//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:56 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#include "Jump.h"

//
Jump::Jump()
{

}

//
Jump::~Jump()
{

}

//
void Jump::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}

//
void Jump::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}

//
void Jump::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}

//
void Jump::falling(Animation * animation)
{
	std::cout << "Falling" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}

//
void Jump::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}

//
void Jump::death(Animation * animation)
{
	std::cout << "Dying" << std::endl;
	animation->setCurrent(new Jump());
	delete this;
}