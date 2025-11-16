#include <vector>
#include <iostream>
using namespace std;

#ifndef BOARD_ELEMENTS_HPP
#define BOARD_ELEMENTS_HPP



class Board_elements // virtual class 
{
private:
    static int id_counter;
    const int id; // Unique identifier for each board element
    vector<int> position; // (x,y,z), z indique son niveau de superposition : 0 le plus en bas. 
    
protected :
    Board_elements(vector<int> pos) : id(id_counter), position(pos) {
        id_counter++;
    }; 

public:
    virtual ~Board_elements(); 
};

class physical_board_element : public Board_elements
{
private:
    physical_type type;
public : 
    physical_board_element(physical_type t, vector<int> v) : type(t), Board_elements(v) {};
};

class meaningful_board_element : public Board_elements
{
private:
    meaningful_type type;
public :
    meaningful_board_element(meaningful_type t, vector<int> v) : type(t), Board_elements(v) {};
};

#endif // BOARD_ELEMENTS_HPP