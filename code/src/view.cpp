#include "view.h"

#include "artist.h"

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
    int maxWindowWidth = static_cast<int>(screenWidth * scalePercent);
    int maxWindowHeight = static_cast<int>(screenHeight * scalePercent);

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

    // Create the renderer with V-sync enabled
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!mRenderer) {
        throw std::runtime_error("Failed to create renderer");
    }

    // Set the initial scale factor
    mScaleFactor = static_cast<float>(tileSize) / renderSize;
}

void view::renderTile(int tileWidth, int tileHeight) {
    int red, green, blue;
    int x, y;
    const levelData& levelData = mModel.getLevelData();
    for (int i = 0; i < levelData.getGrid().size(); i++) {
        getTileColor(levelData.getGrid().at(i).get()->getTile().getColor(), red, green, blue);
        x = i % levelData.getCols();
        y = i / levelData.getCols();
        SDL_Rect fillRect = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
        SDL_SetRenderDrawColor(mRenderer.get(), red, green, blue, 0xFF);
        SDL_RenderFillRect(mRenderer.get(), &fillRect);
    }
}

void view::renderPeople(int tileWidth, int tileHeight) {
    const levelData& levelData = mModel.getLevelData();
    float personX, personY;

    for(const auto& personPtr : levelData.getPeople() ){
        personX = personPtr->getX();
        personY = personPtr->getY();

        int tileX = std::floor(personX);
        int tileY = std::floor(personY);

        float offsetX = personX - tileX;
        float offsetY = personY - tileY;

        SDL_Rect fillRect = {static_cast<int>((tileX + offsetX) * tileWidth),
                             static_cast<int>((tileY + offsetY) * tileHeight), tileWidth / 2, tileWidth / 2}; // Ensure square tiles
        SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
        SDL_RenderFillRect(mRenderer.get(), &fillRect);
    }
}

void view::render() {
    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
    SDL_RenderClear(mRenderer.get());

    // Get level data
    const levelData& levelData = mModel.getLevelData();

    // Get window size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(mWindow.get(), &windowWidth, &windowHeight);

    // Calculate tile width and height
    int tileSize = std::min(windowWidth / levelData.getCols(), windowHeight / levelData.getRows());

    // Render grid
    renderTile(tileSize, tileSize);

    // Render people
    renderPeople(tileSize, tileSize);

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
        }
    }
}

void view::setGridColor(std::vector<GridColor> aGridColor)
{
        // Fill mGridColor with all the different colors
    for (const GridColor& color : aGridColor) {
        mGridColor.push_back(color);
    }
}

void view::getTileColor(char aColor, int& aRed, int& aGreen, int& aBlue) {
    for (const GridColor& color : mGridColor) {
        if (color.letter == aColor) {
            aRed = color.red;
            aGreen = color.green;
            aBlue = color.blue;
            return;
        }
    }
    //default white
    aRed = 255;
    aGreen = 255;
    aBlue = 255;
}