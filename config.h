#ifndef APPCONFIG_H
#define APPCONFIG_H
#include <iostream>
#include <fstream>
using namespace std;
class AppConfig{
    public:
    int mineDelay;
    int factoryDelay;
    AppConfig();
    ~AppConfig();
};
#endif