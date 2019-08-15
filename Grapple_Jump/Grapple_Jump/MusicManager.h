//
// C00204076
// Brandon Seah-Dempsey
// Started at 17:00 2 August 2019
// Finished at 
// Time Taken: 
// Known Bugs: 

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "SFML/Audio.hpp"

#include <iostream>

//../Grapple_Jump/ASSETS/AUDIO

//
class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	void playMusic();

	void setTrackNum(int track);
	void setTitleTrack(int track);
	void setOtherTrack(int track);
	
	int getTrackNum();
	int getTitleTrack();
	int getOtherTrack();

private:
	void initialise();
	void loadSounds();

	void resetMusic();
	
	//
	int m_trackNum, m_state, m_titleTrack, m_otherTrack;
	//
	sf::Music m_bmgMOne, m_bmgMTwo, m_bmgMThree;
	sf::Music m_titleMOne, m_titleMTwo;
	//
	bool m_played;
};

#endif // !MUSICMANAGER_H
