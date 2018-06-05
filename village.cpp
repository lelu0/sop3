#include "village.h"
using namespace std::chrono_literals;

Village::Village(){
    factory = Factory(2000);
    mine = Mine(3000);
    rednecksCounter = 0;
    for(int i = 0; i < 10; i++){
         rednecks.push_back(Redneck(2000,rednecksCounter++));         
    }
   
}
void Village::factoryThread(){
    while(true){
        std::unique_lock<std::mutex> l(f_mutex);
        if(factory.materials == 0)
            factoryMaterialsNotEmpty.wait_for(l,22000ms,[this]{return factory.materials != 0;});
        factory.materials--;
        factory.stock++;
        l.unlock();
        factoryStockNotEmpty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(factory.timeFactor));
    }
}

int Village::getFromFactory(){
    std::unique_lock<std::mutex> l(f_mutex);
    if(factory.stock == 0)
        factoryStockNotEmpty.wait_for(l,22000ms,[this]{return factory.stock != 0;});
    factory.stock--;
    l.unlock();
    return 1;
}

void Village::mineThread(){
    while(true){
        std::unique_lock<std::mutex> l(m_mutex);
        mine.resources++;
        l.unlock();
        mineResourcesNotEmpty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(mine.timeFactor));
    }
}