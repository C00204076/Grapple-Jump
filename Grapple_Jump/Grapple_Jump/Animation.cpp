//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:45 26 June 2019
// Finished at 
// Time taken:
// Known bugs:

#include "Animation.h"

//
Animation::Animation()
{
	m_current = new Idle();

}

//
void Animation::idle(Player* player)
{
	m_current->idle(this);

	//
	if (m_clock.getElapsedTime().asSeconds()> 0.08f)
	{
		//
		if (player->getSourceRectSprite().left >= 925)
		{
			player->setSourceRectSprite(sf::IntRect(1, 4, 75, 75));
		}
		//
		else
		{
			player->setSourceRectSprite(sf::IntRect(player->getSourceRectSprite().left + 77, 4, 75, 75));
		}

		m_clock.restart();
	}
}

//
void Animation::moving(Player* player)
{
	m_current->moving(this);

	//
	if (m_clock.getElapsedTime().asSeconds() > 0.1f)
	{
		//
		if (player->getSourceRectSprite().left >= 925)
		{
			player->setSourceRectSprite(sf::IntRect(1, 4, 75, 75));
		}
		//
		else
		{
			player->setSourceRectSprite(sf::IntRect(player->getSourceRectSprite().left + 77, 4, 75, 75));
		}
	}
}

//
void Animation::jumping(Player* player)
{
	m_clock.restart();
	player->setSourceRectSprite(sf::IntRect(1, 4, 75, 82));
	m_current->jumping(this);

	//
	/*if (m_clock.getElapsedTime().asSeconds() > 0.1f)
	{
		//
		if (player->getSourceRectSprite().left >= 925)
		{
			player->setSourceRectSprite(sf::IntRect(1, 4, 75, 75));
		}
		//
		else
		{
			player->setSourceRectSprite(sf::IntRect(player->getSourceRectSprite().left + 77, 4, 75, 75));
		}
	}*/
}

//
void Animation::falling(Player* player)
{
	m_clock.restart();
	player->setSourceRectSprite(sf::IntRect(1, 4, 75, 63));
	m_current->falling(this);
}

//
void Animation::landing(Player* player)
{

	m_current->landing(this);


	//
	/*if (m_clock.getElapsedTime().asSeconds() > 0.1f)
	{
		//
		if (player->getSourceRectSprite().left >= 925)
		{
			player->setSourceRectSprite(sf::IntRect(1, 4, 75, 75));
		}
		//
		else
		{
			player->setSourceRectSprite(sf::IntRect(player->getSourceRectSprite().left + 77, 4, 75, 75));
		}
	}*/
}

//
void Animation::update(Player* player)
{
	//
	if (player->getMoving() == false && player->getJumping() == false)
	{
		idle(player);
	}
	else if (player->getMoving() == true)
	{
		moving(player);
	}

	//
	if (player->getJumping() == true)
	{
		jumping(player);
	}
	else if (player->getFalling() == true)
	{
		falling(player);
	}
}

//
void Animation::setCurrent(State* current)
{
	m_current = current;
}

//
State* Animation::getCurrent()
{
	return m_current;
}