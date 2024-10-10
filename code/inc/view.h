#ifndef VIEW_H
#define VIEW_H

#include "model.h"
#include <SDL2/SDL.h>
#include <memory>

#define renderSize 10
#define personSize renderSize * 0.5
#define scalePercent 0.8

class View
{
public:
    View(Model &aModel);
    ~View();
    void render();
    void handleEvents(bool &quit);
    void setGridColor(std::vector<GridColor> aGridColor);

private:
    bool initSDL();
    void initializeWindow();
    void renderTile(int tileWidth, int tileHeight);
    void renderPeople(int tileWidth, int tileHeight);
    void getTileColor(char aColor, int &aRed, int &aGreen, int &aBlue);

private:
    Model &mModel;
    std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> mWindow;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> mRenderer;
    float mScaleFactor;
    std::vector<GridColor> mGridColor;
};

#endif // VIEW_H