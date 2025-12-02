
#include "Board_elements.hpp"

int Board_elements::id_counter = 0;

Board_elements::~Board_elements() = default;

void Board_elements::set_position(const vector<int>& new_pos) {
    position = new_pos;
}

vector<int> Board_elements::get_position() const {
    return position;
}
