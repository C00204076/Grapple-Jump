//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:24 2 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#include "MusicManager.h"

//
MusicManager::MusicManager()
{
	initialise();
}

//
MusicManager::~MusicManager()
{

}

//
void MusicManager::initialise()
{
	loadSounds();
	//
	m_titleMOne.setPosition(0, 1, 10); // change its 3D position
	m_titleMOne.setVolume(35);
	//
	m_titleMTwo.setPosition(0, 1, 10); // change its 3D position
	m_titleMTwo.setVolume(35);
	//
	m_bmgMOne.setPosition(0, 1, 10); // change its 3D position
	m_bmgMOne.setVolume(35);
	//
	m_bmgMTwo.setPosition(0, 1, 10); // change its 3D position
	m_bmgMTwo.setVolume(35);
	//
	m_bmgMThree.setPosition(0, 1, 10); // change its 3D position
	m_bmgMThree.setVolume(35);

	//
	m_trackNum = 1;
	m_otherTrack = 3;

	m_played = false;
}

//
void MusicManager::loadSounds()
{
	//
	/*if (!m_bmgOne.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm03.ogg"))
	{
		std::cout << "Error! Unable to load bgm03.ogg from game files!" << std::endl;
	}
	//
	if (!m_bmgTwo.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm05.ogg"))
	{
		std::cout << "Error! Unable to load bgm05.ogg from game files!" << std::endl;
	}
	//
	if (!m_bmgThree.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/boss02.ogg"))
	{
		std::cout << "Error! Unable to load boss02.ogg from game files!" << std::endl;
	}

	//
	if (!m_titleOne.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent04.ogg"))
	{
		std::cout << "Error! Unable to load ivent04.ogg from game files!" << std::endl;
	}
	//
	if (!m_titleTwo.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent08.ogg"))
	{
		std::cout << "Error! Unable to load ivent08.ogg from game files!" << std::endl;
	}*/

	//
	/*if (!m_bmgOne.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm03.wav"))
	{
		std::cout << "Error! Unable to load bgm03.wav from game files!" << std::endl;
	}
	//
	if (!m_bmgTwo.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm05.wav"))
	{
		std::cout << "Error! Unable to load bgm05.wav from game files!" << std::endl;
	}
	//
	if (!m_bmgThree.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/boss02.wav"))
	{
		std::cout << "Error! Unable to load boss02.wav from game files!" << std::endl;
	}

	//
	if (!m_titleOne.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent04.wav"))
	{
		std::cout << "Error! Unable to load ivent04.wav from game files!" << std::endl;
	}
	//
	if (!m_titleTwo.loadFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent08.wav"))
	{
		std::cout << "Error! Unable to load ivent08.wav from game files!" << std::endl;
	}*/

	//
	if (!m_bmgMOne.openFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm03.ogg"))
	{
		std::cout << "Error! Unable to load bgm03.ogg from game files!" << std::endl;
	}
	//
	if (!m_bmgMTwo.openFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/bgm05.ogg"))
	{
		std::cout << "Error! Unable to load bgm05.ogg from game files!" << std::endl;
	}
	//
	if (!m_bmgMThree.openFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/boss02.ogg"))
	{
		std::cout << "Error! Unable to load boss02.ogg from game files!" << std::endl;
	}

	//
	if (!m_titleMOne.openFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent04.ogg"))
	{
		std::cout << "Error! Unable to load ivent04.ogg from game files!" << std::endl;
	}
	//
	if (!m_titleMTwo.openFromFile("../Grapple_Jump/ASSETS/AUDIO/BGM/ivent08.ogg"))
	{
		std::cout << "Error! Unable to load ivent08.ogg from game files!" << std::endl;
	}
}

//
void MusicManager::playMusic()
{
	//
	resetMusic();

	//
	if (m_played == false)
	{
		//
		if (m_trackNum == 1)
		{
			//
			m_titleMOne.setLoop(true);
			m_titleMOne.play();
			m_played = true;
		}
		//
		else if (m_trackNum == 2)
		{
			//
			m_titleMTwo.setLoop(true);
			m_titleMTwo.play();
			m_played = true;
		}
		//
		if (m_trackNum == 3)
		{
			m_bmgMOne.setLoop(true);
			m_bmgMOne.play();
			m_played = true;

		}
		//
		else if (m_trackNum == 4)
		{
			m_bmgMTwo.setLoop(true);
			m_bmgMTwo.play();
			m_played = true;
		}
		//
		else if (m_trackNum == 5)
		{
			m_bmgMThree.setLoop(true);
			m_bmgMThree.play();
			m_played = true;
		}
	}

	//
	if (m_trackNum < 1)
	{
		m_trackNum = 1;
	}
	//
	if (m_trackNum > 5)
	{
		m_trackNum = 5;
	}

	//
	if (m_titleTrack < 1)
	{
		m_titleTrack = 1;
	}
	//
	if (m_titleTrack > 2)
	{
		m_titleTrack = 2;
	}

	//
	if (m_otherTrack < 3)
	{
		m_otherTrack = 3;
	}
	//
	if (m_otherTrack > 5)
	{
		m_otherTrack = 5;
	}
}

//
void MusicManager::resetMusic()
{
	//
	if (m_trackNum == 1)
	{
		//m_titleMOne.stop();
		m_titleMTwo.stop();
		m_bmgMOne.stop();
		m_bmgMTwo.stop();
		m_bmgMThree.stop();
	}
	//
	if (m_trackNum == 2)
	{
		m_titleMOne.stop();
		//m_titleMTwo.stop();
		m_bmgMOne.stop();
		m_bmgMTwo.stop();
		m_bmgMThree.stop();
	}
	//
	if (m_trackNum == 3)
	{
		m_titleMOne.stop();
		m_titleMTwo.stop();
		//m_bmgMOne.stop();
		m_bmgMTwo.stop();
		m_bmgMThree.stop();
	}
	//
	if (m_trackNum == 4)
	{
		m_titleMOne.stop();
		m_titleMTwo.stop();
		m_bmgMOne.stop();
		//m_bmgMTwo.stop();
		m_bmgMThree.stop();
	}
	//
	if (m_trackNum == 5)
	{
		m_titleMOne.stop();
		m_titleMTwo.stop();
		m_bmgMOne.stop();
		m_bmgMTwo.stop();
		//m_bmgMThree.stop();
	}
}

//
void MusicManager::setTrackNum(int track)
{
	//
	if (track < 1)
	{
		track = 1;
	}
	//
	if (track > 5)
	{
		track = 5;
	}

	m_trackNum = track;
	m_played = false;
}

void MusicManager::setTitleTrack(int track)
{
	//
	if (track < 1)
	{
		track = 1;
	}
	//
	if (track > 2)
	{
		track = 2;
	}

	m_titleTrack = track;
}

//
void MusicManager::setOtherTrack(int track)
{
	//
	if (track < 3)
	{
		track = 3;
	}
	//
	if (track > 5)
	{
		track = 5;
	}

	m_otherTrack = track;
}

//
int MusicManager::getTrackNum()
{
	return m_trackNum;
}

//
int MusicManager::getTitleTrack()
{
	return m_titleTrack;
}

//
int MusicManager::getOtherTrack()
{
	return m_otherTrack;
}