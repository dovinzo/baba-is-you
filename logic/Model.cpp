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
                case 'PW':
                    elem = new physical_board_element(physical_type::WALL, pos);
                    break;
                case 'PB':
                    elem = new physical_board_element(physical_type::BABA, pos);
                    break;
                case 'PF':
                    elem = new physical_board_element(physical_type::FLAG, pos);
                    break;
                case 'PR':
                    elem = new physical_board_element(physical_type::ROCK, pos);
                    break;

                // P c'est pour physical, donc PW correspond à un mur physique

                case 'WF':
                    elem = new meaningful_board_element(meaningful_type::FLAG, pos);
                    break;
                case 'WI':
                    elem = new meaningful_board_element(meaningful_type::IS, pos);
                    break;
                case 'WB':
                    elem = new meaningful_board_element(meaningful_type::BABA, pos);
                    break;
                case 'WR':
                    elem = new meaningful_board_element(meaningful_type::ROCK, pos);
                    break;
                case 'WY':
                    elem = new meaningful_board_element(meaningful_type::YOU, pos);
                    break;
                case 'WS':
                    elem = new meaningful_board_element(meaningful_type::STOP, pos);
                    break;
                case 'WW':
                    elem = new meaningful_board_element(meaningful_type::WIN, pos);
                    break;
                case 'WP':
                    elem = new meaningful_board_element(meaningful_type::PUSH, pos);
                    break;
                case 'WA':
                    elem = new meaningful_board_element(meaningful_type::WALL, pos);
                    break;


                
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
    send_new_state_to_controller();
}

void Model::compute_rules()
{
    // on parcours tout le board, et on observe les meaningful elements
    // on en récupère les 3 mots, et on appelle Rules::add_rule
    // on vide les règles avant de commencer
}