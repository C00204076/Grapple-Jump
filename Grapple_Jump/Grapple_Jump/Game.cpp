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
	m_window{ sf::VideoMode{ 1500, 900, 32 }, "Grapple Jump" } ,
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

	if (!m_targetTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Target_Cursor.png"))
	{
		std::cout << "Error! Unable to load Target_Cursor.png from game files!" << std::endl;
	}

	if (!m_miniMapTexture.loadFromFile("../Grapple_Jump/ASSETS/IMAGES/Player_Head(mini-map).png"))
	{
		std::cout << "Error! Unable to load Player_Head(mini-map).png from game files!" << std::endl;
	}
}

//
void Game::initialise()
{
	loadTextures();

	m_splashScreen = new Splash();
	m_licenseScreen = new License();
	m_mainMenu = new MainMenu();
	m_gameOver = new GameOver();
	m_loading = new Loading();

	m_playerView.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_playerView.setSize(1500, 900);
	m_playerView.zoom(1.0f);

	m_miniMapView.reset(sf::FloatRect(0, 0, m_window.getSize().x / 2, m_window.getSize().y / 2));
	m_miniMapView.setViewport(sf::FloatRect(1.2f - (1.0f * m_miniMapView.getSize().x) / m_window.getSize().x - 0.04f,
											0.3f - (1.0f* m_miniMapView.getSize().y) / m_window.getSize().y - 0.02f,
											(1.0f * m_miniMapView.getSize().x) / m_window.getSize().x, 
											(1.0f * m_miniMapView.getSize().y) / m_window.getSize().y));
	m_miniMapView.zoom(25.0f);

	// Sets the mouse cursor's visiblility to false
	m_window.setMouseCursorVisible(false);

	// Sets the texture and origin of the new mouse Sprite
	m_targetSprite.setTexture(m_targetTexture);
	m_targetSprite.setOrigin(25, 25);

	m_player = new Player();
	m_miniPlayer = new Player();

	m_groundTest = new Ground(-250, 750, 4, 3);
	

	// Sets the default constructor and texture of the Ground
	for (int i = 0; i < 4; i++)
	{
		m_ground[i] = new Ground();
	}

	//
	//m_ground[1]->setPosition(sf::Vector2f(50, 350));
	m_ground[2]->setPosition(sf::Vector2f(320, 750));

	//m_ground = new Ground(m_groundTexture);
	// Sets the psition of the Ground
	//m_ground->setPosition(sf::Vector2f(0, 1400));

	// Sets the default constructor and texture of the Hook Points
	for (int i = 0; i < 7; i++)
	{
		m_hookPoint[i] = new HookPoint();
	}
	// Sets the positions of the Hook Points
	//m_hookPoint[0]->setPosition(sf::Vector2f(600, 1000));
	//m_hookPoint[1]->setPosition(sf::Vector2f(1250, 500));
	m_hookPoint[2]->setPosition(sf::Vector2f(50, 0));
	//m_hookPoint[3]->setPosition(sf::Vector2f(2100, 250));
	//m_hookPoint[4]->setPosition(sf::Vector2f(2550, 20));
	//m_hookPoint[5]->setPosition(sf::Vector2f(2550, 1350));
	//m_hookPoint[6]->setPosition(sf::Vector2f(50, 1350));

	m_miniMap = new MiniMap(m_miniPlayer);
	m_musicPlayer = new MusicManager();
	m_start = new Start();
	m_goal = new Goal();

	m_start->setPosition(sf::Vector2f(100, 700));
	m_goal->setPosition(sf::Vector2f(500, 700));

	m_player->setPosition(m_start->getPosition());
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

		//m_musicPlayer->playMusic();
		m_player->mouseCursor(m_window, m_playerView);
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
		case GameState::GAMEOVER:
			break;
		case GameState::LOADING:
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
		m_splashScreen->update(deltaTime);
		//
		if (m_splashScreen->getScreenTime() >= 1)
		{
			//
			m_loading->setPlay(false);
			m_loading->setMainMenu(true);
			m_loading->setGameOver(false);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
		}

		break;
	case GameState::LICENSE:
		m_licenseScreen->update(deltaTime);
		//
		if (m_licenseScreen->getScreenTime() >= 1)
		{
			//
			m_loading->setPlay(false);
			m_loading->setMainMenu(true);
			m_loading->setGameOver(false);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
		}

		break;
	case GameState::MAIN:
		m_mainMenu->update(deltaTime, m_player, m_window, m_musicPlayer, m_playerView);
		// If the Play button is pressed
		if (m_mainMenu->getPlayTime() == true)
		{
			//
			m_loading->setPlay(true);
			m_loading->setMainMenu(false);
			m_loading->setGameOver(false);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
			//
			m_player->setPosition(m_start->getPosition());
			m_player->setFalling(true);
			m_player->reset();
			m_mainMenu->setPlayTime(false);
		}

		break;
	case GameState::GAME:

		//
		m_miniMap->update(deltaTime, m_window, m_miniMapView);
		//
		m_start->update(deltaTime);
		//
		m_goal->update(deltaTime);

		//
		if (m_goal->playerCollision(m_player) == true)
		{
			//
			m_loading->setPlay(false);
			m_loading->setMainMenu(false);
			m_loading->setGameOver(true);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
			m_musicPlayer->setGameOverTrack(7);
			m_musicPlayer->setTrackNum(m_musicPlayer->getGameOverTrack());
			m_gameOver->setPlayTrack(true);
			m_gameOver->setWin(true);
			m_gameOver->setLose(false);
		}

		m_player->collosionWithGround(m_groundTest);

		// Updates the Ground and check if it is colliding with the player
		for (int i = 0; i < 4; i++)
		{
			m_player->collosionWithGround(m_ground[i]);
		}
		
		// Updates the array of Hook Points and checks if the Grappling Hook is colliding with any
		// Hook Point
		for (int i = 0; i < 7; i++) 
		{
			m_hookPoint[i]->update(deltaTime);
			m_player->grapplePointCollision(*m_hookPoint[i]);
		}
		m_player->update(deltaTime, m_playerView, true);
		
		
		m_miniPlayer->setPosition(m_player->getPosition());
		break;
	case GameState::GAMEOVER:
		m_gameOver->update(deltaTime, m_player, m_window, m_musicPlayer, m_playerView);
		
		// If the Replay button is pressed
		if (m_gameOver->getPlayTime() == true)
		{
			//
			m_loading->setPlay(true);
			m_loading->setMainMenu(false);
			m_loading->setGameOver(false);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
			//
			m_musicPlayer->setTrackNum(m_musicPlayer->getTitleTrack());
			//
			m_player->setPosition(m_start->getPosition());
			m_player->setFalling(true);
			m_player->reset();
			m_mainMenu->setPlayTime(false);
			//
			m_gameOver->setLose(false);
			m_gameOver->setWin(false);
			m_gameOver->setPlayTime(false);
			m_gameOver->setPlayTrack(true);
		}

		// If the  Return to Title button is press
		if (m_gameOver->getMainMenu() == true)
		{
			//
			m_loading->setPlay(false);
			m_loading->setMainMenu(true);
			m_loading->setGameOver(false);
			m_loading->setTimer(0);
			//
			setGameState(GameState::LOADING);
			//
			m_musicPlayer->setTitleTrack(m_musicPlayer->getTitleTrack());
			//
			m_gameOver->setLose(false);
			m_gameOver->setWin(false);
			m_gameOver->setMainMenu(false);
			m_gameOver->setPlayTrack(true);
		}
		
		break;
	case GameState::LOADING:
		m_loading->update(deltaTime, m_playerView);

		//
		if (m_loading->getTimer() > 150)
		{
			//
			if (m_loading->getPlay() == true)
			{
				setGameState(GameState::GAME);
				//
				m_musicPlayer->setTrackNum(m_musicPlayer->getTitleTrack());
				//
				m_player->setPosition(m_start->getPosition());
				m_player->setFalling(true);
				m_player->reset();
				m_mainMenu->setPlayTime(false);
				//
				m_gameOver->setLose(false);
				m_gameOver->setWin(false);
				m_gameOver->setPlayTime(false);
				m_gameOver->setPlayTrack(true);
			}
			//
			if (m_loading->getMainMenu() == true)
			{
				setGameState(GameState::MAIN);
				//
				m_musicPlayer->setTitleTrack(m_musicPlayer->getTitleTrack());
				//
				m_gameOver->setLose(false);
				m_gameOver->setWin(false);
				m_gameOver->setMainMenu(false);
				m_gameOver->setPlayTrack(true);
			}
			//
			if (m_loading->getGameOver() == true)
			{
				setGameState(GameState::GAMEOVER);
				//
				m_musicPlayer->setGameOverTrack(7);
				m_musicPlayer->setTrackNum(m_musicPlayer->getGameOverTrack());
				m_gameOver->setPlayTrack(true);
				m_gameOver->setWin(true);
				m_gameOver->setLose(false);
			}
		}
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
		m_splashScreen->render(m_window);
		break;
	case GameState::LICENSE:
		m_licenseScreen->render(m_window);
		break;
	case GameState::MAIN:
		m_mainMenu->render(m_window);

		//
		m_window.setView(m_playerView);
		break;
	case GameState::GAME:
		for (int k = 0, l = 0;
			k < 4, l < 7;
			k++, l++)
		{
			m_miniMap->draw(m_window, m_miniMapView, m_groundTest, m_hookPoint[l]);
		}

		//
		m_window.setView(m_playerView);

		//
		m_start->render(m_window);
		//
		m_goal->render(m_window);
		

		// Renders and draws the Player, Grappling Hook Sprites and Grappling Hook cable Line
		m_player->render(m_window, sf::Vector2f(1.0f, 1.0f));
		// Renders and draws the Ground Sprite
		for (int i = 0; i < 4; i++)
		{
			m_ground[i]->render(m_window);
		}

		m_groundTest->render(m_window);

		//m_ground->render(m_window);
		// Renders and draws the array of Hook Point Sprites
		for (int j = 0; j < 7; j++)
		{
			m_hookPoint[j]->render(m_window);
		}
		break;
	case GameState::GAMEOVER:
		//
		m_window.setView(m_playerView);
		m_gameOver->render(m_window);
		break;
	case GameState::LOADING:
		//
		m_window.setView(m_playerView);
		m_loading->render(m_window);
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