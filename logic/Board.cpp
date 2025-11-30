#include "Board.hpp"
#include <algorithm>
#include <tuple>

Board::Board(const vector<int>& _dimensions) : current_config{}, dimensions(_dimensions)
{
    // initialise la grille 3D avec des listes vides
    int width  = dimensions.size() > 0 ? dimensions[0] : 0;
    int height = dimensions.size() > 1 ? dimensions[1] : 0;
    current_config.resize(width);
    for (auto& column : current_config) {
        column.resize(height);
    }
}

Board::~Board() = default;

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

    size_t width  = current_config.size();
    size_t height = 0;
    if (width > 0) {
        height = current_config[0].size();
    }

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            const vector<Board_elements*>& cell = current_config[i][j];
            for (size_t k = 0; k < cell.size(); ++k) {
                Board_elements* elem = cell[k];
                meaningful_board_element* m_elem =
                    dynamic_cast<meaningful_board_element*>(elem);
                if (!m_elem) {
                    continue;
                }

                // LEFT (j-1) and LEFT-LEFT (j-2): (last, middle, m_elem)
                if (j >= 2) {
                    const vector<Board_elements*>& cell_left1 = current_config[i][j - 1];
                    const vector<Board_elements*>& cell_left2 = current_config[i][j - 2];

                    for (size_t k1 = 0; k1 < cell_left1.size(); ++k1) {
                        meaningful_board_element* middle =
                            dynamic_cast<meaningful_board_element*>(cell_left1[k1]);
                        if (!middle) continue;

                        for (size_t k2 = 0; k2 < cell_left2.size(); ++k2) {
                            meaningful_board_element* last =
                                dynamic_cast<meaningful_board_element*>(cell_left2[k2]);
                            if (!last) continue;

                            vector<meaningful_board_element*> sentence;
                            sentence.push_back(last);
                            sentence.push_back(middle);
                            sentence.push_back(m_elem);
                            sentences.push_back(sentence);
                        }
                    }
                }

                // RIGHT (j+1) and RIGHT-RIGHT (j+2): (m_elem, middle, last)
                if (j + 2 < height) {
                    const vector<Board_elements*>& cell_right1 = current_config[i][j + 1];
                    const vector<Board_elements*>& cell_right2 = current_config[i][j + 2];

                    for (size_t k1 = 0; k1 < cell_right1.size(); ++k1) {
                        meaningful_board_element* middle =
                            dynamic_cast<meaningful_board_element*>(cell_right1[k1]);
                        if (!middle) continue;

                        for (size_t k2 = 0; k2 < cell_right2.size(); ++k2) {
                            meaningful_board_element* last =
                                dynamic_cast<meaningful_board_element*>(cell_right2[k2]);
                            if (!last) continue;

                            vector<meaningful_board_element*> sentence;
                            sentence.push_back(m_elem);
                            sentence.push_back(middle);
                            sentence.push_back(last);
                            sentences.push_back(sentence);
                        }
                    }
                }

                // DOWN (i+1) and DOWN-DOWN (i+2): (m_elem, middle, last)
                if (i + 2 < width) {
                    const vector<Board_elements*>& cell_down1 = current_config[i + 1][j];
                    const vector<Board_elements*>& cell_down2 = current_config[i + 2][j];

                    for (size_t k1 = 0; k1 < cell_down1.size(); ++k1) {
                        meaningful_board_element* middle =
                            dynamic_cast<meaningful_board_element*>(cell_down1[k1]);
                        if (!middle) continue;

                        for (size_t k2 = 0; k2 < cell_down2.size(); ++k2) {
                            meaningful_board_element* last =
                                dynamic_cast<meaningful_board_element*>(cell_down2[k2]);
                            if (!last) continue;

                            vector<meaningful_board_element*> sentence;
                            sentence.push_back(m_elem);
                            sentence.push_back(middle);
                            sentence.push_back(last);
                            sentences.push_back(sentence);
                        }
                    }
                }

                // UP (i-1) and UP-UP (i-2): (last, middle, m_elem)
                if (i >= 2) {
                    const vector<Board_elements*>& cell_up1 = current_config[i - 1][j];
                    const vector<Board_elements*>& cell_up2 = current_config[i - 2][j];

                    for (size_t k1 = 0; k1 < cell_up1.size(); ++k1) {
                        meaningful_board_element* middle =
                            dynamic_cast<meaningful_board_element*>(cell_up1[k1]);
                        if (!middle) continue;

                        for (size_t k2 = 0; k2 < cell_up2.size(); ++k2) {
                            meaningful_board_element* last =
                                dynamic_cast<meaningful_board_element*>(cell_up2[k2]);
                            if (!last) continue;

                            vector<meaningful_board_element*> sentence;
                            sentence.push_back(last);
                            sentence.push_back(middle);
                            sentence.push_back(m_elem);
                            sentences.push_back(sentence);
                        }
                    }
                }
            }
        }
    }

    // Remove duplicates
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

void Board::rebuild_from_positions()
{
    size_t width  = current_config.size();
    size_t height = 0;
    if (width > 0) {
        height = current_config[0].size();
    }

    vector<vector<vector<Board_elements*> > > rebuilt;
    rebuilt.resize(width);
    for (size_t x = 0; x < width; ++x) {
        rebuilt[x].resize(height);
    }

    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            vector<Board_elements*>& cell = current_config[x][y];
            for (size_t idx = 0; idx < cell.size(); ++idx) {
                Board_elements* elem = cell[idx];
                vector<int> pos = elem->get_position();
                if (pos.size() < 2) {
                    continue;
                }
                int nx = pos[0];
                int ny = pos[1];
                if (nx < 0 || ny < 0) {
                    continue;
                }
                if (nx >= static_cast<int>(width) || ny >= static_cast<int>(height)) {
                    continue;
                }
                rebuilt[static_cast<size_t>(nx)][static_cast<size_t>(ny)].push_back(elem);
            }
        }
    }

    current_config.swap(rebuilt);
}


