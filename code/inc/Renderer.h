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
    Renderer();
    ~Renderer();

    void drawSquare(int x, int y, int width, int height, Color color);

private:
    bool initSDL();
    void initializeWindow();

    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;

    float mScaleFactor;
};
