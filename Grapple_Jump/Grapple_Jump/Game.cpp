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
	m_window{ sf::VideoMode{1500, 900, 32}, "Grapple Jump" } ,//sf::VideoMode{2600, 1600, 32}, "Grapple Jump" },
	is_running{ true }, // When false, game will exit
	gameState{ GameState::GAME }
{
	initialise();
}

/// <summary>
/// Default deconstructor
/// </summary>
Game::~Game()
{
	std::cout << "Game object destroyed" << std::endl;
}

//
void Game::loadTextures()
{
	if (!m_groundTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Ground-(small).png"))
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
}

//
void Game::initialise()
{
	loadTextures();

	m_playerView.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_playerView.setSize(1500, 900);
	m_playerView.zoom(1.0f);
	//m_playerView.zoom(2.0f);

	m_miniMapView.reset(sf::FloatRect(0, 0, m_window.getSize().x / 2, m_window.getSize().y / 2));
	m_miniMapView.setViewport(sf::FloatRect(1.2f - (1.0f * m_miniMapView.getSize().x) / m_window.getSize().x - 0.04f,
											0.3f - (1.0f* m_miniMapView.getSize().y) / m_window.getSize().y - 0.02f,
											(1.0f * m_miniMapView.getSize().x) / m_window.getSize().x, 
											(1.0f * m_miniMapView.getSize().y) / m_window.getSize().y));
	m_miniMapView.zoom(3.0f);

	// Sets the mouse cursor's visiblility to false
	m_window.setMouseCursorVisible(false);


	// Sets the texture and origin of the new mouse Sprite
	m_targetSprite.setTexture(m_targetTexture);
	m_targetSprite.setOrigin(25, 25);

	m_player = new Player();
	// Sets the default constructor and texture of the Ground
	for (int i = 0; i < 4; i++)
	{
		m_ground[i] = new Ground(m_groundTexture);
	}

	//
	//m_ground[1]->setPosition(sf::Vector2f(50, 350));
	m_ground[2]->setPosition(sf::Vector2f(120, 800));

	//m_ground = new Ground(m_groundTexture);
	// Sets the psition of the Ground
	//m_ground->setPosition(sf::Vector2f(0, 1400));

	// Sets the default constructor and texture of the Hook Points
	for (int i = 0; i < 7; i++)
	{
		m_hookPoint[i] = new HookPoint(m_hookTexture);
	}
	// Sets the positions of the Hook Points
	//m_hookPoint[0]->setPosition(sf::Vector2f(600, 1000));
	//m_hookPoint[1]->setPosition(sf::Vector2f(1250, 500));
	m_hookPoint[2]->setPosition(sf::Vector2f(50, 0));
	//m_hookPoint[3]->setPosition(sf::Vector2f(2100, 250));
	//m_hookPoint[4]->setPosition(sf::Vector2f(2550, 20));
	//m_hookPoint[5]->setPosition(sf::Vector2f(2550, 1350));
	//m_hookPoint[6]->setPosition(sf::Vector2f(50, 1350));

	m_tileMap = new TileMap();
	m_miniMap = new MiniMap();
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
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			//timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timeSinceLastUpdate);
			timeSinceLastUpdate = sf::Time::Zero;
		}

		m_targetSprite.setPosition(m_player->getMousePosition());

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
		//
		m_miniMap->update(deltaTime, m_player);

		// Updates the Ground and check if it is colliding with the player
		for (int i = 0; i < 4; i++)
		{
			m_ground[i]->update(deltaTime);
			m_player->checkAABBCollision(m_ground[i]->getAABB());
			AABB md = m_ground[i]->getAABB()->minkowskiDifference(m_player->getAABB());

			/*if (md.getMin().x <= 0 &&
				md.getMax().x >= 0 &&
				md.getMin().y <= 0 &&
				md.getMax().y >= 0)
			{
				m_penetrationVector += m_player->getAABB()->closestPointOnBoundsToPoint(m_ground[i]->getPosition());
				m_player->getAABB()->setCenter(m_player->getAABB()->getCenter().x + m_penetrationVector.x, 
					m_player->getAABB()->getCenter().y + m_penetrationVector.y);
					
				m_player->setSourceRectSprite(sf::IntRect(m_player->getPosition().x + m_penetrationVector.x, 
														  m_player->getPosition().y + m_penetrationVector.y, 75, 75));
				m_player->setPosition(sf::Vector2f(m_player->getPosition().x + m_penetrationVector.x, m_player->getPosition().y + m_penetrationVector.y));
			}*/
		}
		//m_ground->update(deltaTime);
		//m_player->collosionWithGround(*m_ground);
		//m_player->checkAABBCollision(m_ground->getAABB());
		// Updates the array of Hook Points and checks if the Grappling Hook is colliding with any
		// Hook Point
		for (int i = 0; i < 7; i++) 
		{
			m_hookPoint[i]->update(deltaTime);
			m_player->grapplePointCollision(*m_hookPoint[i]);
		}
		m_player->update(deltaTime, m_window, m_playerView);
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
		for (int k = 0, l = 0;
			k < 4, l < 7;
			k++, l++)
		{
			m_miniMap->draw(m_window, m_miniMapView, m_player, m_ground[k], m_hookPoint[l]);
		}

		//
		m_window.setView(m_playerView);

		

		//
		//m_tileMap->draw(m_window);

		// Renders and draws the Player, Grappling Hook Sprites and Grappling Hook cable Line
		m_player->render(m_window);
		// Renders and draws the Ground Sprite
		for (int i = 0; i < 4; i++)
		{
			m_ground[i]->render(m_window);
		}

		//m_ground->render(m_window);
		// Renders and draws the array of Hook Point Sprites
		for (int j = 0; j < 7; j++)
		{
			m_hookPoint[j]->render(m_window);
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