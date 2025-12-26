#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

Controller::Controller(sf::RenderWindow& window, Model& model, View& view): window{window}, model{model}, view{view}, menuRequested{false}, quitRequested{false}
{
}

void Controller::handleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            quitRequested = true;
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                model.moveLeft();
                //if (model.checkWin())
                    //menuRequested = true;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                model.moveRight();
                //if (model.checkWin())
                    //menuRequested = true;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                model.moveUp();
                //if (model.checkWin())
                    //menuRequested = true;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                model.moveDown();
                //if (model.checkWin())
                    //menuRequested = true;
            }
            else if (event.key.code == sf::Keyboard::P)
            {
                model.undo();
            }
            else if (event.key.code == sf::Keyboard::N)
            {
                model.redo();
            }
        }
    }
}

bool Controller::getMenuRequested() const
{
    return menuRequested;
}

bool Controller::getQuitRequested() const
{
    return quitRequested;
}
