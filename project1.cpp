#include "window.h"
#include "config.h"
#include "village.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <chrono>
std::vector<Redneck> rednecks;
Window *window;
Village *village;
AppConfig *config;
auto start = std::chrono::high_resolution_clock::now();
;

bool running = true;

void exitListener()
{
    while (running)
    {
        char c = getchar();
        if (c == 'x')
            running = false;
    }
}

void updateWindowFct()
{
    while (running)
    {
        usleep(5000);
        auto now = std::chrono::high_resolution_clock::now();
        village->w_mutex.lock();
        window->updateWindow(village->factory.stock, village->mine.resources, rednecks, village->factory.materials, village->mine.queue, village->mine.mining, std::chrono::duration_cast<std::chrono::seconds>(now - start).count());
        village->w_mutex.unlock();
    }
    delete window;
}

int main(int argc, char *argv[])
{

    village = new Village();
    srand(time(NULL));
    window = new Window();
    //config init
    //create control threads
    std::thread windowThread(updateWindowFct);
    std::thread exitThread(exitListener);
    std::thread factoryThread(&Village::factoryThread, village);
    std::thread mineThread(&Village::mineThread, village);
    std::thread spotThread(&Village::spotterThread, village);
    windowThread.join();
    exitThread.join();
    factoryThread.join();
    mineThread.join();
    spotThread.join();

    return 0;
}