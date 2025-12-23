#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"

class MenuView
{
    public:
        MenuView() = delete;
        MenuView(sf::RenderWindow& window, MenuModel& menuModel);
        void draw();
        void update();
    private:
        void reset();
        sf::Font font;
        sf::Text level1;
        sf::Text level2;
        sf::Text level3;
        sf::RenderWindow& window;
        MenuModel& menuModel;
};

#endif
