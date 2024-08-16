#include "mediaView.h"
#include <iostream>

MusicView::MusicView(MusicModel& model)
    : window(nullptr), renderer(nullptr), iconManager(nullptr), model(model), font(nullptr) {}

MusicView::~MusicView() {
    // cleanup();
    uninit();
}

bool MusicView::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Music Player",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    iconManager = new IconManager(renderer);
    iconManager->loadIcon("prev", "icons/prev.png");
    iconManager->loadIcon("play", "icons/play.png");
    iconManager->loadIcon("pause", "icons/pause.png");
    iconManager->loadIcon("next", "icons/next.png");
    iconManager->loadIcon("volume_up", "icons/volume-up.png");
    iconManager->loadIcon("volume_down", "icons/volume-down.png");
    iconManager->loadIcon("line", "icons/line.png");
    iconManager->loadIcon("mute", "icons/mute.png");
    iconManager->loadIcon("bg1", "icons/bg1.png");

    if (!loadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24)) {
        std::cout << "Failed to load font." << std::endl;
        return false;
    }

    render(); // Render để hiển thị các icon và background
    SDL_RenderPresent(renderer);

    return true;
}

bool MusicView::loadFont(const std::string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    return font != nullptr;
}

void MusicView::renderText(const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 255, 255, 255}; // Màu trắng

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void MusicView::render() {
    SDL_SetRenderDrawColor(renderer, 54, 54, 82, 255);
    SDL_RenderClear(renderer);

    iconManager->renderIcon("bg1", 220, 50, 360, 360);
    iconManager->renderIcon("line", 0, 400, 800, 100);
    iconManager->renderIcon("background", 220, 50, 360, 360);
    iconManager->renderIcon("prev", 220, 480, 110, 110);    // Icon "prev"
    iconManager->renderIcon(model.isPlaying() ? "pause" : "play", 340, 480, 110, 110);   // Icon "play"
    iconManager->renderIcon("next", 460, 480, 110, 110);   // Icon "next"
    iconManager->renderIcon("volume_up", 580, 520, 40, 40);
    iconManager->renderIcon("volume_down", 630, 520, 40, 40);
    iconManager->renderIcon("mute", 680, 520, 40, 40);


    // Render the current track name
    renderText(model.getCurrentTrackName(), 10, 10);

    SDL_RenderPresent(renderer);
}

void MusicView::uninit() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (iconManager) {
        delete iconManager;
        iconManager = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

SDL_Renderer* MusicView::getRenderer() const {
    return renderer;
}
