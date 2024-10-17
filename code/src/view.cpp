#include "view.h"

#include "artist.h"

#include <chrono>
#include <iostream>
#include <thread>

View::View(Model& aModel)
    : mModel(aModel), mRenderer(aModel.getLevelData().getRows(), aModel.getLevelData().getCols()), mTileSize(0) {}

View::~View() {}

void View::renderTile(int tileWidth, int tileHeight) {
    int red, green, blue;
    int x, y;
    LevelData& levelData = mModel.getLevelData();
    for (int i = 0; i < levelData.getGrid().size(); i++) {
        getTileColor(levelData.getGrid().at(i).getTile().getColor(), red, green, blue);
        x = i % levelData.getCols();
        y = i / levelData.getCols();
        SDL_Rect fillRect = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
        mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, Color(red, green, blue));

        if (levelData.getGrid().at(i).isVisited()) {
            std::cout << "PATH gevonden" << std::endl;
            SDL_Rect smallSquare = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
            mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, Color(134, 0, 0));
        }
        if (levelData.getGrid().at(i).isPath()) {
            std::cout << "PATH gevonden" << std::endl;
            SDL_Rect smallSquare = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
            mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, Color(0, 0, 0));
        }
    }
}

void View::renderPeople(int tileWidth, int tileHeight) {
    LevelData& levelData = mModel.getLevelData();

    for (Artist& personItr : levelData.getPeople()) {
        Artist::Location personLocation = personItr.getLocation();

        int tileX = std::floor(personLocation.mX);
        int tileY = std::floor(personLocation.mY);

        float offsetX = personLocation.mX - tileX;
        float offsetY = personLocation.mY - tileY;

        SDL_Rect fillRect = {static_cast<int>((tileX + offsetX) * tileWidth),
                             static_cast<int>((tileY + offsetY) * tileHeight), tileWidth / 2, tileWidth / 2}; // Ensure
                                                                                                              // square
        Color color = {0, 0, 0};

        if (personItr.getRed()) {
            color = Color(255, 0, 0);
        }

        mRenderer.drawSquare(fillRect.x, fillRect.y, fillRect.w, fillRect.h, color);
    }
}

void View::render() {
    mRenderer.clear();

    // Get level data
    const LevelData& levelData = mModel.getLevelData();

    // Get window size
    int windowWidth = mRenderer.getWindowWidth();
    int windowHeight = mRenderer.getWindowHeight();

    // Calculate tile width and height
    mTileSize = std::min(windowWidth / levelData.getCols(), windowHeight / levelData.getRows());

    // Render grid
    renderTile(mTileSize, mTileSize);

    // Render people
    renderPeople(mTileSize, mTileSize);

    mRenderer.show();
}

void View::handleEvents(bool& quit) {
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

void View::setGridColor(std::vector<GridColor> aGridColor) {
    // Fill mGridColor with all the different colors
    for (const GridColor& color : aGridColor) {
        mGridColor.push_back(color);
    }
}

int View::getTileSize() const { return mTileSize; }

void View::getTileColor(char aColor, int& aRed, int& aGreen, int& aBlue) {
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
