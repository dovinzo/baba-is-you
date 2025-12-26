#ifndef APP_HPP
#define APP_HPP

#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "Observer.hpp"
#include "Notification.hpp"
#include <SFML/Graphics.hpp>

class App: public Observer
{
    public:
        App();
        ~App();
        void run();
        void update(const Notification& notification) override;
    private:
        void updateFromVictory();
        void updateFromQuit();
        void changeState(AppState nextAppState);
        void initMenu();
        void processMenu();
        void initLevel();
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
