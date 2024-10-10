#include "view.h"

#include "artist.h"

#include <chrono>
#include <iostream>
#include <thread>

view::view(model& aModel) : mModel(aModel) {}

view::~view() { SDL_Quit(); }

void view::renderTile(int tileWidth, int tileHeight) {
    int red, green, blue;
    int x, y;
    const levelData& levelData = mModel.getLevelData();
    for (int i = 0; i < levelData.getGrid().size(); i++) {
        getTileColor(levelData.getGrid().at(i).get()->getTile().getColor(), red, green, blue);
        x = i % levelData.getCols();
        y = i / levelData.getCols();
        SDL_Rect fillRect = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
        mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, Color(red, green, blue));
        // SDL_SetRenderDrawColor(mRenderer.get(), red, green, blue, 0xFF);
        // SDL_RenderFillRect(mRenderer.get(), &fillRect);
    }
}

void view::renderPeople(int tileWidth, int tileHeight) {
    const levelData& levelData = mModel.getLevelData();

    for (const auto& personPtr : levelData.getPeople()) {
        artist::Location personLocation = personPtr->getLocation();

        int tileX = std::floor(personLocation.mX);
        int tileY = std::floor(personLocation.mY);

        float offsetX = personLocation.mX - tileX;
        float offsetY = personLocation.mY - tileY;

        SDL_Rect fillRect = {static_cast<int>((tileX + offsetX) * tileWidth),
                             static_cast<int>((tileY + offsetY) * tileHeight), tileWidth / 2, tileWidth / 2}; // Ensure
                                                                                                              // square
        Color color = {0, 0, 0};

        if (personPtr->getRed()) {
            color = Color(255, 0, 0);
        }
        // else {
        //     SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
        // }

        // SDL_RenderFillRect(mRenderer.get(), &fillRect);
        mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, color);
    }
}

void view::render() {
    // SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 0xFF);
    // SDL_RenderClear(mRenderer.get());

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

void view::setGridColor(std::vector<GridColor> aGridColor) {
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
    // default white
    aRed = 255;
    aGreen = 255;
    aBlue = 255;
}
