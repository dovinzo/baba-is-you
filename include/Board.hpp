#ifndef BOARD_HPP
#define BOARD_HPP

#include "Enums.hpp"
#include "BoardElement.hpp"
#include "BoardSnapshot.hpp"

#include <string>
#include <vector>
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <cmath>

/* Le Board représente la grille de jeu. Elle ne connait pas les règles, et se contente
d'encapsuler les éléments de la grille, sous forme de pointeurs vers ces BoardElements. */

class Model;

class Board
{
    friend class Model;

    /* Le Model est responsable de la logique du jeu. Lorsqu'il est crée, le Model 
        crée un Board en lui passant le niveau à charger. Seul lui doit pouvoir le faire
        (Singleton pattern).
    */

    friend class BoardSnapshot;

    public:
        // rule of three pour plus de sécurité
        Board() = delete;
        Board(const Board& board) = delete;
        

        int getWidth() const;
        int getHeight() const;

        /* Le Model est responsable de la logique du jeu. Lorsqu'il est crée, le Model 
        crée un Board en lui passant le niveau à charger. Seul lui doit pouvoir le faire
        (Singleton pattern).
        */


    private:
        explicit Board(int level); // explicit pour éviter les conversions implicites. usage : level1.txt
        virtual ~Board();
        
        Board& operator=(const BoardSnapshot& boardSnapshot); // surcharge pour restaurer un snapshot
        const std::vector<BoardElement*>& operator()(int x, int y) const;

        void spawnBoardElement(BoardElementType boardElementType, int x, int y);
        void createEmptyGrid(int width, int height); // utilisé lors de la création du board

        const BoardSnapshot* makeSnapshot() const;
        void setNewPosition(BoardElement* boardElement, int xNew, int yNew);
        void killCell(int x, int y);

        std::vector<BoardElement*>** grid; // grille 3D dynamique de pointeurs vers BoardElement
        int width;
        int height;
};

#endif
