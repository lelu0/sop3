#ifndef VILLAGE_H
#define VILLAGE_H
#include "factory.h"
#include "mine.h"
#include "redneck.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
class Village{
    public:
    Village();
    ~Village();
    //Conditional variables
    std::condition_variable factoryStockNotEmpty;
    std::condition_variable factoryMaterialsNotEmpty;
    std::condition_variable mineResourcesNotEmpty;
    std::mutex f_mutex;
    std::mutex m_mutex;
    std::mutex w_mutex;
    //logic
    Factory factory;
    void factoryThread();
    int getFromFactory();
    Mine mine;
    void mineThread();
    int getFromMine();
    std::vector<Redneck> rednecks;
    std::vector<std::thread> rednecksThreads;
    void redneckThread(Redneck *redneck);
    int rednecksCounter;
    void spotterThread();
};
#endif