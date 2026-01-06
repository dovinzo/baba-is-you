#ifndef BOARDHISTORY_HPP
#define BOARDHISTORY_HPP

#include "BoardSnapshot.hpp"
#include "Board.hpp"
#include <vector>

/* Toujours pour le Pattern Memento, on stock un pile (bien qu'ici ce soit un vector) des actions
dans l'optique de pouvoir faire un Undo et un Redo.*/

class Model; 

class BoardHistory
{
    friend class Model; // c'est le model qui empile les snapshots. 

    public : 
        BoardHistory(const BoardHistory& other) = delete;
        BoardHistory& operator=(const BoardHistory& other) = delete;
        ~BoardHistory();
        
    private:
        BoardHistory() = default;
        void push(const BoardSnapshot* boardSnapshot);

        // lors d'un undo, on dépile, et on restaure le dernier élément de la pile. 
        const BoardSnapshot* undo(); 
        const BoardSnapshot* redo();

        /* On a deux piles : l'un pour l'Undo, l'autre pour le Redo. 
        Une autre méthode, plus économme, aurait pu être de créer une seule liste
        d'historique et de "déplacer la tête de lecture" vers la gauche lors d'un undo, 
        et vers la droite lors d'un redo. */
        std::vector<const BoardSnapshot*> boardSnapshotsForUndo; 
        std::vector<const BoardSnapshot*> boardSnapshotsForRedo;
};

#endif
