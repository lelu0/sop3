#ifndef MINE_H
#define MINE_H
class Mine{
    public:
    int resources;
    int timeFactor;   
    int queue;
    int mining; 
    Mine(int f);
    Mine();
    ~Mine();
};
#endif