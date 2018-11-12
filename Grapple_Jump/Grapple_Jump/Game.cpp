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
	m_window{ sf::VideoMode{2600, 1600, 32}, "Grapple Jump"},
	is_running{ true }, // When false, game will exit
	gameState{GameState::GAME}
{
	if (!m_playerTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Player.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_otherTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/OtherPlayer.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	if (!m_groundTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Ground.png"))
	{
		std::cout << "Error! Unable to load .png from game files!" << std::endl;
	}

	m_player = new Player(m_playerTexture, m_otherTexture);
	m_ground = new Ground(m_groundTexture);
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
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			//timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timeSinceLastUpdate);
			timeSinceLastUpdate = sf::Time::Zero;
		}
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
		m_player->update(deltaTime);
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
		break;

	}

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