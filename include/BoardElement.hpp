#ifndef BOARDELEMENT_HPP
#define BOARDELEMENT_HPP

#include "Enums.hpp"

/* Un BoardElement est un élément de la grille.
Il contient des informations sur son type, sa position, et sa catégorie. Le Board possède leurs adresses.
Par choix de conception, les règles ne sont pas encapsulés directement dans les éléments, pour
éviter une copie inutile d'information (pattern Flyweight) */

class Board;
class BoardSnapshot;

class BoardElement
{
public:
    BoardElement() = delete;
    BoardElement(const BoardElement &boardElement) = delete;
    BoardElement &operator=(const BoardElement &boardElement) = delete;

    BoardElementCategory getCategory() const;
    BoardElementType getType() const;
    int getPositionX() const;
    int getPositionY() const;

    // seuls les Board et BoardSnapshot peuvent en construire.
    friend class Board;
    friend class BoardSnapshot;

private:
    BoardElementType type;

    int x;
    int y;

    BoardElement(BoardElementType type, int x, int y);
    virtual ~BoardElement() = default;

    static BoardElementType intToBoardElementType(int typeCode); // convertisseur lors de la création du niveau à partir d'un fichier txt.
    void setPositionX(int x);
    void setPositionY(int y);
};

#endif
