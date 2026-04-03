// audio_handler.cpp

#include "audio_handler.h"
#include <iostream>

AudioHandler::AudioHandler()
{
    ::InitAudioDevice();
    m_deviceReady = ::IsAudioDeviceReady();
    
    if (m_deviceReady)
    {
        // Assign directly to the member variable so it persists beyond this function
        m_moveSfx = ::LoadSound("audio/tetromino_movement.wav");
    }
}

AudioHandler::~AudioHandler()
{
    if (m_deviceReady)
    {
        // RAII: unload assets before closing the device
        ::UnloadSound(m_moveSfx);

        ::CloseAudioDevice();
    }
}

void AudioHandler::PlayMoveSound() const
{
    if (!m_deviceReady) return;
    ::PlaySound(m_moveSfx);
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
