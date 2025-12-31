#ifndef BOARDSNAPSHOT_HPP
#define BOARDSNAPSHOT_HPP

#include "Board.hpp"
#include "BoardElement.hpp"
#include <vector>

class BoardSnapshot
{
    friend class Board;
    public:
        BoardSnapshot() = delete;
        BoardSnapshot(const Board& board);
        BoardSnapshot& operator=(const BoardSnapshot& other) = delete;
        //BoardSnapshot(const BoardSnapshot& other) = delete;
        //BoardSnapshot(const BoardSnapshot &other);
        ~BoardSnapshot();
    private:
        int width;
        int height;
        std::vector<BoardElement*>** grid;
};

#endif
