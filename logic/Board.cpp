#include "Board.hpp"

Board::Board(const vector<vector<int>> _dimensions) : dimensions(_dimensions) {}; 

void Board::add_element(int x, int y, BoardElements* elem)
{
    current_config[x][y].push_back(elem);
}