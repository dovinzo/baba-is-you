#include "Board.hpp"

Board::Board(const vector<vector<int>> _dimensions) : dimensions(_dimensions) {}; 

void Board::add_element(int x, int y, Board_elements* elem)
{
    current_config[x][y].push_back(elem);
}



// TO DO faire un truc propre

// renvoie un vecteur de trois mots
// nulle : à chaque fois qu'on bouge un meaniglful element
// on check TOUT le BOARD. peut-être juste une zone autour de l'élément bougé ?
const vector<vector<meaningful_board_element*>> Board::get_words()
{
    vector<vector<meaningful_board_element*>> sentences;
    for (size_t i = 0; i < current_config.size(); ++i) {
        for (size_t j = 0; j < current_config[i].size(); ++j) {
            for (size_t k = 0; k < current_config[i][j].size(); ++k) {


                /* antoine passion c++ : on fait un dynamic cast de l'élement !
                si c'est meaningful, c'est pas nulptr, sinon ça l'est ...
                est-ce que ça va marcher ............ */
                Board_elements* elem = current_config[i][j][k];
                meaningful_board_element* m_elem = dynamic_cast<meaningful_board_element*>(elem);
                if (m_elem) {
                    // on a un meaningful element : on regarde autour. 
                    // ça fait au plus 8 autres cases à regarder 
                    // à gauche
                    if (j >= 2) {
                        meaningful_board_element* middle = dynamic_cast<meaningful_board_element*>(current_config[i][j-1][k]);
                        meaningful_board_element* last   = dynamic_cast<meaningful_board_element*>(current_config[i][j-2][k]);
                        if (middle && last) {
                            // on a un mot vertical
                            sentences.push_back({last, middle, m_elem});
                        }
                    }
                    // à droite 
                    if (j + 2 < current_config[i].size()) {
                        meaningful_board_element* middle = dynamic_cast<meaningful_board_element*>(current_config[i][j+1][k]);
                        meaningful_board_element* last   = dynamic_cast<meaningful_board_element*>(current_config[i][j+2][k]);
                        if (middle && last) {
                            // on a un mot vertical
                            sentences.push_back({m_elem, middle, last});

                        }
                    // en haut
                    }
                    if (i + 2 < current_config.size()) {
                        meaningful_board_element* middle = dynamic_cast<meaningful_board_element*>(current_config[i+1][j][k]);
                        meaningful_board_element* last   = dynamic_cast<meaningful_board_element*>(current_config[i+2][j][k]);
                        if (middle && last) {
                            // on a un mot horizontal
                            sentences.push_back({m_elem, middle, last});   
                        }
                    // en bas
                    if (i >= 2) {
                        meaningful_board_element* middle = dynamic_cast<meaningful_board_element*>(current_config[i-1][j][k]);
                        meaningful_board_element* last   = dynamic_cast<meaningful_board_element*>(current_config[i-2][j][k]);
                        if (middle && last) {
                            // on a un mot horizontal
                            sentences.push_back({last, middle, m_elem});  
                        }
                    }
            
                }
            }
        }
    }

    // et on enlève les doublons 

    struct SentenceLess {
        bool operator()(const vector<meaningful_board_element*>& a,
                        const vector<meaningful_board_element*>& b) const {
            return std::make_tuple(a[0], a[1], a[2]) <
                   std::make_tuple(b[0], b[1], b[2]);
        }
    };

    struct SentenceEqual {
        bool operator()(const vector<meaningful_board_element*>& a,
                        const vector<meaningful_board_element*>& b) const {
            return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
        }
    };

    std::sort(sentences.begin(), sentences.end(), SentenceLess());
    sentences.erase(
        std::unique(sentences.begin(), sentences.end(), SentenceEqual()),
        sentences.end()
    );

    return sentences;
}