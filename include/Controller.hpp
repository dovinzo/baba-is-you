#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Subject.hpp"

class Controller: public Subject
{
    public:
        Controller() = delete;
        Controller(sf::RenderWindow& window, Model& model);
        void handleEvent();
    private:
        sf::RenderWindow& window;
        Model& model;
};

#endif
