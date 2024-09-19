#include "view.h"
#include <iostream>

view::view(model& aModel) : mModel(aModel), mWindow(nullptr), mRenderer(nullptr) {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
    }
}

view::~view() {
    cleanupSDL();
}

void view::render() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(mRenderer);

    // Fetch level data from the model
    const levelData& levelData = mModel.getLevelData();

    // Render grid
    for(int i = 0; i < levelData.getTotalTiles(); i++) {
        SDL_Rect fillRect = { levelData.getX(i) * renderSize, levelData.getY(i) * renderSize, renderSize, renderSize };
        int red, green, blue;
        levelData.getGridColor(i, red, green, blue);
        SDL_SetRenderDrawColor(mRenderer, red, green, blue, 0xFF);
        SDL_RenderFillRect(mRenderer, &fillRect);
    }

    // Render persons
    for (int i = 0; i < levelData.getPersonCount(); i++) {
        SDL_Rect fillRect = { levelData.getPersonX(i) * personSize, levelData.getPersonY(i) * personSize, personSize, personSize };
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
        SDL_RenderFillRect(mRenderer, &fillRect);
    }

    SDL_RenderPresent(mRenderer);
}

bool view::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("Game View", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void view::cleanupSDL() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}