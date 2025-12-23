#include <SFML/Graphics.hpp>
#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include "Enums.hpp"

MenuController::MenuController(sf::RenderWindow& window, MenuModel& menuModel, MenuView& menuView): window{window}, menuModel{menuModel}, menuView{menuView}, levelRequested{false}, whichLevelRequested{}, quitRequested{false}
{
}

void MenuController::handleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            quitRequested = true;
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                menuModel.previous();
                menuView.update();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                menuModel.next();
                menuView.update();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                levelRequested = true;
                whichLevelRequested = MenuController::whichLevel(menuModel.getMenuItem());
            }
        }
    }
}

bool MenuController::getLevelRequested() const
{
    return levelRequested;
}

int MenuController::getWhichLevelRequested() const
{
    return whichLevelRequested;
}

bool MenuController::getQuitRequested() const
{
    return quitRequested;
}

int MenuController::whichLevel(MenuItem menuItem)
{
    int whichLevelRequested;
    switch (menuItem)
    {
        case MenuItem::LEVEL1:
            whichLevelRequested = 1;
            break;
        case MenuItem::LEVEL2:
            whichLevelRequested = 2;
            break;
        case MenuItem::LEVEL3:
            whichLevelRequested = 3;
            break;
    }
    return whichLevelRequested;
}
