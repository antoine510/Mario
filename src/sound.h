#pragma once

#include "common.h"
#include <fmod.hpp>

#define SOUND_MUTE

enum class Sounds {
	NO_SOUND = 0, COIN, JUMP, STOMP_ENEMY, BREAK_BLOCK, HURT, POWERUP, PLAYERDEATH, WIN, MENU_SELECTION, MENU_CURSOR, FIREBALL, PLAYERDEATH_LITE
};

enum class Musics {
	NO_MUSIC = 0, OVERWORLD, MENU
};

//! \brief Sound and music playing queue
//!
class SoundStack {
public:
	//! \brief Adds a sound to the stack \param soundFlag The sound flag
	inline void addToStack(Sounds sound) { m_soundsToPlay.push_back(sound); }
	//! \brief Transmits the sounds to play \return The vector of flags
	inline std::vector<Sounds>& getSoundsToPlay() { return m_soundsToPlay; }

	//! \brief Adds a music to the stack \param musicFlag The music flag
	inline void changeMusic(Musics music) { m_music = music; m_musicChanged = true; }
	//! \brief Stops the playing music
	inline void stopMusic() { m_music = Musics::NO_MUSIC; m_musicChanged = true; }
	//! \brief Getter \return Has the music changed
	inline bool musicHasChanged() { return m_musicChanged; }
	//! \brief Getter \return Active music flag
	inline Musics activeMusic() { return m_music; }
	//! \brief The music was updated
	inline void musicUpdated() { m_musicChanged = false; }

private:
	std::vector<Sounds> m_soundsToPlay;
	Musics m_music;
	bool m_musicChanged;
};

/** Global var makes the code way more understandable and maintainable**/
extern SoundStack* soundStack;

//! \brief Handles the loading and playing of sounds
//!
class Sound {
public:
	Sound();
	void playAll();
	~Sound();

private:

	bool loadEverySound();
	bool loadSound(const char path[], unsigned int index);
	void loadMusic(const char path[], unsigned int index);
	void deleteEverySound();

	void playSound(Sounds sound);
	void playMusic(Musics music);
	void pauseMusic(bool pause);

	void changeMusic(Musics musicFlag);

	FMOD::System* m_system;
	FMOD_RESULT result;

	std::vector<FMOD::Sound*> m_sounds;
	std::vector<FMOD::Sound*> m_musics;
	FMOD::Channel* m_musicChannel;

	Musics m_currentMusic;
};

