#include "view.h"

#include <chrono>
#include <iostream>
#include <thread>

view::view(model& aModel)
    : mModel(aModel), mWindow(nullptr, SDL_DestroyWindow), mRenderer(nullptr, SDL_DestroyRenderer), mScaleFactor(1.0f) {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
    }
    initializeWindow();
}

view::~view() { SDL_Quit(); }

bool view::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void view::initializeWindow() {
    // Get screen dimensions
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    // Calculate maximum window size (70% of the screen)
    int maxWindowWidth = static_cast<int>(screenWidth * 0.7);
    int maxWindowHeight = static_cast<int>(screenHeight * 0.7);

    // Get level data
    const levelData& levelData = mModel.getLevelData();
    int cols = levelData.getCols();
    int rows = levelData.getRows();

    // Calculate the window size to maintain the aspect ratio and ensure tiles are squares
    int tileSize = std::min(maxWindowWidth / cols, maxWindowHeight / rows);
    int windowWidth = tileSize * cols;
    int windowHeight = tileSize * rows;

    // Create the window with the calculated size
    mWindow.reset(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));
    if (!mWindow) {
        throw std::runtime_error("Failed to create window");
    }

    // Create the renderer
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!mRenderer) {
        throw std::runtime_error("Failed to create renderer");
    }

    // Set the initial scale factor
    mScaleFactor = static_cast<float>(tileSize) / renderSize;
}

void view::render() {
    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
    SDL_RenderClear(mRenderer.get());

    // Fetch level data from the model
    const levelData& levelData = mModel.getLevelData();

    // Get window size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(mWindow.get(), &windowWidth, &windowHeight);

    // Calculate tile width and height
    int tileWidth = windowWidth / levelData.getCols();
    int tileHeight = windowHeight / levelData.getRows();

    // Render grid
    for (int i = 0; i < levelData.getTotalTiles(); i++) {
        SDL_Rect fillRect = {levelData.getX(i) * tileWidth, levelData.getY(i) * tileHeight, tileWidth, tileHeight};
        int red, green, blue;
        levelData.getGridColor(i, red, green, blue);
        SDL_SetRenderDrawColor(mRenderer.get(), red, green, blue, 0xFF);
        SDL_RenderFillRect(mRenderer.get(), &fillRect);

        // Draw black outline
        SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
        SDL_RenderDrawRect(mRenderer.get(), &fillRect);
    }

    // Render people
    for (int i = 0; i < levelData.getPersonCount(); i++) {
        float personX = levelData.getPersonX(i);
        float personY = levelData.getPersonY(i);

        int tileX = static_cast<int>(personX);
        int tileY = static_cast<int>(personY);

        float offsetX = personX - tileX;
        float offsetY = personY - tileY;

        SDL_Rect fillRect = {static_cast<int>((tileX + offsetX) * tileWidth),
                             static_cast<int>((tileY + offsetY) * tileHeight), tileWidth / 2, tileHeight / 2};
        SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
        SDL_RenderFillRect(mRenderer.get(), &fillRect);
    }

    SDL_RenderPresent(mRenderer.get());
}

void view::handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        } else if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                int width, height;
                SDL_GetWindowSize(mWindow.get(), &width, &height);
                mScaleFactor = std::min(static_cast<float>(width) / (mModel.getLevelData().getCols() * renderSize),
                                        static_cast<float>(height) / (mModel.getLevelData().getRows() * renderSize));
            }
        }
    }
}
