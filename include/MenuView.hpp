#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"

class App;
class MenuController;

class MenuView
{
    friend class App;
    friend class MenuController;

public:
    MenuView() = delete;

private:
    MenuView(sf::RenderWindow &window, MenuModel &menuModel);
    void draw();
    void update();
    void reset();
    sf::Font font;
    sf::Text level1;
    sf::Text level2;
    sf::Text level3;
    sf::RenderWindow &window;
    MenuModel &menuModel;
};

#endif
