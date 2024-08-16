#include "mediaController.h"
#include <iostream>
#include <SDL2/SDL.h>

MusicController::MusicController(MusicModel& model, MusicView& view)
    : model(model), view(view) {}


void MusicController::displayCurrentTrack() {
    std::cout << "Current track: " << model.getCurrentTrackName() << std::endl;
}

void MusicController::handleMute() {
    model.toggleMute();
    if (model.isMuted()) {
        std::cout << "Music is muted. Volume was: " << model.getVolume() << std::endl;
    } else {
        std::cout << "Music is unmuted. Current volume: " << model.getVolume() << std::endl;
    }
}

void MusicController::getMouseStatus() {
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x >= 220 && x <= 330 && y >= 480 && y <= 590) {
                    handlePreviousTrack();
                } else if (x >= 340 && x <= 450 && y >= 480 && y <= 590) {
                    handlePlayPause();
                } else if (x >= 460 && x <= 560 && y >= 480 && y <= 590) {
                    handleNextTrack();
                } else if (x >= 580 && x <= 620 && y >= 520 && y <= 560) {
                    handleIncreaseVolume();
                } else if (x >= 630 && x <= 670 && y >= 520 && y <= 560) {
                    handleDecreaseVolume();
                } else if (x >= 680 && x <= 720 && y >= 520 && y <= 560) {
                    handleMute();
                }
            }
        }

        view.render();

        // Cập nhật nội dung của cửa sổ
        SDL_RenderPresent(view.getRenderer());
    }
}

void MusicController::handlePlayPause() {
    if (model.isPlaying()) {
        model.pauseMusic();
    } else {
        model.playMusic();
    }
}

void MusicController::handleIncreaseVolume() {
    model.increaseVolume(); // Tăng âm lượng lên 10 đơn vị
}

void MusicController::handleDecreaseVolume() {
    model.decreaseVolume(); // Giảm âm lượng đi 10 đơn vị
}

void MusicController::handleNextTrack() {
    model.nextMusic();
}

void MusicController::handlePreviousTrack() {
    model.previousMusic();
}

// void MusicController::handleTrackSelection(int trackNumber) {
//     if (trackNumber > 0 && static_cast<size_t>(trackNumber) <= model.getMusicFiles().size()) {
//         model.stopMusic();
//         model.setCurrentTrack(trackNumber - 1);
//         model.loadMusic(model.getMusicFiles()[model.getCurrentTrack()]);
//         model.playMusic();
//     } else {
//         std::cout << "Invalid track number." << std::endl;
//     }
// }

// void MusicController::handleUserInput() {
//     std::string input;
//     std::cout << "Enter command (p: play/pause, n: next, b: previous, s: stop, m: display menu, q: quit): ";
//     std::cin >> input;

//     if (input == "p") {
//         handlePlayPause();
//     } else if (input == "n") {
//         handleNextTrack();
//     } else if (input == "b") {
//         handlePreviousTrack();
//     } else if (input == "s") {
//         model.stopMusic();
//     } else if (input == "m") {
//         displayMenumusic();  // Thêm lựa chọn hiển thị menu nhạc
//     } else if (input == "q") {
//         // Quit sẽ được xử lý trong vòng lặp chính
//     } else {
//         try {
//             int trackNumber = std::stoi(input);
//             handleTrackSelection(trackNumber);
//         } catch (const std::invalid_argument&) {
//             std::cout << "Unknown command." << std::endl;
//         }
//     }
// }

void MusicController::displayMenumusic() {
    const std::vector<std::string>& tracks = model.getMusicFiles();
    std::cout << "Music Menu:" << std::endl;
    for (size_t i = 0; i < tracks.size(); ++i) {
        std::cout << i + 1 << ". " << tracks[i] << std::endl;
    }
    std::cout << "Enter track number to play or any other command: ";
}


