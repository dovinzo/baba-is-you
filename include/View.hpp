#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include <unordered_map>

/**
 * @class View
 * @brief Représente la vue du jeu, dans le design pattern MVC.
 */
class View
{
    public:

        /**
         * @brief Construit un objet View, initialisé avec les données
         *        du modèle au début du jeu et de la taille de la fenêtre.
         *
         * @param model
         *        Modèle du jeu au début de la partie
         *        permettant d'initialiser la vue.
         * @param window
         *        Fenêtre du jeu, permettant de récupérer
         *        sa taille.
         */
        View(Model& model, sf::RenderWindow& window);

        ~View();

        /**
         * @brief Met à jour la vue à partir des données du modèle du jeu.
         *
         * @param model
         *        Modèle du jeu en cours.
         */
        void update(Model& model);

        /**
         * @brief Dessine à l'écran (i.e. sur la fenêtre du jeu) la vue.
         *
         * @param window
         *        Fenêtre du jeu.
         */
        void draw(sf::RenderWindow& window);

    private:

        /**
         * @brief Dictionnaire entre les noms des objets pouvant s'afficher
         *        à l'écran et leur texture correspondante.
         *
         *        Liste des textures :
         *        textures["BABA"], textures["ROCK"], textures["FLAG"],
         *        textures["WALL"], textures["TEXT_IS"], textures["TEXT_BABA"],
         *        textures["TEXT_YOU"], textures["TEXT_WALL"], textures["TEXT_PUSH"].
         */
        std::unordered_map<std::string, sf::Texture*> textures;

        /**
         * @brief Dictionnaire entre chaque id des objets du modèle et leur sprite
         *        correspondant permettant d'afficher l'objet du modèle à l'écran.
         */
        std::unordered_map<int, sf::Sprite*> sprites;
};

#endif