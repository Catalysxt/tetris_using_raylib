// audio_handler.h
//
// Encapsulates the Raylib audio device and sound playback.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 6)
// ============================================================
// - Facade Pattern & RAII:
//   This class hides the C-style Raylib audio initialization and
//   ensures CloseAudioDevice() is always called via the destructor.
//   It provides semantic methods (PlayLockSound) so game logic
//   doesn't need to load or manage specific .wav files.
// ============================================================

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
    // Placeholders for future loaded sound assets
    // Sound m_moveSfx;
    // Sound m_lockSfx;
    
    // We track if the device successfully initialized
    bool m_deviceReady = false;
};
