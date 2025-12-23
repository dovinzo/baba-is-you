#include "App.hpp"
#include "Enums.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>

App::App(): window{nullptr}, appState{}, menuModel{nullptr}, menuView{nullptr}, menuController{nullptr}, levelModel{nullptr}, levelView{nullptr}, levelController{nullptr}
{
}

void App::run()
{
    this->initState();

    while (appState != AppState::QUIT)
    {
        switch (appState)
        {
            case AppState::MENU:
                this->processMenu();
                break;
            case AppState::LEVEL:
                this->processLevel();
                break;
            case AppState::QUIT:
                break;
        }
    }
}

void App::initState()
{
    window = new sf::RenderWindow{sf::VideoMode(800, 800), "Baba Is You", sf::Style::Close};
    window->setFramerateLimit(60);
    menuModel = new MenuModel;
    menuView = new MenuView{*window, *menuModel};
    menuController = new MenuController{*window, *menuModel, *menuView};
    appState = AppState::MENU;
}

void App::changeState(AppState nextAppState)
{
    if (appState == AppState::MENU)
    {
        if (nextAppState == AppState::LEVEL)
        {
            levelModel = new Model{menuController->getWhichLevelRequested()};
            levelView = new View{*levelModel, *window};
            levelController = new Controller{*window, *levelModel, *levelView};
        }
        else if (nextAppState == AppState::QUIT)
        {
            window->close();
            delete window;
        }
        delete menuModel;
        delete menuView;
        delete menuController;
    }
    else if (appState == AppState::LEVEL)
    {
        if (nextAppState == AppState::MENU)
        {
            menuModel = new MenuModel;
            menuView = new MenuView{*window, *menuModel};
            menuController = new MenuController{*window, *menuModel, *menuView};
        }
        else if (nextAppState == AppState::QUIT)
        {
            window->close();
            delete window;
        }
        delete levelModel;
        delete levelView;
        delete levelController;
    }
    appState = nextAppState;
}

void App::processMenu()
{
    while (appState == AppState::MENU)
    {
        menuController->handleEvent();
        window->clear();
        menuView->draw();
        window->display();
        if (menuController->getLevelRequested())
            this->changeState(AppState::LEVEL);
        else if (menuController->getQuitRequested())
            this->changeState(AppState::QUIT);
    }
}

void App::processLevel()
{
    while (appState == AppState::LEVEL)
    {
        levelController->handleEvent();
        window->clear();
        levelView->draw();
        window->display();
        if (levelController->getMenuRequested())
            this->changeState(AppState::MENU);
        else if (levelController->getQuitRequested())
            this->changeState(AppState::QUIT);
    }
}
