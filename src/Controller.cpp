#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "Subject.hpp"
#include "Quit.hpp"

Controller::Controller(sf::RenderWindow& window, Model& model): window{window}, model{model}
{
}

void Controller::handleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->notifyObservers(Quit{});
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
                model.moveLeft();
            else if (event.key.code == sf::Keyboard::Right)
                model.moveRight();
            else if (event.key.code == sf::Keyboard::Up)
                model.moveUp();
            else if (event.key.code == sf::Keyboard::Down)
                model.moveDown();
            else if (event.key.code == sf::Keyboard::P)
                model.undo();
            else if (event.key.code == sf::Keyboard::N)
                model.redo();
        }
    }
}
