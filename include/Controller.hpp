#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"

class Controller
{
    public:
        void handleEvent(Model& model, sf::Event& event, sf::RenderWindow& window);
};

#endif
