#ifndef BOARDHISTORY_HPP
#define BOARDHISTORY_HPP

#include "BoardSnapshot.hpp"
#include "Board.hpp"
#include <vector>

class BoardHistory
{
    public:
        BoardHistory() = default;
        ~BoardHistory();
        void push(const BoardSnapshot* boardSnapshot);
        const BoardSnapshot* undo();
        const BoardSnapshot* redo();
    private:
        std::vector<const BoardSnapshot*> boardSnapshotsForUndo;
        std::vector<const BoardSnapshot*> boardSnapshotsForRedo;
};

#endif
