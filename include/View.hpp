#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
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
        void update();

        /**
         * @brief Dessine à l'écran (i.e. sur la fenêtre du jeu) la vue.
         *
         * @param window
         *        Fenêtre du jeu.
         * @param model
         *        Modèle du jeu permettant de parcourir
         *        les sprites dans le bon ordre pour la superposition.
         */
        void draw();

    private:

        void createTextures();

        void createSprites();

        void createSprite(BoardElement* boardElement);

        float calculateSpritesScale();

        int convertXGridToXScreen(int xGrid);

        int convertYGridToYScreen(int yGrid);

    private:

        /**
         * @brief Dictionnaire entre le type des éléments du board
         *        pouvant s'afficher à l'écran et leur texture correspondante.
         */
        std::unordered_map<BoardElementType, sf::Texture*> textures;

        /**
         * @brief Dictionnaire entre chaque élément du board et leur sprite
         *        correspondant permettant d'afficher l'élément du board à l'écran.
         */
        std::unordered_map<BoardElement*, sf::Sprite*> sprites;

        Model& model;

        sf::RenderWindow& window;
};

#endif
