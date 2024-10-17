#ifndef VIEW_H
#define VIEW_H

#include <SDL2/SDL.h>
#include <memory>

#include "Renderer.h"
#include "model.h"

class View {
public:
    View(Model& aModel);
    ~View();

    void render();
    void handleEvents(bool& quit);
    void setGridColor(std::vector<GridColor> aGridColor);
    int getTileSize() const;

private:
    void renderTile(int tileWidth, int tileHeight);
    void renderPeople(int tileWidth, int tileHeight);
    void getTileColor(char aColor, int& aRed, int& aGreen, int& aBlue);

private:
    Model& mModel;

    std::vector<GridColor> mGridColor;

    Renderer mRenderer;

    int mTileSize;
};

#endif // VIEW_H
