#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"

/**
 * @class Controller
 * @brief Représente le contrôleur dans le design pattern MVC.
 */
class Controller
{
    public:

        /**
         * @brief S'occupe de traiter/interpréter les évènements issus du clavier et de la souris.
         *
         * @param event
         *        Instance de sf::Event qui sera remplie par la fonction pollEvent
         *        pour récupérer les évènements issus du clavier et de la souris.
         * @param window
         *        Fenêtre du jeu, qui devra être fermée si le joueur clique
         *        sur la croix en haut à droite.
         * @param model
         *        Modèle du jeu, dans le design pattern MVC, qui sera modifié
         *        en fonction des évènements.
         */
        void handleEvent(sf::Event& event, sf::RenderWindow& window, Model& model);
};

#endif
