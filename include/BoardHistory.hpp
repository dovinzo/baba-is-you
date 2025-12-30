#ifndef BOARDHISTORY_HPP
#define BOARDHISTORY_HPP

#include "BoardSnapshot.hpp"
#include "Board.hpp"
#include <vector>

class Model; 

class BoardHistory
{
    friend class Model;
        
    private:
        BoardHistory() = default;
        ~BoardHistory();
        void push(const BoardSnapshot* boardSnapshot);
        const BoardSnapshot* undo();
        const BoardSnapshot* redo();
        std::vector<const BoardSnapshot*> boardSnapshotsForUndo;
        std::vector<const BoardSnapshot*> boardSnapshotsForRedo;
};

#endif
