#ifndef APP_HPP
#define APP_HPP

#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class App
{
    public:
        App();
        void run();
    private:
        void initState();
        void changeState(AppState nextAppState);
        void processMenu();
        void processLevel();
    private:
        sf::RenderWindow* window;
        AppState appState;
        MenuModel* menuModel;
        MenuView* menuView;
        MenuController* menuController;
        Model* levelModel;
        View* levelView;
        Controller* levelController;
};

#endif
