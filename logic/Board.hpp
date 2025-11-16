#ifndef LOGIC_RULES_HPP
#define LOGIC_RULES_HPP 

#include <vector>
#include <iostream>

using namespace std;

class BoardElements;

class Board
{
private:
    vector<vector<vector<BoardElements*>>> current_config; //3D vector to hold pointers to board elements
    const vector<vector<int>> dimensions; // dimensions of the board

    void add_element(int x, int y, BoardElements* elem); 

public:
    Board(const vector<vector<int>> _dimensions); // to do : comment on le construit ? on importe un fichier de configuration ?
    ~Board(); // TO DO !!!! 
};


#endif // LOGIC_BOARD_HPP
