#ifndef BOARDSNAPSHOT_HPP
#define BOARDSNAPSHOT_HPP

#include "Board.hpp"
#include "BoardElement.hpp"
#include <vector>

/* La class BoardSnapshot est le fruit du pattern Memento. L'idée, c'est que pour storer l'historique
des Board dans l'optique de faire un Undo/Redo, il n'est pas nécessaire de stocker tout un Board 
(avec ses différentes méthodes), mais simplement une photographie de sa configuration (sans les règles).
Ensuite, on pourra le restaurer à l'aide de la surcharge de = pour Board. */

class BoardSnapshot
{
    friend class Board; // seul un Board peut se prendre en photo. 

    public:
        BoardSnapshot() = delete;
        BoardSnapshot& operator=(const BoardSnapshot& other) = delete;
        BoardSnapshot(const BoardSnapshot& other) = delete;
        ~BoardSnapshot();
    private:
        // il s'agit seulement d'une photographie : pas de getter, etc. 
        explicit BoardSnapshot(const Board& board);
        std::vector<BoardElement*>& operator()(int x, int y);
        const std::vector<BoardElement*>& operator()(int x, int y) const;
        int width;
        int height;
        std::vector<BoardElement*>** grid;
};

#endif
