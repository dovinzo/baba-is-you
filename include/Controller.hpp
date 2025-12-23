#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"

class Controller
{
    public:
        Controller() = delete;
        Controller(sf::RenderWindow& window, Model& model, View& view);
        void handleEvent();
        bool getMenuRequested() const;
        bool getQuitRequested() const;
    private:
        sf::RenderWindow& window;
        Model& model;
        View& view;
        bool menuRequested;
        bool quitRequested;
};

#endif
