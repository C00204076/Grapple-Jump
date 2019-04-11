// Sets the methods, functions and changes of the variables related to Game header file
// C00204076
// Brandon Seah-Dempsey
// Started at 9:48 31 October 2018
// Finished at 15:07 11 April 2019
// Time Taken: 4 hours 39 minutes
// Known Bugs: None

#include "Game.h"

/// <summary>
/// Default constructor
/// </summary>
Game::Game() :
	// sf::VideoMode{1500, 900, 32}, "Grapple Jump" } for at home work
	m_window{ sf::VideoMode{2600, 1600, 32}, "Grapple Jump" },
	is_running{ true }, // When false, game will exit
	gameState{ GameState::GAME }
{
	// Sets the mouse cursor's visiblility to false
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
	// Sets the texture and origin of the new mouse Sprite
	m_targetSprite.setTexture(m_targetTexture);
	m_targetSprite.setOrigin(25, 25);

	m_player = new Player();
	// Sets the default constructor and texture of the Ground
	m_ground = new Ground(m_groundTexture);
	// Sets the psition of the Ground
	m_ground->setPosition(sf::Vector2f(0, 1400));

	// Sets the default constructor and texture of the Hook Points
	for (int i = 0; i < 7; i++)
	{
		m_hookPoint[i] = new HookPoint(m_hookTexture);
	}
	// Sets the positions of the Hook Points
	m_hookPoint[0]->setPosition(sf::Vector2f(600, 1000));
	m_hookPoint[1]->setPosition(sf::Vector2f(1250, 500));
	m_hookPoint[2]->setPosition(sf::Vector2f(50, 0));
	m_hookPoint[3]->setPosition(sf::Vector2f(2100, 250));
	m_hookPoint[4]->setPosition(sf::Vector2f(2550, 20));
	m_hookPoint[5]->setPosition(sf::Vector2f(2550, 1350));
	m_hookPoint[6]->setPosition(sf::Vector2f(50, 1350));
}

/// <summary>
/// Default deconstructor
/// </summary>
Game::~Game()
{
	std::cout << "Game object destroyed" << std::endl;
}

/// <summary>
/// Calls all methods needed to run game, such as update and render
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		// Gets the mouse position relative to the game's window
		m_mousePosition = sf::Mouse::getPosition(m_window);
		// Set the mouse X and Y to floats, then to Vector2f; as a means of converting Vector2i
		// to Vector2f
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
/// Calls and updates any method of game objects needed for gameplay
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
		// Updates the Ground and check if it is colliding with the player
		m_ground->update(deltaTime);
		m_player->collosionWithGround(*m_ground);
		// Updates the array of Hook Points and checks if the Grappling Hook is colliding with any
		// Hook Point
		for (int i = 0; i < 7; i++) 
		{
			m_hookPoint[i]->update(deltaTime);
			m_player->grapplePointCollision(*m_hookPoint[i]);
		}
		m_player->update(deltaTime, m_window);
		break;
	}
}

/// <summary>
/// Renders and draws the Sprites of the different game object sprites
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
		// Renders and draws the Player, Grappling Hook Sprites and Grappling Hook cable Line
		m_player->render(m_window);
		// Renders and draws the Ground Sprite
		m_ground->render(m_window);
		// Renders and draws the array of Hook Point Sprites
		for (int i = 0; i < 7; i++)
		{
			m_hookPoint[i]->render(m_window);
		}
		break;
	}

	m_window.draw(m_targetSprite);

	m_window.display();
}

/// <summary>
/// Sets the game state to the given arguement
/// </summary>
/// <param name="gameMode"></param>
void Game::setGameState(GameState gameMode)
{
	gameState = gameMode;
}

/// <summary>
/// Returns the current value of the game state
/// </summary>
/// <returns></returns>
GameState Game::getGameState()
{
	return gameState;
}