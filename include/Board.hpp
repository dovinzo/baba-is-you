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

class BoardSnapshot;
class Model;

class Board
{
    public:
        Board() = delete;
        Board(const Board& board) = delete;
        ~Board();
        int getWidth() const;
        int getHeight() const;

        friend class Model;
        friend class BoardSnapshot;


    private:
    
        explicit Board(int level);
        Board& operator=(const BoardSnapshot& boardSnapshot);
        std::vector<BoardElement*> operator()(int x, int y) const;
        void spawnBoardElement(BoardElementType boardElementType, int x, int y);
        void createEmptyGrid(int width, int height);
        const BoardSnapshot* makeSnapshot() const;
        void setNewPosition(BoardElement* boardElement, int xNew, int yNew);
        void killCell(int x, int y);


        int width;
        int height;
        std::vector<BoardElement*>** grid;
};

#endif
