#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enums.hpp"

Controller::Controller(App& app, Model& model): app{app}, model{model}
{
}

void Controller::handleEvent()
{
    sf::Event event;
    while (app.window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.appState = AppState::QUIT;
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                model.moveLeft();
                if (model.checkWin())
                    app.appState = AppState::MENU;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                model.moveRight();
                if (model.checkWin())
                    app.appState = AppState::MENU;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                model.moveUp();
                if (model.checkWin())
                    app.appState = AppState::MENU;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                model.moveDown();
                if (model.checkWin())
                    app.appState = AppState::MENU;
            }
        }
    }
}
