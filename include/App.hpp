#ifndef APP_HPP
#define APP_HPP

#include "Enums.hpp"
#include <SFML/Graphics.hpp>

class App
{
    friend class Controller;
    friend class MenuController;
    public:
        App();
        void run();
    private:
        void processMenu();
        void processLevel();
        sf::RenderWindow window;
        AppState appState;
        int chosenLevel;
};

#endif
