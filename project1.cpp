#include "window.h"
#include "config.h"
#include "village.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <vector>
Window *window;
Village *village;
AppConfig *config;
bool running = true;

void exitListener()
{
    while (running)
    {
        char c = getchar();
        if(c == 'x')
            running = false;
    }
}


void updateWindowFct()
{
    while (running)
    {
        usleep(5000);
        village->w_mutex.lock();
        window->updateWindow(village->factory.stock, village->mine.resources, village->rednecks);
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
    config = new AppConfig();    
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