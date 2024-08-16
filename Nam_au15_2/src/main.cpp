#include "mediaModel.h"
#include "mediaView.h"
#include "mediaController.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <SDL2/SDL_image.h>

const std::string defaultPath = "/home/namdo/Desktop/lilux";  // Đường dẫn mặc định

// Biến toàn cục để điều khiển việc dừng luồng
std::atomic<bool> stopFlag(false);

void musicThread(MusicController& controller) {
    while (!stopFlag.load()) {
        // Điều khiển phát nhạc trong khi luồng vẫn hoạt động
        controller.getMouseStatus();
    }
}

int main() {
    // Khởi tạo SDL và SDL_image một lần trước vòng lặp chính
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    // Tạo các đối tượng Model, View, Controller
    MusicModel model;
    MusicView view(model);
    MusicController controller(model, view);

    // Khởi tạo Model và View
    model.init();
    view.init();

    std::thread musicPlayerThread;

    bool quit = false;
    while(!quit) {
        // Hiển thị menu và xử lý các lựa chọn
        int choice;
        std::cout << "Menu:\n";
        std::cout << "1. Run Music Player with Directory\n";
        std::cout << "2. Display Music List\n";
        std::cout << "3. Stop Music Player\n";
        std::cout << "0. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string musicDirectory;
                std::cout << "Enter the music directory path (leave empty for default): ";
                std::cin.ignore(); // Bỏ qua ký tự newline còn lại trong bộ đệm sau khi nhập số
                std::getline(std::cin, musicDirectory);

                if (musicDirectory.empty()) {
                    musicDirectory = defaultPath;
                }

                // Nếu luồng cũ đang chạy, dừng nó lại trước khi khởi động luồng mới
                if (musicPlayerThread.joinable()) {
                    std::cout << "Stopping current music player...\n";
                    stopFlag.store(true);  // Đặt cờ để dừng luồng phát nhạc
                    model.stopMusic();  // Dừng phát nhạc nếu có
                    musicPlayerThread.join();  // Chờ luồng kết thúc
                    stopFlag.store(false);  // Reset flag cho lần chạy tiếp theo nếu có
                }

                model.loadMusicFiles(musicDirectory);  // Load các file nhạc từ thư mục mới

                // Khởi động luồng phát nhạc mới
                musicPlayerThread = std::thread(musicThread, std::ref(controller));
                break;
            }

            case 2:
                if (!stopFlag.load()) {
                // Chỉ hiển thị danh sách nhạc mà không ảnh hưởng đến luồng phát nhạc
                    controller.displayMenumusic();
                    // controller.displayPagedSongs(5);
                } else {
                    std::cout << "Music player is currently stopped. Please start it first.\n";
                }
                break;

            case 3:
                std::cout << "Stopping Music Player...\n";
                stopFlag.store(true);  // Đặt cờ để dừng luồng phát nhạc
                model.stopMusic();  // Dừng phát nhạc nếu có
                if (musicPlayerThread.joinable()) {
                    musicPlayerThread.join();  // Chờ luồng kết thúc
                }
                stopFlag.store(false);  // Reset flag cho lần chạy tiếp theo nếu có
                break;

            case 0:
                std::cout << "Quitting...\n";
                stopFlag.store(true);  // Đặt cờ để dừng luồng phát nhạc

                // Dừng phát nhạc nếu đang phát
                model.stopMusic(); 

                // Chờ luồng phát nhạc kết thúc
                if (musicPlayerThread.joinable()) {
                    musicPlayerThread.join();
                }

                // Giải phóng tài nguyên của view và model
                view.uninit();
                model.uninit();

                quit = true;  // Thoát vòng lặp chính
                break;

            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }

    // Giải phóng SDL_image và SDL một lần sau khi thoát vòng lặp chính
    IMG_Quit();
    SDL_Quit();

    std::cout << "\nProgram has exited successfully.\n";

    return 0;
}
