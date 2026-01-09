#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"
#include "MenuView.hpp"

class App;

class MenuController
{
    friend class App;

public:
    MenuController() = delete;
    bool getLevelRequested() const;
    int getWhichLevelRequested() const;
    bool getQuitRequested() const;

private:
    MenuController(sf::RenderWindow &window, MenuModel &menuModel, MenuView &menuView);
    void handleEvent();

    static int whichLevel(MenuItem menuItem);
    sf::RenderWindow &window;
    MenuModel &menuModel;
    MenuView &menuView;
    bool levelRequested;
    int whichLevelRequested;
    bool quitRequested;
};

#endif
