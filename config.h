#ifndef APPCONFIG_H
#define APPCONFIG_H
#include <iostream>
#include <fstream>
using namespace std;
class AppConfig{
    public:
    int mineDelay;
    int factoryDelay;
    int miningTime;
    int spotMin;
    int spotMax;
    int maxPopulation;
    int foodIncMin;
    int foodIncMax;
    int redneckStepTime;
    int redneckStartHealth;
    int miningCost;
    AppConfig();
    ~AppConfig();
};
#endif