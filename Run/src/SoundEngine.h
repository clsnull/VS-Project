#pragma once
#include <SFML/Audio.hpp>

class SoundEngine
{
private:
    static sf::Music music;

    static sf::SoundBuffer m_clickBuffer;
    static sf::Sound* m_clickSound;

    static sf::SoundBuffer m_jumpBuffer;
    static sf::Sound* m_jumpSound;

    static sf::SoundBuffer mFireballLaunchBuffer;
    static sf::Sound mFireballLaunchSound;

public:
    SoundEngine();
    static SoundEngine *m_sInstance;
    static bool mMusicIsPlaying;

    static void startMusic();
    static void pauseMusic();
    static void resumeMusic();
    static void stopMusic();

    static void playClick();
    static void playJump();
    ~SoundEngine();
};
