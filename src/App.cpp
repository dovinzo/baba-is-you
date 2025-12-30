#include "App.hpp"
#include "Enums.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include "Observer.hpp"
#include "Notification.hpp"
#include "Victory.hpp"
#include "Quit.hpp"
#include <SFML/Graphics.hpp>

App::App(): window{nullptr}, appState{AppState::MENU}, menuModel{nullptr}, menuView{nullptr}, menuController{nullptr}, levelModel{nullptr}, levelView{nullptr}, levelController{nullptr}
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(desktop, "Baba Is You", sf::Style::Fullscreen);
    window->setFramerateLimit(60);
    window->setFramerateLimit(60);
    menuModel = new MenuModel;
    menuView = new MenuView{*window, *menuModel};
    menuController = new MenuController{*window, *menuModel, *menuView};
}

App::~App()
{
    if (levelModel != nullptr)
    {
        delete levelModel;
        delete levelView;
        delete levelController;
    }
    if (menuModel != nullptr)
    {
        delete menuModel;
        delete menuView;
        delete menuController;
    }
    window->close();
    delete window;
}

void App::run()
{
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

void App::update(const Notification& notification)
{
    const Victory* victory;
    const Quit* quit;
    victory = dynamic_cast<const Victory*>(&notification);
    quit = dynamic_cast<const Quit*>(&notification);
    if (victory != nullptr)
        this->updateFromVictory();
    else if (quit != nullptr)
        this->updateFromQuit();
}

void App::updateFromVictory()
{
    appState = AppState::MENU;
}

void App::updateFromQuit()
{
    appState = AppState::QUIT;
}

void App::changeState(AppState nextAppState)
{
    appState = nextAppState;
}

void App::initMenu()
{
    if (menuModel == nullptr)
    {
        menuModel = new MenuModel;
        menuView = new MenuView{*window, *menuModel};
        menuController = new MenuController{*window, *menuModel, *menuView};
    }
    if (levelModel != nullptr)
    {
        delete levelModel;
        delete levelView;
        delete levelController;
        levelModel = nullptr;
        levelView = nullptr;
        levelController = nullptr;
    }
}

void App::processMenu()
{
    this->initMenu();
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

void App::initLevel()
{
    if (levelModel == nullptr)
    {
        levelModel = new Model{menuController->getWhichLevelRequested()};
        levelModel->addObserver(dynamic_cast<Observer*>(this));
        levelView = new View{*levelModel, *window};
        levelController = new Controller{*window, *levelModel};
        levelController->addObserver(dynamic_cast<Observer*>(this));
    }
    if (menuModel != nullptr)
    {
        delete menuModel;
        delete menuView;
        delete menuController;
        menuModel = nullptr;
        menuView = nullptr;
        menuController = nullptr;
    }
}

void App::processLevel()
{
    this->initLevel();
    while (appState == AppState::LEVEL)
    {
        levelController->handleEvent();
        window->clear();
        levelView->draw();
        window->display();
    }
}
