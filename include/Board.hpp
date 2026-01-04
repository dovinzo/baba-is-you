#ifndef BOARD_HPP
#define BOARD_HPP

#include "Enums.hpp"
#include "BoardElement.hpp"
#include <string>
#include <vector>

class BoardSnapshot;
class Model;

class Board
{
    public:
        Board() = delete;
        ~Board();
        Board(const Board& board) = delete;
        int getWidth() const;
        int getHeight() const;
        std::vector<BoardElement*> getCell(int x, int y) const;

        friend class Model;
        friend class BoardSnapshot;


    private:
    
        Board(int level);
        Board& operator=(const BoardSnapshot& boardSnapshot);
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
