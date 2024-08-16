#pragma once

#ifndef ICON_MANAGER_H
#define ICON_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class IconManager {
public:
    IconManager(SDL_Renderer* renderer);
    ~IconManager();

    bool loadIcon(const std::string& id, const std::string& path);
    void renderIcon(const std::string& id, int x, int y, int width, int height);

private:
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> icons;
};

#endif //ICON_MANAGER_H