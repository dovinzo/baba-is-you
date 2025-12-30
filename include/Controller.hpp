#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Subject.hpp"

class App;

class Controller: public Subject
{
    public:
        Controller() = delete;
        Controller(sf::RenderWindow& window, Model& model);

        friend class App;
    private:
        void handleEvent();
        sf::RenderWindow& window;
        Model& model;
};

#endif
