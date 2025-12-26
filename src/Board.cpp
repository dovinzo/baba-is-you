#include "Board.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
#include "BoardSnapshot.hpp"
#include <fstream> // pour std::ifstream
#include <string> // pour std::string
#include <sstream> // pour std::istringstream
#include <iostream>

Board::Board(int level): width{}, height{}, grid{}
{
    std::string filePath = "assets/level" + std::to_string(level) + ".txt";
    std::string line;
    int x, y, typeCode, width, height;
    BoardElementType boardElementType;
    std::ifstream file{filePath}; // ouvre le fichier en lecture
    std::getline(file, line);
    std::istringstream iss{line};
    iss >> width >> height;
    this->createEmptyGrid(width, height);
    while (std::getline(file, line))
    {
        std::istringstream iss{line};
        iss >> x >> y >> typeCode;
        boardElementType = BoardElement::intToBoardElementType(typeCode);
        this->spawnBoardElement(boardElementType, x, y);
    }
}

Board::~Board()
{
    for (int i = 0 ; i < width ; i++)
    {
        for (int j = 0 ; j < height ; j++)
        {
           while (not grid[i][j].empty())
           {
               delete grid[i][j].back();
               grid[i][j].pop_back();
           }
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Board::createEmptyGrid(int width, int height)
{
    this->width = width;
    this->height = height;
    grid = new std::vector<BoardElement*>*[width]{nullptr};
    for (int i = 0 ; i < width ; i++)
    {
        grid[i] = new std::vector<BoardElement*>[height]{};
    }
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

void Board::setNewPosition(BoardElement* boardElement, int xNew, int yNew)
{
    int xOld{boardElement->getPositionX()};
    int yOld{boardElement->getPositionY()};
    boardElement->setPositionX(xNew);
    boardElement->setPositionY(yNew);
    for (int i = 0 ; i < static_cast<int>(grid[xOld][yOld].size()) ; i++)
    {
        if (grid[xOld][yOld][i] == boardElement)
        {
            grid[xOld][yOld].erase(grid[xOld][yOld].begin() + i);
            grid[xNew][yNew].push_back(boardElement);
            break;
        }
    }
}

const BoardSnapshot* Board::makeSnapshot() const
{
    return new BoardSnapshot{*this};
}

void Board::restore(const BoardSnapshot* boardSnapshot)
{
    if (boardSnapshot == nullptr)
        return;
    for (int x = 0 ; x < width ; x++)
    {
        for (int y = 0 ; y < height ; y++)
        {
            while (not grid[x][y].empty())
            {
                delete grid[x][y].back();
                grid[x][y].pop_back();
           }
           for (int i = 0 ; i < static_cast<int>(boardSnapshot->grid[x][y].size()) ; i++)
           {
               grid[x][y].push_back(new BoardElement{boardSnapshot->grid[x][y][i]->getType(), x, y});
           }
        }
    }
}

void Board::spawnBoardElement(BoardElementType boardElementType, int x, int y)
{
    grid[x][y].push_back(new BoardElement{boardElementType, x, y});
}

std::vector<BoardElement*> Board::getCell(int x, int y) const
{
    return grid[x][y];
}
