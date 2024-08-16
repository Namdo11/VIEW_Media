#ifndef MEDIA_CONTROLLER_H
#define MEDIA_CONTROLLER_H

#include "MediaLibrary.cpp"
#include "MediaInterface.cpp"

class MediaController {
public:
    MediaController(MediaLibrary& lib, MediaInterface& inf ,MediaFile& media);
    //void runMusicPlayer(const std::string& musicDirectory); // ?
    //void run();
    void handleMusicControl();
    void handleMenuOption();

    void getMouseStatus(); // UI SDL2

private:
    void handlePlayPause();
    void handleNextMediaFile();
    void handlePreviousMediaFile();
    void handleIncreaseVolume();
    void handleDecreaseVolume();
    void handleMute();

    void handleMediaFileSelection(const std::string& _path);
    void handleAddMediaFiletoPlayList();
    void handleShowMetaData();

    void handleLibrary();
    void handlePlaylist();

    void handleManageLibrary();
    //void handleManagePlayList();

    //void handleUserInput();
   
    MediaLibrary& Library;
    MediaInterface& Interface;
};

#endif // MEDIA_CONTROLLER_H