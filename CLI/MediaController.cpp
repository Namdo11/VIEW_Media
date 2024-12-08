#include "MediaController.h"

MediaController::MediaController(MediaLibrary& lib, MediaInterface& inf, MediaFile& media)
    : Library(lib), Interface(inf) MediaFile(media){}

// void MediaController::run() {
//     bool quit = false;
//     SDL_Event e;

//     while (!quit) {
//         while (SDL_PollEvent(&e) != 0) {
//             if (e.type == SDL_QUIT) {
//                 quit = true;
//             } else if (e.type == SDL_MOUSEBUTTONDOWN) {
//                 int x, y;
//                 SDL_GetMouseState(&x, &y);

//                 if (x >= 10 && x <= 120 && y >= 10 && y <= 120) {
//                     handlePreviousMediaFile();
//                 } else if (x >= 130 && x <= 240 && y >= 10 && y <= 120) {
//                     handlePlayPause();
//                 } else if (x >= 250 && x <= 360 && y >= 10 && y <= 120) {
//                     handleNextMediaFile();
//                 }
//             }
//         }

//         //Interface.render();
//     }
// }

void MediaController::handlePlayPause() {
    std::shared_ptr<MediaFile> media = Library.getCurrentMediaFile();
    if (media->isPlaying()) media->pause();
    else media->play();
}

void MediaController::handleNextMediaFile() {
    Library.settoNextMediaFileinLibrary();
    Library.getCurrentMediaFile()->load();
}

void MediaController::handlePreviousMediaFile() {
    Library.settoPrevMediaFileinLibrary();
    Library.getCurrentMediaFile()->load();
}

void MediaController::handleIncreaseVolume(){
    media.increaseVolume();
}

void MediaController::handleDecreaseVolume(){
    media.decreaseVolume();
}

void MediaController::handleMute(){
    moedia.toggleMute();
    if (media.isMuted()) {
        std::cout << "Music is muted. Volume was: " << media.getVolume() << std::endl;
    } else {
        std::cout << "Music is unmuted. Current volume: " << media.getVolume() << std::endl;
    }
}
void MediaController::handleMediaFileSelection(const std::string& _path) {
    std::shared_ptr<MediaFile> media = Library.getCurrentMediaFile();
    if (media) media->stop();
    Library.setCurrentMediaFile(_path);
    media = Library.getCurrentMediaFile();
    media->load(); // load metadata and music
    //media->play();
}

void MediaController::handleAddMediaFiletoPlayList() {
    std::cout << "\nEnter PlayList name: ";
    std::string name;
    std::cin >> name;
    std::shared_ptr<MediaFile> media = Library.getCurrentMediaFile();
    Library.addMediaFiletoPlayList(name, media->getPath());
    // xoa dong nay di tren cmd
}

void MediaController::handleShowMetaData() {
    Library.getCurrentMediaFile()->displayMetadata();
}

enum {
    MENU=0, SHOWDATA, PREV, PLAYPAUSE, NEXT, ADDTOPLAYLIST
};

void MediaController::handleMusicControl() {
    Interface.displayMusicScreen();
    while(1) 
    {   int choice;
        std::cin >> choice;
        switch (choice)
        {
        case MENU:
            Interface.displayMenuInter();
            goto QUIT;
        case SHOWDATA:
            handleShowMetaData();
            break;
        case PREV:
            handlePreviousMediaFile();
            break;
        case PLAYPAUSE:
            handlePlayPause();
            break;
        case NEXT:
            handleNextMediaFile();
            break;
        case ADDTOPLAYLIST:
            handleAddMediaFiletoPlayList();
            break;

        default:
            break;
        }
        continue;
        QUIT: break;
    }
}

void MediaController::handleLibrary(){
    int number = 1;
    for (const auto& [path, mediaFile] : Library.getAllMediaFiles()) {
        std::cout << number << "-" << mediaFile->getPath() << "\n";
        number++;
    }
}

void MediaController::handlePlaylist(){
    int number = 1;
    for (const auto& [path, playlist] : Library.getAllPlayList()) {
        std::cout << number << "-" << playlist->getName() << "\n";
        number++;
    }
}

void MediaController::handleMenuOption() {
    Interface.displayMenuInter();
    while(1){
        int choice;
        std::cout<<"Choose:";
        std::cin>> choice;

        switch (choice)
        {
        case 1:
            Interface.displayLibrary();
            handleLibrary();
            break;
        case 2:
            Interface.displayPlaylist();
            handlePlaylist();
            break;
        case 3:
            handleManageLibrary();
            break;
        case 4:
            goto EXIT;
        default:
            break;
        }
        continue;
        EXIT: break;
    }

}

enum {
    ADD=0, REMOVE, GET_INFO, EXIT
};

void MediaController::handleManageLibrary() {
    Interface.displayLibManager();
    while(1)
        {int option;
        std::string path;
        std::cin >> option;
        auto _l = [](){
            std::cout << "Enter file path: ";
            std::cin >> path;};
        switch (option)
        {
        case ADD:
            _l();
            Library.addNewMediaFile(path);
            break;
        case REMOVE:
            _l();
            Library.removeMediaFilebyPath(path);
            break;
        case GET_INFO:
            _l();
            Library.getMediaFilebyPath()->displayMetadata();
            break;
        case EXIT:
            Interface.displayMenuInter();
            goto QUITLIB;
        default:
            break;
        }
        continue;
        QUITLIB: break;
    }
}

// void MusicController::handleUserInput() {
//     std::string input;
//     std::cout << "Enter command (p: play/pause, n: next, b: previous, s: stop, q: quit): ";
//     std::cin >> input;

//     if (input == "p") {
//         handlePlayPause();
//     } else if (input == "n") {
//         handleNextTrack();
//     } else if (input == "b") {
//         handlePreviousTrack();
//     } else if (input == "s") {
//         Library.getCurrentMediaFile()->stop();
//     } else if (input == "q") {
//         // Quit will be handled in the main loop
//     } else {
//         try {
//             int trackNumber = std::stoi(input);
//             handleTrackSelection(trackNumber);
//         } catch (const std::invalid_argument&) {
//             std::cout << "Unknown command." << std::endl;
//         }
//     }
// }