#ifndef BOARD_HPP
#define BOARD_HPP

#include "Enums.hpp"
#include "BoardElement.hpp"
#include <string>
#include <vector>

class Board
{
    friend class View;
    friend class Model;
    public:
        Board();
        ~Board();
        void createEmptyGrid(int width, int height);
        int getWidth() const;
        int getHeight() const;
        std::vector<BoardElement*> getCell(int x, int y) const;
        //int findPositionI(BoardElement* boardElement) const;
        //int findPositionJ(BoardElement* boardElement) const;
        void loadLevel(const std::string& filePath);
        void setNewPosition(BoardElement* boardElement, int xNew, int yNew);
    private:
        int width;
        int height;
        std::vector<BoardElement*>** grid;
        void spawnBoardElement(BoardElementType boardElementType, int x, int y);
};

#endif
