// audio_handler.cpp

#include "audio_handler.h"
#include <iostream>

AudioHandler::AudioHandler()
{
    ::InitAudioDevice();
    m_deviceReady = ::IsAudioDeviceReady();
    
    if (m_deviceReady)
    {
        m_moveSfx = ::LoadSound("audio/tetromino_movement.wav");
        m_lockSfx  = ::LoadSound("audio/lock_piece.wav");
        m_lineClearSfx = ::LoadSound("audio/line_clear.wav");
        
        m_gameplayMusic = ::LoadMusicStream("audio/gameplay.wav");
        m_gameplayMusic.looping = true; // explicitly enable repeating
    }
}

AudioHandler::~AudioHandler()
{
    if (m_deviceReady)
    {
        ::UnloadSound(m_moveSfx);
        ::UnloadMusicStream(m_gameplayMusic);
        
        ::CloseAudioDevice();
    }
}

void AudioHandler::PlayGameplayMusic() const
{
    if (!m_deviceReady) return;
    ::PlayMusicStream(m_gameplayMusic);
}

void AudioHandler::StopGameplayMusic() const
{
    if (!m_deviceReady) return;
    ::StopMusicStream(m_gameplayMusic);
}

void AudioHandler::UpdateMusicStream() const
{
    if (!m_deviceReady) return;
    // Raylib needs to process chunk generation from the music buffer every tick
    ::UpdateMusicStream(m_gameplayMusic);
}

void AudioHandler::PlayMoveSound() const
{
    if (!m_deviceReady) return;
        ::PlaySound(m_moveSfx);
}

void AudioHandler::PlayLockSound() const
{
    if (!m_deviceReady) return;
        ::PlaySound(m_lockSfx);
}

void AudioHandler::PlayLineClearSound() const
{
    if (!m_deviceReady) return;
        ::PlaySound(m_lineClearSfx);
}

void AudioHandler::PlayGameOverSound() const
{
    if (!m_deviceReady) return;
    // TODO: ::PlaySound(m_gameoverSfx);
}
