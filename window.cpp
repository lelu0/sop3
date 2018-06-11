#include "window.h"
#include <ncurses.h>
#include <unistd.h>

Window::Window()
{
    initWindow();
}
Window::~Window()
{
    endwin();
}

void Window::initWindow()
{
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
}

void Window::drawMine(int free, int id, int queue)
{
    mvprintw(0, 0, "Mine");
    //draw border
    for (int i = 0; i <= 8; i++)
    {
        mvprintw(1, i, "_");
        mvprintw(6, i, "_");
    }
    for (int i = 1; i <= 6; i++)
    {
        mvprintw(i, 8, "|");
    }
    mvprintw(3, 0, "Free:%d", free);
    mvprintw(4, 0, "ID:%d", id);
    mvprintw(5, 0, "Queue:%d", queue);
}

void Window::drawPeoples(std::vector<Redneck> rednecks)
{
    for (int i = 0; i < rednecks.size(); i++)
    {
        if (rednecks[i].health > 0){
            if(rednecks[i].isCarring)
                mvprintw(rednecks[i].position[0], rednecks[i].position[1], "o");
            else
                mvprintw(rednecks[i].position[0], rednecks[i].position[1], "x");
        }
            
    }
    mvprintw(0, 15, "vecsize: %d", rednecks.size());
}

void Window::drawFactory(int store, int materials)
{
    mvprintw(0, 51, "Factory");
    //draw border
    for (int i = 50; i <= 58; i++)
    {
        mvprintw(1, i, "_");
        mvprintw(6, i, "_");
    }
    for (int i = 1; i <= 6; i++)
    {
        mvprintw(i, 50, "|");
    }
    mvprintw(3, 51, "Free:%d", store);
    mvprintw(4, 51, "Materials:%d", materials);
}

void Window::updateWindow(int store, int res, std::vector<Redneck> rednecks, int materials)
{
    clear();
    drawMine(res, 0, 0); 
    drawFactory(store, materials);
    drawPeoples(rednecks);
    refresh();
}
