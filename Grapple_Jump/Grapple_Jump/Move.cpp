//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:56 27 June 2019
// Finished at
// Time taken:
// Known bugs:

#include "Move.h"

//
Move::Move()
{

}

//
Move::~Move()
{

}

//
void Move::idle(Animation * animation)
{
	std::cout << "Idling" << std::endl;
	animation->setCurrent(new Move());
	delete this;
}

//
void Move::moving(Animation * animation)
{
	std::cout << "Moving" << std::endl;
	animation->setCurrent(new Move());
	delete this;
}

//
void Move::jumping(Animation * animation)
{
	std::cout << "Jumping" << std::endl;
	animation->setCurrent(new Move());
	delete this;
}

//
void Move::falling(Animation * animation)
{
	std::cout << "Falling" << std::endl;
	animation->setCurrent(new Move());
	delete this;
}

//
void Move::landing(Animation * animation)
{
	std::cout << "Landing" << std::endl;
	animation->setCurrent(new Move());
	delete this;
}