#include "village.h"
using namespace std::chrono_literals;

Village::Village()
{
    factory = Factory(2000);
    mine = Mine(3000);
    rednecksCounter = 0;
}
void Village::factoryThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> l(f_mutex);
        if (factory.materials == 0)
            factoryMaterialsNotEmpty.wait_for(l, 22000ms, [this] { return factory.materials != 0; });
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
    if (factory.stock == 0)
        factoryStockNotEmpty.wait_for(l, 22000ms, [this] { return factory.stock != 0; });
    factory.stock--;
    l.unlock();
    return 1;
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

void Village::spotterThread()
{
    while (rednecksCounter < 2)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        rednecks.push_back(Redneck(2000, rednecksCounter++));
        rednecksThreads.push_back(std::thread(&Village::redneckThread,this, &rednecks[rednecks.size() - 1]));
        
    }
}

void Village::redneckThread(Redneck *redneck)
{
    std::ofstream myfile;
    while (true)
    {
        w_mutex.lock();
        redneck->move();
        if (redneck->id = 1)
        {            
            myfile.open("rednect.txt",std::ios::out | std::ios::app);
            myfile << "position: ";
            myfile << redneck->position[1];
            myfile << "id: ";
            myfile << redneck->id;
            myfile << "\n";
            myfile.close();
        }
        w_mutex.unlock();
        

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}