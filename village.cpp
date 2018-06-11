#include "village.h"
using namespace std::chrono_literals;

Village::Village()
{
    factory = Factory(config->factoryDelay);
    mine = Mine(config->mineDelay);
    rednecksCounter = 0;
}
void Village::factoryThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> l(f_mutex);
        if (factory.materials <= 0)
            factoryMaterialsNotEmpty.wait(l);
        factory.materials--;
        factory.stock++;
        l.unlock();
        factoryStockNotEmpty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(factory.timeFactor));
    }
}

int Village::getFromFactory()
{
    std::unique_lock<std::mutex> l(f_mutex);
    if (factory.stock <= 0)
        factoryStockNotEmpty.wait(l);
    factory.stock--;
    l.unlock();
    return 1;
}

void Village::putToFactory()
{
    std::unique_lock<std::mutex> l(f_mutex);
    factory.materials++;
    factoryMaterialsNotEmpty.notify_one();
    l.unlock();
}

void Village::mineThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> l(m_mutex);
        mine.resources++;
        l.unlock();
        mineResourcesNotEmpty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(mine.timeFactor));
    }
}

int Village::getFromMine(int id)
{
    std::unique_lock<std::mutex> l(m_mutex);   
    mine.queue++;
    if (mine.mining != -1)
        miningCond.wait(l);
    mine.queue--;

    if (mine.resources <= 0)
    {
        mineResourcesNotEmpty.wait(l);
    }
    mine.mining = id;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    mine.resources--;
    mine.mining = -1;
    l.unlock();
    miningCond.notify_one();
    return 1;
}

void Village::spotterThread()
{
    while (rednecksCounter < 20)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 1000));
        rednecks.push_back(Redneck(2000, rednecksCounter));
        rednecksThreads.push_back(std::thread(&Village::redneckThread, this, rednecksCounter++));
    }
}

void Village::redneckThread(int id)
{
    std::ofstream myfile;
    while (true)
    {
        if (rednecks[id].health <= 0)
            continue;
        w_mutex.lock();
        rednecks[id].move();
        w_mutex.unlock();
        rednecks[id].health--;
        if (rednecks[id].isCarring && rednecks[id].checkFactory())
        {
            putToFactory();
            rednecks[id].isCarring = false;
        }
        if (rednecks[id].checkFactory())
        {
            rednecks[id].health += (rand() % 100 + 50) * getFromFactory();
        }
        if (rednecks[id].checkMine())
        {
            if (getFromMine(id) == 1)
                rednecks[id].isCarring = true; 
        }
        /*if (rednecks[id].id == 1)
        {            
            myfile.open("rednect.txt",std::ios::out | std::ios::app);
            myfile << "position: ";
            myfile << rednecks[id].position[1];
            myfile << "id: ";
            myfile << rednecks[id].id;
            myfile << "\n";
            myfile.close();
        }*/

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}