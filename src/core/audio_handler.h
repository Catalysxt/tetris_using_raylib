// audio_handler.h
//
// Encapsulates the Raylib audio device and sound playback.

#pragma once

#include <raylib.h>

class AudioHandler
{
public:
    AudioHandler();
    ~AudioHandler();

    // Non-copyable (manages hardware resources)
    AudioHandler(const AudioHandler&) = delete;
    AudioHandler& operator=(const AudioHandler&) = delete;

    // Music
    void PlayGameplayMusic() const;
    void StopGameplayMusic() const;
    void UpdateMusicStream() const; // Called every frame
    
    // Sounds
    void PlayMoveSound() const;
    void PlayLockSound() const;
    void PlayLineClearSound() const;
    void PlayGameOverSound() const;

private:
    // Sound assets 
    Sound m_moveSfx{};   
    Sound m_lockSfx{};
    Sound m_lineClearSfx{};

    // For background themes, we use Music instead of Sound
    // because Music streams from disk and handles looping properly.
    Music m_gameplayMusic{};

    // We track if the device successfully initialized
    bool m_deviceReady = false;
};
