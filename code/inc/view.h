#ifndef VIEW_H
#define VIEW_H

#include "model.h"
#include <SDL2/SDL.h>

#define renderSize 50
#define personSize 25 //half of renderSize

class view {
public:
    view(model& aModel);
    ~view();
    void render();

private:
    model& mModel;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool initSDL();
    void cleanupSDL();
};

#endif // VIEW_H