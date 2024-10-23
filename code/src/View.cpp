#include "View.h"

#include "Artist.h"
#include "Configuration.h"

#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief Constructs a View object.
 * @param aModel Reference to the Model object.
 */
View::View(Model& aModel)
    : mModel(aModel), mRenderer(aModel.getLevelData().getRows(), aModel.getLevelData().getCols()), mTileSize(0) {}

/**
 * @brief Destructor for the View object.
 */
View::~View() {}

/**
 * @brief Renders the tiles on the screen.
 * @param tileWidth Width of each tile.
 * @param tileHeight Height of each tile.
 */
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

        if (levelData.getGrid().at(i).isVisited() && Configuration::getInstance().getConfig("RenderVisited")) {
            SDL_Rect smallSquare = {x * tileWidth, y * tileHeight, tileWidth, tileWidth}; // Ensure square tiles
            mRenderer.drawSquareRect(fillRect.x, fillRect.y, fillRect.w, fillRect.h, Color(134, 0, 0));
        }
        if (levelData.getGrid().at(i).isPath() && Configuration::getInstance().getConfig("RenderPath")) {
            // Calculate new dimensions
            int newTileWidth = static_cast<int>(tileWidth * 0.7);
            int newTileHeight = static_cast<int>(tileHeight * 0.7);

            // Calculate new starting positions to center the smaller square
            int newX = x * tileWidth + (tileWidth - newTileWidth) / 2;
            int newY = y * tileHeight + (tileHeight - newTileHeight) / 2;

            SDL_Rect smallSquare = {newX, newY, newTileWidth, newTileHeight}; // Ensure square tiles
            mRenderer.drawSquare(smallSquare.x, smallSquare.y, smallSquare.w, smallSquare.h, Color(0, 0, 0));
        }
    }
}

/**
 * @brief Renders the people on the screen.
 * @param tileWidth Width of each tile.
 * @param tileHeight Height of each tile.
 */
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

/**
 * @brief Renders the quadtree boundaries on the screen.
 */
void View::renderQuadtree() {
    if (mBoundaries.size() == 0) {
        return;
    }

    // Get window size
    int windowWidth = mRenderer.getWindowWidth();
    int windowHeight = mRenderer.getWindowHeight();

    // Calculate tile width and height
    mTileSize = std::min(windowWidth / mModel.getLevelData().getCols(), windowHeight / mModel.getLevelData().getRows());

    for (Quadtree::Boundary boundary : mBoundaries) {
        mRenderer.drawSquareRect(boundary.x * mTileSize, boundary.y * mTileSize, boundary.width * mTileSize,
                                 boundary.height * mTileSize, Color(0, 255, 17));
    }

    mBoundaries.resize(0);
}

/**
 * @brief Renders the entire view including grid, people, and quadtree.
 */
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

    if (Configuration::getInstance().getConfig("RenderArtists")) {
        renderPeople(mTileSize, mTileSize);
    }

    renderQuadtree();

    mRenderer.show();
}

/**
 * @brief Sets the quadtree boundaries to be rendered.
 * @param aBoundaries Vector of quadtree boundaries.
 */
void View::setQuadtreeBoundaries(std::vector<Quadtree::Boundary> aBoundaries) { mBoundaries = aBoundaries; }

/**
 * @brief Handles SDL events such as quitting and key presses.
 * @param quit Reference to a boolean that indicates whether to quit the application.
 */
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

/**
 * @brief Sets the grid colors.
 * @param aGridColor Vector of GridColor objects.
 */
void View::setGridColor(std::vector<GridColor> aGridColor) {
    // Fill mGridColor with all the different colors
    for (const GridColor& color : aGridColor) {
        mGridColor.push_back(color);
    }
}

/**
 * @brief Gets the tile size.
 * @return The size of the tile.
 */
int View::getTileSize() const { return mTileSize; }

/**
 * @brief Gets the color of a tile based on a character.
 * @param aColor Character representing the color.
 * @param aRed Reference to the red component.
 * @param aGreen Reference to the green component.
 * @param aBlue Reference to the blue component.
 */
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