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
class App;

class View
{

    friend class App;

public:
    View() = delete;
    View(const View &view) = delete;
    View &operator=(const View &view) = delete;

private:
    View(Model &model, sf::RenderWindow &window);
    virtual ~View();

    void draw();

    void createTextures();

    void updateSpriteFromBoardElement(sf::Sprite &sprite, BoardElement &boardElement);

    float calculateSpritesScale();

    int convertXGridToXScreen(int xGrid);

    int convertYGridToYScreen(int yGrid);

    /**
     * @brief Dictionnaire entre le type des éléments du board
     *        pouvant s'afficher à l'écran et leur texture correspondante.
     */
    std::unordered_map<BoardElementType, sf::Texture *> textures;

    Model &model;

    sf::RenderWindow &window;
};

#endif
