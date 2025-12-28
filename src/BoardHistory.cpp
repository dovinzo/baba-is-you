#include "BoardHistory.hpp"
#include "Board.hpp"
#include "BoardSnapshot.hpp"

BoardHistory::~BoardHistory()
{
    while (not this->boardSnapshotsForUndo.empty())
    {
        delete this->boardSnapshotsForUndo.back();
        this->boardSnapshotsForUndo.pop_back();
    }
    while (not this->boardSnapshotsForRedo.empty())
    {
        delete this->boardSnapshotsForRedo.back();
        this->boardSnapshotsForRedo.pop_back();
    }
}

void BoardHistory::push(const BoardSnapshot* boardSnapshot)
{

    if (boardSnapshotsForUndo.size() >= 100)     
    {
        delete this->boardSnapshotsForUndo.front();
        this->boardSnapshotsForUndo.erase(this->boardSnapshotsForUndo.begin());
    }
    this->boardSnapshotsForUndo.push_back(boardSnapshot);
    while (not this->boardSnapshotsForRedo.empty())
    {
        delete this->boardSnapshotsForRedo.back();
        this->boardSnapshotsForRedo.pop_back();
    }
}

const BoardSnapshot* BoardHistory::undo()
{
    if (this->boardSnapshotsForUndo.size() <= 1)
        return nullptr;
    this->boardSnapshotsForRedo.push_back(this->boardSnapshotsForUndo.back());
    this->boardSnapshotsForUndo.pop_back();
    return this->boardSnapshotsForUndo.back();
}

const BoardSnapshot* BoardHistory::redo()
{
    if (this->boardSnapshotsForRedo.size() == 0)
        return nullptr;
    this->boardSnapshotsForUndo.push_back(this->boardSnapshotsForRedo.back());
    this->boardSnapshotsForRedo.pop_back();
    return this->boardSnapshotsForUndo.back();
}
