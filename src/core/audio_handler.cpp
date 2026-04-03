// audio_handler.cpp

#include "audio_handler.h"
#include <iostream>

AudioHandler::AudioHandler()
{
    ::InitAudioDevice();
    m_deviceReady = ::IsAudioDeviceReady();
    
    if (m_deviceReady)
    {
        // Future: Load actual .wav files here
        // m_moveSfx = ::LoadSound("assets/move.wav");
    }
}

AudioHandler::~AudioHandler()
{
    if (m_deviceReady)
    {
        // Future: Unload specific sound assets
        // ::UnloadSound(m_moveSfx);
        
        ::CloseAudioDevice();
    }
}

void AudioHandler::PlayMoveSound() const
{
    if (!m_deviceReady) return;
    // ::PlaySound(m_moveSfx);
}

void AudioHandler::PlayLockSound() const
{
    if (!m_deviceReady) return;
    // ::PlaySound(m_lockSfx);
}

void AudioHandler::PlayClearSound() const
{
    if (!m_deviceReady) return;
    // ::PlaySound(m_clearSfx);
}

void AudioHandler::PlayGameOverSound() const
{
    if (!m_deviceReady) return;
    // ::PlaySound(m_gameoverSfx);
}
