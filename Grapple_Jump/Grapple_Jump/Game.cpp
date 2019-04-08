//
// C00204076
// Brandon Seah-Dempsey
// Started at 9:48 31 October 2018
// Finished at
// Time Taken:
// Known Bugs:

#include "Game.h"

//
Game::Game() :
	// sf::VideoMode{1500, 900, 32}, "Grapple Jump" } for at home work
	m_window{ sf::VideoMode{2600, 1600, 32}, "Grapple Jump" },
	is_running{ true }, // When false, game will exit
	gameState{ GameState::GAME }
{
	m_window.setMouseCursorVisible(false);

	if (!m_groundTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Ground.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_hookTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Block.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_targetTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Target_Cursor.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	m_targetSprite.setTexture(m_targetTexture);
	m_targetSprite.setOrigin(25, 25);

	m_player = new Player();
	//
	for (int i = 0; i < 2; i++)
	{
		m_ground[i] = new Ground(m_groundTexture);
	}
	//
	m_ground[0]->setPosition(sf::Vector2f(0, 1400));
	m_ground[1]->setPosition(sf::Vector2f(2300, 650));

	//
	for (int i = 0; i < 6; i++)
	{
		m_hookPoint[i] = new HookPoint(m_hookTexture);
	}
	//
	m_hookPoint[0]->setPosition(sf::Vector2f(80, 1000));
	m_hookPoint[1]->setPosition(sf::Vector2f(700, 600));
	m_hookPoint[2]->setPosition(sf::Vector2f(1500, 400));
	m_hookPoint[3]->setPosition(sf::Vector2f());
	m_hookPoint[4]->setPosition(sf::Vector2f());
	m_hookPoint[5]->setPosition(sf::Vector2f());

}

//
Game::~Game()
{
	std::cout << "Game object destroyed" << std::endl;
}

/// <summary>
/// 
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		m_mousePosition = sf::Mouse::getPosition(m_window);

		m_mouseX = m_mousePosition.x;
		m_mouseY = m_mousePosition.y;
		m_mouseVector = sf::Vector2f(m_mouseX, m_mouseY);

		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			//timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timeSinceLastUpdate);
			timeSinceLastUpdate = sf::Time::Zero;
		}

		m_targetSprite.setPosition(m_mouseVector);

		render();
	}
}

/// <summary>
/// 
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				is_running = false;
			}
		}
		processGameEvents(event);
	}
}

/// <summary>
/// Detect and handle keyboard input.
/// </summary>
/// <param name=""></param>
void Game::processGameEvents(sf::Event& event)
{
	//Check if the event is a mouse release event

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		//m_keyhandler.updateKey(event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		//m_keyhandler.updateKey(event.key.code, false);
		break;
	default:
		break;
	}
}

/// <summary>
/// 
/// </summary>
void Game::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}

		//Updates game based on current state
		switch (gameState)
		{
		case GameState::SPLASH:
			break;
		case GameState::LICENSE:
			break;
		case GameState::MAIN:
			break;
		case GameState::GAME:

			break;
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="t_deltaTime"></param>
void Game::update(sf::Time deltaTime)
{
	if (!is_running)
	{
		m_window.close();
	}

	


	//Updates game based on current state
	switch (gameState)
	{
	case GameState::SPLASH:
		break;
	case GameState::LICENSE:
		break;
	case GameState::MAIN:
		break;
	case GameState::GAME:
		//
		for (int i = 0; i < 2; i++)
		{
			m_ground[i]->update(deltaTime);
			m_player->collosionWithGround(*m_ground[i]);
		}

		//
		for (int i = 0; i < 6; i++) 
		{
			m_hookPoint[i]->update(deltaTime);
			m_player->grapplePointCollision(*m_hookPoint[i]);
		}
		m_player->update(deltaTime, m_window);
		
		break;
	}
}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black); //Set background to black

	//Draw objects based on current gamestate
	switch (gameState)
	{
	case GameState::SPLASH:
		break;
	case GameState::LICENSE:
		break;
	case GameState::MAIN:
		break;
	case GameState::GAME:
		m_player->render(m_window);
		//
		for (int i = 0; i < 2; i++)
		{
			m_ground[i]->render(m_window);
		}

		//
		for (int i = 0; i < 6; i++)
		{
			m_hookPoint[i]->render(m_window);
		}
		break;
	}

	m_window.draw(m_targetSprite);

	m_window.display();
}

/// <summary>
/// 
/// </summary>
/// <param name="gameMode"></param>
void Game::setGameState(GameState gameMode)
{
	gameState = gameMode;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
GameState Game::getGameState()
{
	return gameState;
}