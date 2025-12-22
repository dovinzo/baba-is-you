#include "MenuController.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>

MenuController::MenuController(App& app, MenuModel& model, MenuView& view): app{app}, model{model}, view{view}
{
}

void MenuController::handleEvent()
{
    sf::Event event;
    while (app.window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.appState = AppState::QUIT;
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                model.previous();
                view.update();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                model.next();
                view.update();
            }
            else if (event.key.code == sf::Keyboard::Enter)
                this->selectLevel();
        }
    }
}

void MenuController::selectLevel()
{
    app.appState = AppState::LEVEL;
    MenuItem item = model.getMenuItem();
    switch (item)
    {
        case MenuItem::LEVEL1:
            app.chosenLevel = 1;
            break;
        case MenuItem::LEVEL2:
            app.chosenLevel = 2;
            break;
        case MenuItem::LEVEL3:
            app.chosenLevel = 3;
            break;
    }
}