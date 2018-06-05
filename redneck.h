#ifndef REDNECK_H
#define REDNECK_H
#include <stdlib.h> 
class Redneck{
    public:
    int id;
    int health;
    bool isCarring;
    int timeFactor;    
    int position[2];
    const int screenBorder[2] = {8,40};
    bool direction; //false mean left
    Redneck(int f, int id);
    Redneck();
    ~Redneck();
    void move();
    bool checkFactory();
    bool checkMine();
};
#endif