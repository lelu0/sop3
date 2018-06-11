#include "config.h"

AppConfig::AppConfig()
{
    ifstream in("config.cfg");
    if (!in)
    {
        cout << "Cannot open input file.\n";
    }
    std::string str;
    bool linecheck = false;
    int linecounter = 0;
    while (std::getline(in, str))
    {
        if (linecheck)
        {
            switch (linecounter)
            {
            case 0:
                mineDelay = stoi(str);
                break;
            case 1:
                factoryDelay = stoi(str);
                break;
            case 2:
                miningTime = stoi(str);
                break;
            case 3:
                spotMin = stoi(str);
                break;
            case 4:
                spotMax = stoi(str);
                break;
            case 5:
                maxPopulation = stoi(str);
                break;
            case 6:
                foodIncMin = stoi(str);
                break;
            case 7:
                foodIncMax = stoi(str);
                break;
            case 8:
                redneckStepTime = stoi(str);
                break;
            case 9:
                redneckStartHealth = stoi(str);
                break;
            case 10:
                miningCost = stoi(str);
                break;
            }
            linecounter++;
        }
        linecheck = !linecheck;
    }
    in.close();
}
AppConfig::~AppConfig() {}