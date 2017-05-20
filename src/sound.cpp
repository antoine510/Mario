#include "sound.h"
#include "filetool.h"

/**Global Var**/
SoundStack* soundStack;

//! \brief Initializes the sound library and loads the sounds
//! This constructor sets FMOD up, creates the actual soundstack and loads every sounds and musics
//!
Sound::Sound() {
#ifndef SOUND_MUTE
	result = FMOD::System_Create(&m_system);
	if(result != FMOD_OK) std::cerr << "FMOD error while creating system\n";

	result = m_system->init(8, FMOD_INIT_NORMAL, NULL);
	if(result != FMOD_OK) std::cerr << "FMOD error " << result << " while initializing system\n";
#endif

	soundStack = new SoundStack;

#ifndef SOUND_MUTE
	if(loadEverySound()) std::cerr << "Sound assets loading failed\n";

	//Initialization of music channel
	playMusic(Musics::OVERWORLD);
	pauseMusic(true);
#endif

	m_currentMusic = Musics::OVERWORLD;
}

//! \brief Plays all the sounds on the soundstack
//! This function plays the sounds and musics on the stack and pops them out
//!
void Sound::playAll() {
#ifndef SOUND_MUTE
	std::vector<Sounds>& soundsToPlay = soundStack->getSoundsToPlay();
	m_system->update();

	if(soundStack->musicHasChanged()) {
		changeMusic(soundStack->activeMusic());
		soundStack->musicUpdated();
	}

	for(unsigned int i = 0; i < soundsToPlay.size(); i++) {
		playSound(soundsToPlay[i]);
	}
	soundsToPlay.clear();
#endif
}

bool Sound::loadEverySound() {
	xmlDocPtr soundDoc = parseXML("audioAssets/sounds.xml");
	xmlNodePtr soundsN = xmlDocGetRootElement(soundDoc)->xmlChildrenNode;
	bypassText(soundsN);
	xmlNodePtr soundN = soundsN->children;
	bypassText(soundN);

	while(soundN) {
		std::string path = asString(soundsN, "prefix") + asString(soundN, "path");
		if(loadSound(path.c_str(), asInt(soundN, "id"))) return true;
		switchNextNode(soundN);
	}

	switchNextNode(soundsN);
	xmlNodePtr musicN = soundsN->children;
	bypassText(musicN);

	while(musicN) {
		std::string path = asString(soundsN, "prefix") + asString(musicN, "path");
		loadMusic(path.c_str(), asInt(musicN, "id"));
		switchNextNode(musicN);
	}

	xmlFreeDoc(soundDoc);
	return false;
}

bool Sound::loadSound(const char path[], unsigned int index) {
	m_sounds.resize(index + 1, NULL);

	result = m_system->createSound(path, FMOD_CREATESAMPLE, 0, &m_sounds[index]);
	if(result != FMOD_OK) { std::cerr << "FMOD error while loading sound : " << path << std::endl; return true; }
	return false;
}

void Sound::loadMusic(const char path[], unsigned int index) {
	m_musics.resize(index + 1, NULL);

	result = m_system->createSound(path, FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &m_musics[index]);
	if(result != FMOD_OK) std::cerr << "FMOD error while loading music : " << path << std::endl;

	result = m_musics[index]->setLoopCount(-1);
	if(result != FMOD_OK) std::cerr << "FMOD error while setting loop count of music : " << path << std::endl;
}

void Sound::playSound(Sounds sound) {
	result = m_system->playSound(m_sounds[(int)sound], nullptr, 0, NULL);
	if(result != FMOD_OK) std::cerr << "FMOD error while playing sound. soundFlag : " << (int)sound << std::endl;
}

void Sound::playMusic(Musics music) {
	m_musicChannel->stop();

	result = m_system->playSound(m_musics[(int)music], nullptr, false, &m_musicChannel);
	if(result != FMOD_OK) std::cerr << "FMOD error while playing music. musicFlag : " << (int)music << std::endl;

	m_currentMusic = music;
}

void Sound::pauseMusic(bool pause) {
	result = m_musicChannel->setPaused(pause);
	if(result != FMOD_OK) std::cerr << "FMOD error while pausing the music\n";
}

void Sound::changeMusic(Musics music) {
	if(music == Musics::NO_MUSIC) {
		pauseMusic(true);
	} else if(music != m_currentMusic) {
		result = m_musicChannel->setPosition(0, FMOD_TIMEUNIT_MS);
		if(result != FMOD_OK) std::cerr << "FMOD error while reseting music position\n";

		playMusic(music);
	} else {
		pauseMusic(false);
	}
}

void Sound::deleteEverySound() {
	m_sounds.erase(m_sounds.begin(), m_sounds.end());
	m_musics.erase(m_musics.begin(), m_musics.end());
}

//! \brief Deletes the sound system
//!
Sound::~Sound() {
	delete soundStack;
	deleteEverySound();
#ifndef SOUND_MUTE
	m_system->close();
	m_system->release();
#endif
}


