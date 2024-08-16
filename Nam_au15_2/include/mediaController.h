
#ifndef MEDIA_CONTROLLER_H
#define MEDIA_CONTROLLER_H

#include "mediaModel.h"
#include "mediaView.h"

class MusicController {
public:
    MusicController(MusicModel& model, MusicView& view);
    
    // void runMusicPlayer(const std::string& musicDirectory);
    void getMouseStatus();

    void displayMenumusic();

private:

    void handlePlayPause();
    void handleNextTrack();
    void handlePreviousTrack();
    // void handleTrackSelection(int trackNumber);
    // void handleUserInput();
    void handleIncreaseVolume();
    void handleDecreaseVolume();
    void handleMute();
    void displayCurrentTrack();

    MusicModel& model;
    MusicView& view;
};

#endif //MEDIA_CONTROLLER_H
