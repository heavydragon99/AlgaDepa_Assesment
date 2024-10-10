#ifndef VIEW_H
#define VIEW_H

#include <SDL2/SDL.h>
#include <memory>

#include "Renderer.h"
#include "model.h"

class view {
public:
    view(model& aModel);
    ~view();
    void render();
    void handleEvents(bool& quit);
    void setGridColor(std::vector<GridColor> aGridColor);

private:
    void renderTile(int tileWidth, int tileHeight);
    void renderPeople(int tileWidth, int tileHeight);
    void getTileColor(char aColor, int& aRed, int& aGreen, int& aBlue);

private:
    model& mModel;
    std::vector<GridColor> mGridColor;

    Renderer mRenderer;
};

#endif // VIEW_H
