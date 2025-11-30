#ifndef BOARD_ELEMENTS_HPP
#define BOARD_ELEMENTS_HPP

#include "Enums.hpp"
#include <vector>
#include <iostream>

using namespace std;




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
    // le constructeur protected empêche l'instanciation directe de cette classe.

public:
    virtual ~Board_elements(); 
    void set_position(const vector<int>& new_pos);
    vector<int> get_position() const;


};

class physical_board_element : public Board_elements
{
private:
    physical_type type;
public : 
    physical_board_element(physical_type t, vector<int> v) :  Board_elements(v), type(t) {};
    physical_type get_type() const { return type; }
};

class meaningful_board_element : public Board_elements
{
private:
    meaningful_type type;
public :
    meaningful_board_element(meaningful_type t, vector<int> v) :  Board_elements(v), type(t) {};
    meaningful_type get_type() const { return type; }
};

#endif // BOARD_ELEMENTS_HPP