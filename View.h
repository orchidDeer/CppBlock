#ifndef CMINECRAFT_VIEW_H
#define CMINECRAFT_VIEW_H

#include <vector>
#include <iostream>
#include <string>
#include <future>
#include "World.h"
#include "compatibility.h"

/**
 * Handles the View and draws it.
 */
class View {
public:

    /**
     * Creates visible matrix of the world.
     * @param height View distance height.
     * @param width View distance length.
     * @param world The world.
     */
    View(int height, int width, World world);
    ~View();

    /**
     * Moves view x units.
     * @param x Units to move the view
     */
    void move(int x);

    /**
     * Draws the current view.
     */
    void draw();
private:
    /// World how it should be drawn.
    std::vector<std::vector<short int>> loadedWorld;
    /// World how it currently is drawn.
    std::vector<std::vector<short int>> onScreen;

    int posX = 0, posY = 0;
    World world;
};

#endif //CMINECRAFT_VIEW_H
