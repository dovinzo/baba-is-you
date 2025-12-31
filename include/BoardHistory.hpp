#ifndef BOARDHISTORY_HPP
#define BOARDHISTORY_HPP

#include "BoardSnapshot.hpp"
#include "Board.hpp"
#include <vector>

class Model; 

class BoardHistory
{
    friend class Model;

    public : 
        BoardHistory(const BoardHistory& other) = delete;
        BoardHistory& operator=(const BoardHistory& other) = delete;
        ~BoardHistory();
        
    private:
        BoardHistory() = default;
       


        void push(const BoardSnapshot* boardSnapshot);
        const BoardSnapshot* undo();
        const BoardSnapshot* redo();
        std::vector<const BoardSnapshot*> boardSnapshotsForUndo;
        std::vector<const BoardSnapshot*> boardSnapshotsForRedo;
};

#endif
