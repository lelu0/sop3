#ifndef VILLAGE_H
#define VILLAGE_H
#include "factory.h"
#include "mine.h"
#include "config.h"
#include "redneck.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>

extern std::vector<Redneck> rednecks;
extern AppConfig *config;
class Village{
    public:
    Village();
    ~Village();
    //Conditional variables
    std::condition_variable factoryStockNotEmpty;
    std::condition_variable factoryMaterialsNotEmpty;
    std::condition_variable mineResourcesNotEmpty;
    std::condition_variable miningCond;
    std::mutex f_mutex;
    std::mutex m_mutex;
    std::mutex w_mutex;
    //logic
    Factory factory;
    void factoryThread();
    int getFromFactory();
    void putToFactory();
    Mine mine;
    void mineThread();
    int getFromMine(int id);
    std::vector<std::thread> rednecksThreads;
    void redneckThread(int id);
    int rednecksCounter;
    void spotterThread();
};
#endif