#include "View.h"

View::View(int height, int width, World &world) {
    this->world = &world;
    viewWidth = width;
    // resize vectors
    loadedWorld.resize(width);
    onScreen.resize(width);

    // setup console for operating system
    setupConsole();

    posX = width / 2;
    // put view on center height
    posY = world.getSegment(posX, 0, 0).height;

    // fill vectors with world data
    for (int i = 0; i < width; ++i) {
        loadedWorld[i] = world.getSegment(i, posY - 10, posY + 10);
        onScreen[i].data.resize(loadedWorld[i].data.size());

        // fill with -1 because nothing has been drawn
        std::fill(onScreen[i].data.begin(), onScreen[i].data.end(), -1);
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
    posY = world->getSegment(posX, 0, 0).height;

    // create new view
    for (int i = 0; i <= loadedWorld.size() - 1; ++i) {
        loadedWorld[i] = world->getSegment((posX - viewWidth / 2) + i, posY - 10, posY + 10);
    }
}

void View::draw() {
    std::string needToDraw;
    for (short y = 0; y < short(loadedWorld[0].data.size()) - 1; ++y) {
        for (short x = 0; x <= short(loadedWorld.size()) - 1; ++x) {

            // Create draw buffer.
            if(loadedWorld[x].data[y] == 0 && onScreen[x].data[y] != loadedWorld[x].data[y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[42m ";
            } else if(loadedWorld[x].data[y] == 1 && onScreen[x].data[y] != loadedWorld[x].data[y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[41m ";
            } else if(loadedWorld[x].data[y] == -1 && onScreen[x].data[y] != loadedWorld[x].data[y]) {
                needToDraw += "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H\033[43m ";
            }

            // Update what is drawn.
            if(onScreen[x].data[y] != loadedWorld[x].data[y]) {
                onScreen[x].data[y] = loadedWorld[x].data[y];
            }
        }
    }
    // Print Player
    needToDraw += "\033[" + std::to_string(10) + ";" + std::to_string(int(loadedWorld.size()) / 2) + "H\033[44m ";

    // Print coordinates of Player
    needToDraw += "\033[25;25H\033[0mCoords X Y: " + std::to_string(posX) + " : " + std::to_string(posY);

    // Draw buffer.
    printf("%s", needToDraw.c_str());
}
