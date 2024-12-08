#ifndef MEDIA_INTERFACE_H
#define MEDIA_INTERFACE_H

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

class MediaInterface{
private:
    void gotoxy(int x, int y);
public:
    void clearScreen();
    void displayMusicScreen();
    void displayMenuInter();
    void displayLibrary();
    void displayPlaylist();

    void displayLibManager();
    //void displayPlayListManager();
}; 

#endif // MEDIA_INTERFACE_H