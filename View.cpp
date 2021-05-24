#include "View.h"

View::View(int height, int width, World world) : world(world) {
    // resize vectors
    loadedWorld.resize(width);
    onScreen.resize(width);

    for (int i = 0; i < loadedWorld.size(); ++i) {
        loadedWorld[i].resize(height);
        onScreen[i].resize(height);
    }

    // setup console for operating system
    setupConsole();

    // put view on center height
    posY = world.getTerrainHeight(width / 2);

    // fill vectors with world data
    for (int i = 0; i < loadedWorld.size(); ++i) {
        loadedWorld[i] = world.createNext(i, posY + 10, posY - 10);
        // fill with -1 because nothing has been drawn
        std::fill(onScreen[i].begin(), onScreen[i].end(), -1);
    }
}
View::~View() {
    loadedWorld.clear();
    onScreen.clear();
}

void View::move(int x) {
    // save new x position
    posX += x;
    // save new y position
    posY = world.getTerrainHeight(int(loadedWorld.size()) / 2 + posX);

    // create new view
    for (int i = 0; i <= loadedWorld.size() - 1; ++i) {
        loadedWorld[i] = world.createNext(posX + i, posY + 10, posY - 10);
    }
}

void View::draw() {
    std::string needToDraw;
    for (short y = 0; y < short(loadedWorld[0].size()) - 1; ++y) {
        for (short x = 0; x <= short(loadedWorld.size()) - 1; ++x) {

            // Create draw buffer.
            if(loadedWorld[x][y] == 0 && onScreen[x][y] != loadedWorld[x][y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[42m ";
            } else if(loadedWorld[x][y] == 1 && onScreen[x][y] != loadedWorld[x][y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[41m ";
            } else if(loadedWorld[x][y] == -1 && onScreen[x][y] != loadedWorld[x][y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[43m ";
            }

            // Update what is drawn.
            if(onScreen[x][y] != loadedWorld[x][y]) {
                onScreen[x][y] = loadedWorld[x][y];
            }
        }
    }
    needToDraw += "\033[" + std::to_string(10) + ";" + std::to_string(int(loadedWorld.size()) / 2) + "H\033[44m ";

    needToDraw += "\033[25;25H\033[0mCoords X Y: " + std::to_string(posX + loadedWorld.size() / 2) + " : " + std::to_string(posY);

    // Draw buffer.
    printf("%s", needToDraw.c_str());
}
