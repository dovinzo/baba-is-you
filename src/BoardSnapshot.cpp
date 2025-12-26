#include "BoardSnapshot.hpp"
#include "Board.hpp"
#include <vector>

BoardSnapshot::BoardSnapshot(const Board& board): width{board.getWidth()}, height{board.getHeight()}, grid{nullptr}
{
    std::vector<BoardElement*> cell;
    grid = new std::vector<BoardElement*>*[width]{nullptr};
    for (int i = 0 ; i < width ; i++)
    {
        grid[i] = new std::vector<BoardElement*>[height]{};
    }
    for (int x = 0 ; x < width ; x++)
    {
        for (int y = 0 ; y < height ; y++)
        {
            cell = board.getCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                grid[x][y].push_back(new BoardElement{cell[i]->getType(), x, y});
            }
        }
    }
}

//BoardSnapshot::BoardSnapshot(const BoardSnapshot &other): width{other.width}, height{other.height}, grid{nullptr}
//{
    //grid = new std::vector<BoardElement*>*[width]{nullptr};
    //for (int i = 0 ; i < width ; i++)
    //{
        //grid[i] = new std::vector<BoardElement*>[height]{};
    //}
    //for (int x = 0 ; x < width ; x++)
    //{
        //for (int y = 0 ; y < height ; y++)
        //{
            //for (int i = 0 ; i < static_cast<int>(other.grid[x][y].size()) ; i++)
            //{
                //grid[x][y].push_back(new BoardElement{other.grid[x][y][i]->getType(), x, y});
            //}
        //}
    //}
//}

BoardSnapshot::~BoardSnapshot()
{
    for (int x = 0 ; x < width ; x++)
    {
        for (int y = 0 ; y < height ; y++)
        {
           while (not grid[x][y].empty())
           {
               delete grid[x][y].back();
               grid[x][y].pop_back();
           }
        }
        delete[] grid[x];
    }
    delete[] grid;
}
