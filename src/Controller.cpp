#include "Controller.hpp"

Controller::Controller(sf::RenderWindow& window, Model& model): window{window}, model{model}
{
}

Direction sf_keyboard_to_direction(sf::Keyboard::Key direction)
{
    switch (direction)
    {
        case sf::Keyboard::Left:
            return Direction::LEFT;
        case sf::Keyboard::Right:
            return Direction::RIGHT;
        case sf::Keyboard::Up:
            return Direction::UP;
        case sf::Keyboard::Down:
            return Direction::DOWN;
        default:
            throw std::invalid_argument("Invalid direction key");
    }
}


void Controller::handleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                model.move(sf_keyboard_to_direction(event.key.code));
            else if (event.key.code == sf::Keyboard::P)
                model.undo();
            else if (event.key.code == sf::Keyboard::N)
                model.redo();
            else if (event.key.code == sf::Keyboard::Q)
                this->notifyObservers(Quit{});
        }
    }
}

