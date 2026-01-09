#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Quit.hpp"
#include "Subject.hpp"
#include "Enums.hpp"

/* Controller d'un niveau, Gère le lien entre le modèle et la vu. Rôle assez minime dans notre
implémentation, car il se contente de gérer les inputs de l'utilisateurs. */

class App;

class Controller : public Subject
{
public:
    Controller() = delete;

    friend class App;

private:
    virtual ~Controller() = default;
    Controller(sf::RenderWindow &window, Model &model); // uniquement possible par l'App
    void handleEvent();                                 // gère les inputs

    // envoie les input au modèle
    sf::RenderWindow &window;
    Model &model;
};

#endif
