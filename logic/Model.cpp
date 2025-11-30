#include <fstream>
#include "Model.hpp"



// Fonction utilitaire pour charger un niveau à partir d'un fichier ASCII
vector<string> load_level_ascii(const string& path)
{
    ifstream file(path);
    vector<string> lines;
    string line;

    if (!file) {
        throw runtime_error("Impossible d'ouvrir " + path);
    }

    while (getline(file, line)) {
        if (!line.empty() && line[0] == '#') {
            continue; // on ignore les commentaires éventuels
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    return lines;
}

Board Model::load_level_from_file(const string& path)
{
    vector<string> lines = load_level_ascii(path);
    if (lines.empty()) {
        throw runtime_error("Fichier de niveau vide: " + path);
    }

    int height = static_cast<int>(lines.size());
    int width  = static_cast<int>(lines[0].size());

    vector<vector<int>> dimensions = { {width}, {height}}; // z dimension = 1 au début
    Board board(dimensions);

    for (int y = 0; y < height; ++y) {
        const string& row = lines[y];
        for (int x = 0; x < width; ++x) {
            char c = row[x];

            // position (x, y, z), z = 0 au début
            vector<int> pos = {x, y, 0};

            Board_elements* elem = nullptr;

            switch (c) {
                case 'W':
                    elem = new physical_board_element(physical_type::WALL, pos);
                    break;
                case 'B':
                    elem = new physical_board_element(physical_type::BABA, pos);
                    break;
                case 'F':
                    elem = new physical_board_element(physical_type::FLAG, pos);
                    break;
                case 'R':
                    elem = new physical_board_element(physical_type::ROCK, pos);
                    break;

                // UPPER CASE c'est pour physical, donc W correspond à un mur physique

                case 'f':
                    elem = new meaningful_board_element(meaningful_type::FLAG, pos);
                    break;
                case 'i':
                    elem = new meaningful_board_element(meaningful_type::IS, pos);
                    break;
                case 'b':
                    elem = new meaningful_board_element(meaningful_type::BABA, pos);
                    break;
                case 'r':
                    elem = new meaningful_board_element(meaningful_type::ROCK, pos);
                    break;
                case 'y':
                    elem = new meaningful_board_element(meaningful_type::YOU, pos);
                    break;
                case 's':
                    elem = new meaningful_board_element(meaningful_type::STOP, pos);
                    break;
                case 'w':
                    elem = new meaningful_board_element(meaningful_type::WIN, pos);
                    break;
                case 'p':
                    elem = new meaningful_board_element(meaningful_type::PUSH, pos);
                    break;
                case 'a':
                    elem = new meaningful_board_element(meaningful_type::WALL, pos);
                    break;
                    // attention : 'a' pour wall car 'w' est pris par win
                
                case '.':
                default:
                    break; 
            }

            if (elem != nullptr) {
                board.add_element(x, y, elem);
            }
        }
    }

    return board;
} 




Model::Model(const string& level_file_path) : board(load_level_from_file(level_file_path))
{
    compute_rules();
}

void Model::compute_rules()
{
    rules.reset_all();

    const vector<vector<meaningful_board_element*>> words = board.get_words();

    for (const vector<meaningful_board_element*>& row : words) {
        const size_t row_size = row.size();
        for (size_t i = 0; i + 2 < row_size; ++i) {
            meaningful_type word1 = row[i]->get_type();
            meaningful_type word2 = row[i + 1]->get_type();
            meaningful_type word3 = row[i + 2]->get_type();

            rules.new_rule(word1, word2, word3);
        }
    }
}

void Model::move(char direction/* TO DO direction ? */)
{

    vector<physical_type> you = rules.get_you_objets(); // renvoie les objets movables;

    for (int x = 0; x < board.dimensions[0]; ++x) {
        for (int y = 0; y < board.dimensions[1]; ++y) {
            // parcours du board
            for (Board_elements* elem : board.current_config[x][y]) {
                physical_board_element* phys_elem = dynamic_cast<physical_board_element*>(elem);
                if (phys_elem != nullptr) {
                    physical_type type = phys_elem->get_type();
                    if (find(you.begin(), you.end(), type) != you.end()) {
                        // on a un élément de type YOU
                        vector<Board_elements*> rangee; 
                        // on empile les éléments en partant de la fin vers où on veux aller
                        switch (direction) {
                            
                            case 'L':
                                for (int d = 0; d < y; ++d) {
                                    for (Board_elements* belem : board.current_config[x][d]) {
                                        rangee.push_back(belem);
                                }
                                }
                                break;
                            case 'R':
                                for (int d = y; d < board.dimensions[0]; ++d) {
                                    for (Board_elements* belem : board.current_config[x][d]) {
                                        rangee.push_back(belem);
                                }
                                }
                                break;
                            case 'U':
                                for (int d = 0; d < x; ++d) {
                                    for (Board_elements* belem : board.current_config[d][y]) {
                                        rangee.push_back(belem);
                                }
                                }
                                break;
                            case 'D':
                                for (int d = x; d < board.dimensions[1]; ++d) {
                                    for (Board_elements* belem : board.current_config[d][y]) {
                                        rangee.push_back(belem);
                                }
                                }
                                break;
                            default:
                                break;
                        }

                        // on a la pile des éléments à déplacer

                         /* on découle la pile en retirant (c'est plutot une file) 
                            en partant de l'élément you, à partir du moment où on a un truc
                            du style pas movable, pas stop (ou vide)

                            on vire tout le reste.  

                        */

                        bool dead = false;
                        for (int k = rangee.size() - 1; k >= 0; --k)
                        {
                            Board_elements* belem = rangee[k];
                            physical_board_element* pbelem = dynamic_cast<physical_board_element*>(belem);
                            if (pbelem != nullptr) {
                                physical_type ptype = pbelem->get_type();
                                if (rules[ptype].is_stop == true) {
                                    dead = true;
                                    break;
                                }

                                if (ptype == physical_type::EMPTY || (rules[ptype].is_push == false && rules[ptype].is_stop == false)) { 
                                    rangee.erase(rangee.begin(), rangee.begin() + k + 1);
                                    break;
                                }
                        }
                        }

                        if (!dead) {
                             // maintenant on a la pile à déplacer
                            for (Board_elements* belem : rangee) {
                                switch (direction) {
                                    case 'L': {
                                        vector<int> pos = belem->get_position();
                                        pos[1] -= 1;
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'R': {
                                        vector<int> pos = belem->get_position();
                                        pos[1] += 1;
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'U': {
                                        vector<int> pos = belem->get_position();
                                        pos[0] -= 1;
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'D': {
                                        vector<int> pos = belem->get_position();
                                        pos[0] += 1;
                                        belem->set_position(pos);
                                        break;
                                    }
                                    default:
                                        break;
                                }
                        }

                       
                        
                                                        

                            



                        
                            
                            } 

                        }

                        

                       

                    }
                }
            }
        }
    
   // TO DO
   /*
   1- faire un push ou un move
        a) récupérer les éléments YOU
        b) pour chacun d'eux, essayer de le déplacer dans la direction voulue
            i) faire une pile
        c) si c'est possbile, move
   2- si un meaningful_type a bougé, recompute_rules
    3- controller->is_notified(*this);
   */

   compute_rules();
   //controller->is_notified(*this);
}