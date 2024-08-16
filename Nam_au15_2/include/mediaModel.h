
#ifndef MEDIA_MODEL_H
#define MEDIA_MODEL_H

#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define MAX_VOLUME 100
#define MIN_VOLUME 0
#define AMOUNT_OF_CHANGE_VOLUME 10


class MusicModel {
public:
    MusicModel();
    ~MusicModel();
    bool init();
    bool loadMusic(const std::string &path);
    void playMusic();
    void pauseMusic();
    void stopMusic();
    void nextMusic();
    void previousMusic();

    void uninit();

    void increaseVolume();
    void decreaseVolume();
    int getVolume() const;
    std::string getCurrentTrackName() const;
    bool isPlaying() const;
    bool isPaused() const;

    void toggleMute(); // Thêm phương thức toggleMute
    bool isMuted() const;

    void loadMusicFiles(const std::string &directoryPath);
    const std::vector<std::string>& getMusicFiles() const;
    size_t getCurrentTrack() const;
    void setCurrentTrack(size_t track);

private:
    Mix_Music* music;
    bool is_playing=false;
    bool is_paused=false;
    std::vector<std::string> musicFiles;
    size_t currentTrack;
    int volume;
    bool muted;
    int lastVolume;
};

#endif //MEDIA_MODEL_H