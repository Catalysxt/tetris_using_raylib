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

    // Semantic playback methods
    void PlayMoveSound() const;
    void PlayLockSound() const;
    void PlayClearSound() const;
    void PlayGameOverSound() const;

private:
    // Sound assets — member variables so they live for the entire game session
    Sound m_moveSfx{};   // {} zero-initializes so it's safe to Unload even if never loaded

    // We track if the device successfully initialized
    bool m_deviceReady = false;
};
