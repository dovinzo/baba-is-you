#ifndef BOARD_HPP
#define BOARD_HPP

#include "Enums.hpp"
#include "BoardElement.hpp"
#include <string>
#include <vector>

class BoardSnapshot;

class Board
{
    public:
        Board() = delete;
        Board(int level);
        ~Board();
        int getWidth() const;
        int getHeight() const;
        std::vector<BoardElement*> getCell(int x, int y) const;
        void setNewPosition(BoardElement* boardElement, int xNew, int yNew);
        const BoardSnapshot* makeSnapshot() const;
        void restore(const BoardSnapshot* boardSnapshot);
    private:
        void spawnBoardElement(BoardElementType boardElementType, int x, int y);
        void createEmptyGrid(int width, int height);
    private:
        int width;
        int height;
        std::vector<BoardElement*>** grid;
};

#endif
