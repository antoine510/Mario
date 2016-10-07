#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "common.h"
#include <fmod.h>

#define SOUND_NO_SOUND 0
#define SOUND_COIN 1
#define SOUND_JUMP 2
#define SOUND_STOMP_ENEMY 3
#define SOUND_BREAK_BLOCK 4
#define SOUND_HURT 5
#define SOUND_POWERUP 6
#define SOUND_PLAYERDEATH 7
#define SOUND_WIN 8
#define SOUND_MENU_SELECTION 9
#define SOUND_MENU_CURSOR 10
#define SOUND_FIREBALL 11
#define SOUND_PLAYERDEATH_LITE 12

#define MUSIC_NO_MUSIC 0
#define MUSIC_OVERWORLD 1
#define MUSIC_MENU 2

//#define SOUND_MUTE

//! \brief Sound and music playing queue
//!
class SoundStack
{
    public:
                            //! \brief Adds a sound to the stack \param soundFlag The sound flag
        inline void addToStack(int soundFlag) {m_soundsToPlay.push_back(soundFlag);}
                            //! \brief Transmits the sounds to play \return The vector of flags
        inline std::vector<int>& getSoundsToPlay() {return m_soundsToPlay;}

                            //! \brief Adds a music to the stack \param musicFlag The music flag
        inline void changeMusic(int musicFlag) {m_music = musicFlag; m_musicChanged = true;}
                            //! \brief Stops the playing music
        inline void stopMusic() {m_music = 0; m_musicChanged = true;}
                            //! \brief Getter \return Has the music changed
        inline bool musicHasChanged () {return m_musicChanged;}
                            //! \brief Getter \return Active music flag
        inline int activeMusic () {return m_music;}
                            //! \brief The music was updated
        inline void musicUpdated() {m_musicChanged = false;}

    private:
        std::vector<int> m_soundsToPlay;
        int m_music;
        bool m_musicChanged;
};

/** Global var makes the code way more understandable and maintainable**/
extern SoundStack* soundStack;

//! \brief Handles the loading and playing of sounds
//!
class Sound
{
    public:
        Sound();
        void playAll();
        ~Sound();

    private:

        bool loadEverySound();
        bool loadSound(const char path[], unsigned int index);
        void loadMusic(const char path[], unsigned int index);
        void deleteEverySound();

        void playSound(int soundFlag);
        void playMusic(int musicFlag);
        void pauseMusic(bool pause);

        void changeMusic(int musicFlag);

        FMOD_SYSTEM* m_system;
        FMOD_RESULT result;

        std::vector<FMOD_SOUND*> m_sounds;
        std::vector<FMOD_SOUND*> m_musics;
        FMOD_CHANNEL* m_musicChannel;

        int m_currentMusicFlag;
};

#endif // SOUND_H_INCLUDED
