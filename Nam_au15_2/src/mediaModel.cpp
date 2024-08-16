#include "mediaModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <filesystem>
#include <algorithm>

MusicModel::MusicModel()
    : music(nullptr), is_playing(false), is_paused(false), currentTrack(0), volume(MIX_MAX_VOLUME / 2), muted(false), lastVolume(MIX_MAX_VOLUME / 2) {}

MusicModel::~MusicModel() {
    uninit();
}

int MusicModel::getVolume() const {
    return volume;
}

void MusicModel::toggleMute() {
    muted = !muted;
    if (muted) {
        lastVolume = volume;
        volume = 0;
        Mix_VolumeMusic(volume);
    } else {
        volume = lastVolume;
        Mix_VolumeMusic(volume);
    }
}

bool MusicModel::isMuted() const {
    return muted;
}

std::string MusicModel::getCurrentTrackName() const {
    if (!musicFiles.empty() && currentTrack < musicFiles.size()) {
        size_t lastSlash = musicFiles[currentTrack].find_last_of("/\\");
        return musicFiles[currentTrack].substr(lastSlash + 1);
    }
    return "No track playing";
}

bool MusicModel::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool MusicModel::loadMusic(const std::string &path) {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    
    music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void MusicModel::playMusic() {
    if (musicFiles.empty()) {
        std::cout << "No music files loaded." << std::endl;
        return;
    }

    if (!is_playing) {
        if (is_paused) {
            Mix_ResumeMusic();
            is_paused = false;
        } else {
            if (!loadMusic(musicFiles[currentTrack])) {
                std::cout << "Failed to load the current track." << std::endl;
                return;
            }
            Mix_PlayMusic(music, -1); // -1 to loop infinitely
        }
        is_playing = true;
        std::cout << "Music playing." << std::endl;
    }
}

void MusicModel::pauseMusic() {
    if (is_playing && !is_paused) {
        Mix_PauseMusic();
        is_playing = false;
        is_paused = true;
        std::cout << "Music paused." << std::endl;
    }
}

void MusicModel::increaseVolume() {
    volume = std::min(MAX_VOLUME, volume + AMOUNT_OF_CHANGE_VOLUME); // Adjust volume range as needed
    Mix_VolumeMusic(volume);
    std::cout << "Volume increased to: " << volume << std::endl;
}

void MusicModel::decreaseVolume() {
    volume = std::max(MIN_VOLUME, volume - AMOUNT_OF_CHANGE_VOLUME); // Adjust volume range as needed
    Mix_VolumeMusic(volume);
    std::cout << "Volume decreased to: " << volume << std::endl;
}

void MusicModel::stopMusic() {
    Mix_HaltMusic();
    is_playing = false;
    is_paused = false;
    std::cout << "Music stopped." << std::endl;
}

void MusicModel::nextMusic() {
    if (musicFiles.empty()) {
        std::cout << "No music files loaded." << std::endl;
        return;
    }
    
    stopMusic();
    currentTrack = (currentTrack + 1) % musicFiles.size();
    std::cout << "----------------\nNext:\nCurrent track: " << musicFiles[currentTrack] << "\n";
    if (!loadMusic(musicFiles[currentTrack])) {
        std::cout << "Failed to load the next track." << std::endl;
        return;
    }
    playMusic();
}

void MusicModel::previousMusic() {
    if (musicFiles.empty()) {
        std::cout << "No music files loaded." << std::endl;
        return;
    }
    
    stopMusic();
    currentTrack = (currentTrack > 0) ? currentTrack - 1 : musicFiles.size() - 1;
    std::cout << "----------------\nBack:\nCurrent track: " << musicFiles[currentTrack] << "\n";
    if (!loadMusic(musicFiles[currentTrack])) {
        std::cout << "Failed to load the previous track." << std::endl;
        return;
    }
    playMusic();
}

void MusicModel::uninit() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    Mix_CloseAudio();  // Đóng audio mixer
}

bool MusicModel::isPlaying() const {
    return is_playing;
}

bool MusicModel::isPaused() const {
    return is_paused;
}

void MusicModel::loadMusicFiles(const std::string &directoryPath) {
    namespace fs = std::filesystem;
    musicFiles.clear(); // Clear any previously loaded files
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && 
            (entry.path().extension() == ".mp3" || entry.path().extension() == ".wav")) {
            musicFiles.push_back(entry.path().string());
        }
    }
}

const std::vector<std::string>& MusicModel::getMusicFiles() const {
    return musicFiles;
}

size_t MusicModel::getCurrentTrack() const {
    return currentTrack;
}

void MusicModel::setCurrentTrack(size_t track) {
    if (track < musicFiles.size()) {
        currentTrack = track;
    }
}
