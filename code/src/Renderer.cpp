#include "Renderer.h"

#include <iostream>

/**
 * @brief Constructor for Renderer.
 * @param aRows Number of rows in the grid.
 * @param aCols Number of columns in the grid.
 */
Renderer::Renderer(int aRows, int aCols)
    : mWindow(nullptr, SDL_DestroyWindow), mRenderer(nullptr, SDL_DestroyRenderer), mScaleFactor(1.0f) {

    this->mRows = aRows;
    this->mCols = aCols;

    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
    }
    initializeWindow();
}

/**
 * @brief Destructor for Renderer.
 */
Renderer::~Renderer() { SDL_Quit(); }

/**
 * @brief Presents the rendered content on the screen.
 */
void Renderer::show() { SDL_RenderPresent(mRenderer.get()); }

/**
 * @brief Clears the renderer with a black color.
 */
void Renderer::clear() {
    SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 255); // RGB values for black and full opacity
    SDL_RenderClear(mRenderer.get());
}

/**
 * @brief Gets the width of the window.
 * @return The width of the window.
 */
int Renderer::getWindowWidth() {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(mWindow.get(), &windowWidth, &windowHeight);

    return windowWidth;
}

/**
 * @brief Gets the height of the window.
 * @return The height of the window.
 */
int Renderer::getWindowHeight() {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(mWindow.get(), &windowWidth, &windowHeight);

    return windowHeight;
}

/**
 * @brief Initializes SDL.
 * @return True if SDL was initialized successfully, false otherwise.
 */
bool Renderer::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Initializes the SDL window and renderer.
 */
void Renderer::initializeWindow() {
    // Get screen dimensions
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    // Calculate maximum window size (70% of the screen)
    int maxWindowWidth = static_cast<int>(screenWidth * SCALE_PERCENT);
    int maxWindowHeight = static_cast<int>(screenHeight * SCALE_PERCENT);

    // Calculate the window size to maintain the aspect ratio and ensure tiles are squares
    int tileSize = std::min(maxWindowWidth / mCols, maxWindowHeight / mRows);
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
    mScaleFactor = static_cast<float>(tileSize) / RENDER_SIZE;
}

/**
 * @brief Draws a filled square on the renderer.
 * @param x The x-coordinate of the square.
 * @param y The y-coordinate of the square.
 * @param width The width of the square.
 * @param height The height of the square.
 * @param color The color of the square.
 */
void Renderer::drawSquare(int x, int y, int width, int height, Color color) {
    SDL_Rect fillRect = {x, y, width, height}; // Ensure square tiles
    SDL_SetRenderDrawColor(mRenderer.get(), color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect(mRenderer.get(), &fillRect);
}

/**
 * @brief Draws the outline of a square on the renderer.
 * @param x The x-coordinate of the square.
 * @param y The y-coordinate of the square.
 * @param width The width of the square.
 * @param height The height of the square.
 * @param color The color of the square.
 */
void Renderer::drawSquareRect(int x, int y, int width, int height, Color color) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(mRenderer.get(), color.r, color.g, color.b, 0xFF);
    SDL_RenderDrawRect(mRenderer.get(), &rect);
}