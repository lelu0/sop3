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
    //logic
    Factory factory;
    void factoryThread();
    int getFromFactory();
    Mine mine;
    void mineThread();
    int getFromMine();
    std::vector<Redneck> rednecks;
    int rednecksCounter;
};
#endif