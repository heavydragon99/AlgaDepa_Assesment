#pragma once

#include <SDL.h>
#include <memory>

#define renderSize 10
#define personSize renderSize * 0.5
#define scalePercent 0.8

struct Color {
    int r, g, b;
};

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

    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;

    float mScaleFactor;

    int mRows;
    int mCols;
};
