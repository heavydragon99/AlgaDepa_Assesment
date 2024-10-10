#include "Renderer.h"

#include <iostream>

Renderer::Renderer()
    : mWindow(nullptr, SDL_DestroyWindow), mRenderer(nullptr, SDL_DestroyRenderer), mScaleFactor(1.0f) {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
    }
    initializeWindow();
}

Renderer::~Renderer() { SDL_Quit(); }

bool Renderer::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::initializeWindow() {
    // Get screen dimensions
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    // Calculate maximum window size (70% of the screen)
    int maxWindowWidth = static_cast<int>(screenWidth * scalePercent);
    int maxWindowHeight = static_cast<int>(screenHeight * scalePercent);

    // Get level data
    // const levelData& levelData = mModel.getLevelData();
    // int cols = levelData.getCols();
    // int rows = levelData.getRows();
    //
    // // Calculate the window size to maintain the aspect ratio and ensure tiles are squares
    // int tileSize = std::min(maxWindowWidth / cols, maxWindowHeight / rows);
    int windowWidth = 600;
    int windowHeight = 600;

    // Create the window with the calculated size
    mWindow.reset(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));
    if (!mWindow) {
        throw std::runtime_error("Failed to create window");
    }

    // Create the renderer with V-sync enabled
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!mRenderer) {
        throw std::runtime_error("Failed to create renderer");
    }

    // Set the initial scale factor
    // mScaleFactor = static_cast<float>(tileSize) / renderSize;
}

void Renderer::drawSquare(int x, int y, int width, int height, Color color) {
    SDL_Rect fillRect = {x, y, width, height}; // Ensure square tiles
    SDL_SetRenderDrawColor(mRenderer.get(), color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect(mRenderer.get(), &fillRect);
}
