#include <fstream>
#include <stdexcept>
#include <algorithm>
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

    vector<int> dimensions = {width, height, 1}; // z dimension = 1 au début
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
                case ' ':
                    elem = new physical_board_element(physical_type::EMPTY, pos);
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




Model::Model(const string& level_file_path) : rules(), board(load_level_from_file(level_file_path))
{

    compute_rules();
}

Model::~Model() = default;

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
/*
void Model::move(char direction/* TO DO direction ? )
{

    cout << "MOVE called with direction " << direction << "\n";


    vector<physical_type> you = rules.get_you_objets(); // renvoie les objets movables;
    cout << "YOU objects count = " << you.size() << "\n";


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
                            for (int d = y; d < board.dimensions[1]; ++d) { // height
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
                            for (int d = x; d < board.dimensions[0]; ++d) { // width
                                for (Board_elements* belem : board.current_config[d][y]) {
                                    rangee.push_back(belem);
                                }
                            }
                            break;

                        }

                        // on a la pile des éléments à déplacer

                         /* on découle la pile en retirant (c'est plutot une file) 
                            en partant de l'élément you, à partir du moment où on a un truc
                            du style pas movable, pas stop (ou vide)

                            on vire tout le reste.  

                        

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
                                        pos[0] -= 1; // x--
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'R': {
                                        vector<int> pos = belem->get_position();
                                        pos[0] += 1; // x++
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'U': {
                                        vector<int> pos = belem->get_position();
                                        pos[1] -= 1; // y--
                                        belem->set_position(pos);
                                        break;
                                    }
                                    case 'D': {
                                        vector<int> pos = belem->get_position();
                                        pos[1] += 1; // y++
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
   
    board.rebuild_from_positions();
    compute_rules();

   //controller->is_notified(*this);
}

*/

void Model::move(char direction)
{
    vector<physical_type> you = rules.get_you_objets();
    if (you.empty()) {
        return;
    }

    int step_x = 0;
    int step_y = 0;
    if (direction == 'L')      { step_x = -1; }
    else if (direction == 'R') { step_x = 1;  }
    else if (direction == 'U') { step_y = -1; }
    else if (direction == 'D') { step_y = 1;  }
    else { return; }

    int width  = board.dimensions.size() > 0 ? board.dimensions[0] : 0;
    int height = board.dimensions.size() > 1 ? board.dimensions[1] : 0;

    // Snapshot so we iterate over the original positions
    vector<vector<vector<Board_elements*> > > snapshot = board.current_config;
    set<Board_elements*> moved;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            vector<Board_elements*>& cell = snapshot[x][y];
            for (size_t idx = 0; idx < cell.size(); ++idx) {
                Board_elements* elem = cell[idx];
                if (moved.find(elem) != moved.end()) {
                    continue;
                }

                physical_board_element* phys_elem = dynamic_cast<physical_board_element*>(elem);
                if (phys_elem == 0) {
                    continue;
                }

                physical_type type = phys_elem->get_type();
                if (std::find(you.begin(), you.end(), type) == you.end()) {
                    continue; // not YOU
                }

                // Build the push chain in front of this YOU
                vector<Board_elements*> push_list;
                int tx = x + step_x;
                int ty = y + step_y;
                bool blocked = false;
                bool out_of_bounds = false;

                while (true) {
                    if (tx < 0 || tx >= width || ty < 0 || ty >= height) {
                        out_of_bounds = true;
                        break;
                    }

                vector<Board_elements*>& target_cell = board.current_config[tx][ty];
                bool has_pushable = false;

                for (size_t t = 0; t < target_cell.size(); ++t) {
                    Board_elements* t_elem = target_cell[t];

                    // Physical elements: STOP and/or PUSH per rules
                    physical_board_element* t_phys = dynamic_cast<physical_board_element*>(t_elem);
                    if (t_phys != 0) {
                        physical_type t_type = t_phys->get_type();
                        if (rules[t_type].is_stop && !rules[t_type].is_push) {
                            blocked = true;
                            break;
                        }
                        if (rules[t_type].is_push) {
                            has_pushable = true;
                            push_list.push_back(t_elem);
                        }
                        continue;
                    }

                    // Meaningful elements: treat as pushable by default
                    meaningful_board_element* t_word = dynamic_cast<meaningful_board_element*>(t_elem);
                    if (t_word != 0) {
                        has_pushable = true;
                        push_list.push_back(t_elem);
                    }
                }


                    if (blocked) {
                        break;
                    }

                    if (!has_pushable) {
                        break; // empty or only non-push, non-stop -> we can move
                    }

                    tx += step_x;
                    ty += step_y;
                }

                if (blocked || out_of_bounds) {
                    continue;
                }

                // Move pushables from farthest to nearest
                for (int p = static_cast<int>(push_list.size()) - 1; p >= 0; --p) {
                    Board_elements* p_elem = push_list[p];
                    vector<int> p_pos = p_elem->get_position();
                    if (p_pos.size() < 2) {
                        continue;
                    }
                    p_pos[0] += step_x;
                    p_pos[1] += step_y;
                    p_elem->set_position(p_pos);
                    moved.insert(p_elem);
                }

                // Move the YOU element
                vector<int> pos = elem->get_position();
                if (pos.size() >= 2) {
                    pos[0] += step_x;
                    pos[1] += step_y;
                    elem->set_position(pos);
                    moved.insert(elem);
                }
            }
        }
    }

    board.rebuild_from_positions();
    compute_rules();
}


vector<string> Model::render_board() const
{
    int width  = board.dimensions.size() > 0 ? board.dimensions[0] : 0;
    int height = board.dimensions.size() > 1 ? board.dimensions[1] : 0;

    vector<string> output(static_cast<size_t>(height), string(static_cast<size_t>(width), '.'));

    // simple priority: higher wins
    // 0 = empty, 1 = words, 2 = walls/rocks/flag, 3 = YOU/BABA
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int best_priority = 0;
            char best_symbol = '.';
            const vector<Board_elements*>& cell = board.current_config[x][y];
            for (size_t k = 0; k < cell.size(); ++k) {
                const Board_elements* elem = cell[k];
                char symbol = '.';
                int prio = 0;

                const physical_board_element* physical = dynamic_cast<const physical_board_element*>(elem);
                if (physical != 0) {
                    switch (physical->get_type()) {
                        case physical_type::WALL:  symbol = '#'; prio = 2; break;
                        case physical_type::BABA:  symbol = 'B'; prio = 3; break;
                        case physical_type::FLAG:  symbol = 'F'; prio = 2; break;
                        case physical_type::ROCK:  symbol = 'R'; prio = 2; break;
                        case physical_type::EMPTY: symbol = '.'; prio = 0; break;
                    }
                } else {
                    const meaningful_board_element* word = dynamic_cast<const meaningful_board_element*>(elem);
                    if (word != 0) {
                        prio = 1;
                        switch (word->get_type()) {
                            case meaningful_type::FLAG: symbol = 'f'; break;
                            case meaningful_type::IS:   symbol = 'i'; break;
                            case meaningful_type::BABA: symbol = 'b'; break;
                            case meaningful_type::ROCK: symbol = 'r'; break;
                            case meaningful_type::PUSH: symbol = 'p'; break;
                            case meaningful_type::YOU:  symbol = 'y'; break;
                            case meaningful_type::WALL: symbol = 'a'; break;
                            case meaningful_type::STOP: symbol = 's'; break;
                            case meaningful_type::WIN:  symbol = 'w'; break;
                            case meaningful_type::COUNT:symbol = '?'; break;
                        }
                    }
                }

                if (prio > best_priority && symbol != '.') {
                    best_priority = prio;
                    best_symbol = symbol;
                }
            }

            output[static_cast<size_t>(y)][static_cast<size_t>(x)] = best_symbol;
        }
    }

    return output;
}


vector<string> Model::get_word_triples()
{
    vector<string> result;

    vector<vector<meaningful_board_element*> > sentences = board.get_words();

    for (size_t i = 0; i < sentences.size(); ++i) {
        const vector<meaningful_board_element*>& sentence = sentences[i];
        if (sentence.size() != 3) {
            continue;
        }

        string s;
        s.push_back(meaningful_char(sentence[0]->get_type()));
        s.push_back(meaningful_char(sentence[1]->get_type()));
        s.push_back(meaningful_char(sentence[2]->get_type()));

        result.push_back(s);
    }

    return result;
}
