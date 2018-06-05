#include "redneck.h"

Redneck::Redneck(int f, int id){
    this->id = id;
    timeFactor = f;
    health = 100;
    isCarring = false;
    direction = false;   
    position[1] = rand() % screenBorder[1] + 10;
    position[0] = rand() % screenBorder[0] + 1;
}
Redneck::Redneck(){}
Redneck::~Redneck(){}
void Redneck::move(){
    if(direction)
        position[1]++;
    else
        position[1]--;

    if(position[1] < 9 || position[1] > 49)
        direction = !direction;
}

bool Redneck::checkFactory(){
    return position[1] > 49;
}


bool Redneck::checkMine(){
    return position[1] < 9;
}