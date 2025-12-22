#include "App.hpp"
#include "Enums.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include <SFML/Graphics.hpp>

App::App(): window{sf::VideoMode(800, 800), "Baba Is You", sf::Style::Close}, appState{AppState::MENU}, chosenLevel{1}
{
    window.setFramerateLimit(60);
}

void App::run()
{
    while (window.isOpen())
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
                window.close();
                break;
        }
    }
}

void App::processMenu()
{
    MenuModel model;
    MenuView view{window, model};
    MenuController controller{*this, model, view};
    while (appState == AppState::MENU)
    {
        controller.handleEvent();
        window.clear();
        view.draw();
        window.display();
    }
}

void App::processLevel()
{
    Model model{chosenLevel};
    View view{model, window};
    Controller controller{*this, model};
    while (appState == AppState::LEVEL)
    {
        controller.handleEvent();
        view.update(model);
        window.clear();
        view.draw(window, model);
        window.display();
    }
}
