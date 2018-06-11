#include "config.h"

AppConfig::AppConfig(){
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
        if(linecheck){
            std::cout << str << std::endl; 
            switch(linecounter){
                case 0:
                    mineDelay = stoi(str);
                break;
                case 1:
                    factoryDelay = stoi(str);
                break;
            }
            linecounter++;
        }
        linecheck = !linecheck;
               
    }
    in.close();
}
AppConfig::~AppConfig(){}