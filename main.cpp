#include <iostream>
#include "World.h"
#include "View.h"

int main() {
    int seed = 452;

    World world(50, seed);
    View view(20, 119, world);

    clock_t time = clock();

    /*std::cout << int(0.1) << std::endl;
    std::cout << int(0.5)  << std::endl;
    std::cout << int(0.99999)  << std::endl;
    std::cout << int(1.5)  << std::endl;*/

    while(true) {
        if(clock() - time > 50) {
            time = clock();
            if(getStateOfKey(0x57)) {
                view.move(1);
            } else if(getStateOfKey(0x53)) {
                view.move(-1);
            } else if(getStateOfKey(0x1B)) {
                break;
            }
            view.draw();
        }
    }

    restoreConsole();

    return 0;
}