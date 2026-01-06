#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Quit.hpp"
#include "Subject.hpp"

class App;

class Controller: public Subject
{
    public:
        Controller() = delete;

        friend class App;
    private:
        Controller(sf::RenderWindow& window, Model& model);
        void handleEvent();
        sf::RenderWindow& window;
        Model& model;
};

#endif
