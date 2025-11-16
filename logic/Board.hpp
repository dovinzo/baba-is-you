#ifndef BOARD_HPP
#define BOARD_HPP 

#include <vector>
#include <iostream>

using namespace std;

class Board_elements;
class Model; // pour petre décklaré ami avec Board

class Board
{
private:
    vector<vector<vector<Board_elements*>>> current_config; //3D vector to hold pointers to board elements
    /* faire attention aux cast
    parce que les BoardElements* peuvent pointer vers des physical_board_element* ou des rule_board_element*
    */ 
    const vector<vector<int>> dimensions; // dimensions of the board

    void add_element(int x, int y, Board_elements* elem); 

public:
    Board(const vector<vector<int>> _dimensions); 
    ~Board(); // TO DO !!!! 

friend class Model;

};


#endif //BOARD_HPP
