#ifndef WINDOW_H
#define WINDOW_H
#include<vector>
#include"redneck.h"
class Window{
    public:
    Window();
    ~Window();
    void initWindow();
    void updateWindow(int store, int res, std::vector<Redneck> rednecks);
    void drawMine(int free, int id, int queue);
    void drawPeoples(std::vector<Redneck> rednecks);
    void drawFactory(int store);
};

#endif