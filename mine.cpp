#include "mine.h"

Mine::Mine(int f){
    timeFactor = f;
    resources = 5;    
    queue = 0;
    mining = -1;
}
Mine::Mine(){}
Mine::~Mine(){}