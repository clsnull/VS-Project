#include "SoundEngine.h"
#include <assert.h>
#include <iostream>

SoundEngine *SoundEngine::m_sInstance = nullptr;
bool SoundEngine::mMusicIsPlaying = false;
sf::Music SoundEngine::music;

sf::SoundBuffer SoundEngine::m_clickBuffer;
sf::Sound* SoundEngine::m_clickSound = nullptr;

sf::SoundBuffer SoundEngine::m_jumpBuffer;
sf::Sound* SoundEngine::m_jumpSound = nullptr;

SoundEngine::SoundEngine()
{
    assert(m_sInstance == nullptr);

    m_sInstance = this;
    if (!m_clickBuffer.loadFromFile("sound/click.wav"))
    {
        std::cout << "加载音频失败" << std::endl;
    };
    SoundEngine::m_clickSound = new sf::Sound(m_clickBuffer);
    if (!m_jumpBuffer.loadFromFile("sound/jump.wav"))
    {
        std::cout << "加载音频失败" << std::endl;
    }
    SoundEngine::m_jumpSound = new sf::Sound(m_jumpBuffer);
}

void SoundEngine::playClick()
{
    // SoundEngine::m_clickSound->play();
}

void SoundEngine::playJump()
{
    SoundEngine::m_jumpSound->play();
}

void SoundEngine::startMusic()
{
    music.openFromFile("music/music.wav");
    m_sInstance->music.play();
    m_sInstance->music.setLooping(true);
    mMusicIsPlaying = true;
}

void SoundEngine::pauseMusic()
{
    m_sInstance->music.pause();
    mMusicIsPlaying = false;
}
void SoundEngine::resumeMusic()
{
    m_sInstance->music.play();
    mMusicIsPlaying = true;
}
void SoundEngine::stopMusic()
{
    m_sInstance->music.stop();
    mMusicIsPlaying = false;
}

SoundEngine::~SoundEngine(){
    delete m_clickSound;
    delete m_jumpSound;
}