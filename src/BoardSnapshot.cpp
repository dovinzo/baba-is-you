#include "BoardSnapshot.hpp"
#include <vector>

BoardSnapshot::BoardSnapshot(const Board &board) : width{board.getWidth()}, height{board.getHeight()}, grid{nullptr}
{
    std::vector<BoardElement *> cell;
    grid = new std::vector<BoardElement *> *[width]
    { nullptr };
    for (int i = 0; i < width; i++)
    {
        grid[i] = new std::vector<BoardElement *>[height] {};
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            cell = board(x, y);
            for (int i = 0; i < static_cast<int>(cell.size()); i++)
            {
                (*this)(x, y).push_back(new BoardElement{cell.at(i)->getType(), x, y});
            }
        }
    }
}

std::vector<BoardElement *> &BoardSnapshot::operator()(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        throw std::out_of_range{"BoardSnapshot::operator(): coordonnées (" + std::to_string(x) + ", " + std::to_string(y) + ") hors de la grille."};
    }
    return grid[x][y];
}

const std::vector<BoardElement *> &BoardSnapshot::operator()(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        throw std::out_of_range{"BoardSnapshot::operator(): coordonnées (" + std::to_string(x) + ", " + std::to_string(y) + ") hors de la grille."};
    }
    return grid[x][y];
}

BoardSnapshot::~BoardSnapshot()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            while (not(*this)(x, y).empty())
            {
                delete (*this)(x, y).back();
                (*this)(x, y).pop_back();
            }
        }
        delete[] grid[x];
    }
    delete[] grid;
}
