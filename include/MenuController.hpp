#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"
#include "MenuView.hpp"

class MenuController
{
    public:
        MenuController() = delete;
        MenuController(sf::RenderWindow& window, MenuModel& menuModel, MenuView& menuView);
        void handleEvent();
        bool getLevelRequested() const;
        int getWhichLevelRequested() const;
        bool getQuitRequested() const;
    private:
        static int whichLevel(MenuItem menuItem);
    private:
        sf::RenderWindow& window;
        MenuModel& menuModel;
        MenuView& menuView;
        bool levelRequested;
        int whichLevelRequested;
        bool quitRequested;
};

#endif
