
#include <iostream>
#include "iconManager.h"
IconManager::IconManager(SDL_Renderer* renderer) : renderer(renderer) {}

IconManager::~IconManager() {
    for (auto& pair : icons) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    icons.clear(); // Xóa hết các mục trong map
}

bool IconManager::loadIcon(const std::string& id, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << path << "! IMG Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    icons[id] = texture;
    return true;
}

void IconManager::renderIcon(const std::string& id, int x, int y, int width, int height) {
    if (icons.find(id) != icons.end()) {
        SDL_Rect destRect = { x, y, width, height }; // Adjust width and height as needed
        SDL_RenderCopy(renderer, icons[id], nullptr, &destRect);
    }
}
