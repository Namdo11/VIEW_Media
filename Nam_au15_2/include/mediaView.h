#ifndef MEDIA_VIEW_H
#define MEDIA_VIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "iconManager.h"
#include "mediaModel.h"
// #include "mediaController.h"

class MusicView {
public:
    MusicView(MusicModel& model );
    ~MusicView();

    bool init();
    void uninit();
    void render(); // Đảm bảo khai báo hàm này
    bool loadFont(const std::string& fontPath, int fontSize);
    void renderText(const std::string& text, int x, int y);

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    IconManager& getIconManager();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    IconManager* iconManager;
    MusicModel& model;
    TTF_Font* font;
    // MusicController* controll;
};

#endif // MEDIA_VIEW_H