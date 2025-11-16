#ifndef LOGIC_RULES_HPP
#define LOGIC_RULES_HPP 

#include <vector>
#include <iostream>

using namespace std;

class BoardElements;

class Board
{
private:
    vector<vector<vector<BoardElements>>> current_config; //3D vector to hold board elements

public:
    Board(); // to do : comment on le construit ? on importe un fichier de configuration ?
    ~Board();
};


#endif // LOGIC_BOARD_HPP
