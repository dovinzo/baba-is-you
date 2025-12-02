#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Controller::handleEvent(sf::Event& event, sf::RenderWindow& window, Model& model)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
                model.move('L');
            else if (event.key.code == sf::Keyboard::Right)
                model.move('R');
            else if (event.key.code == sf::Keyboard::Up)
                model.move('U');
            else if (event.key.code == sf::Keyboard::Down)
                model.move('D');
        }
    }
}
