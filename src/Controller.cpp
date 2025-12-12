#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Controller::handleEvent(Model& model, sf::Event& event, sf::RenderWindow& window)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
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
        }
    }
}
