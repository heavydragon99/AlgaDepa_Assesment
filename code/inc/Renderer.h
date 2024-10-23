#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <memory>

#define RENDER_SIZE 10
#define PERSON_SIZE RENDER_SIZE * 0.5
#define SCALE_PERCENT 0.8

/**
 * @brief Structure to represent RGB color.
 */
struct Color {
    int r; ///< Red component
    int g; ///< Green component
    int b; ///< Blue component
};

/**
 * @brief Class responsible for rendering graphics using SDL.
 */
class Renderer {
public:

    Renderer(int aRows, int aCols);
    ~Renderer();

    void show();
    void clear();
    void drawSquare(int x, int y, int width, int height, Color color);
    void drawSquareRect(int x, int y, int width, int height, Color color);
    int getWindowWidth();
    int getWindowHeight();

private:
    bool initSDL();
    void initializeWindow();

    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow; ///< SDL window
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer; ///< SDL renderer

    float mScaleFactor; ///< Scale factor for rendering

    int mRows; ///< Number of rows in the grid
    int mCols; ///< Number of columns in the grid
};

#endif // RENDERER_H