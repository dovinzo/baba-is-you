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

Board load_level_from_file(const string& path)
{
    vector<string> lines = load_level_ascii(path);
    if (lines.empty()) {
        throw runtime_error("Fichier de niveau vide: " + path);
    }

    int height = static_cast<int>(lines.size());
    int width  = static_cast<int>(lines[0].size());

    Board board(width, height);

    for (int y = 0; y < height; ++y) {
        const string& row = lines[y];
        for (int x = 0; x < width; ++x) {
            char c = row[x];

            // position (x, y, z), z = 0 au début
            vector<int> pos = {x, y, 0};

            Board_elements* elem = nullptr;

            switch (c) {
                case '#':
                    elem = new physical_board_element(physical_type::WALL, pos);
                    break;
                case 'B':
                    elem = new physical_board_element(physical_type::BABA, pos);
                    break;
                case 'F':
                    elem = new physical_board_element(physical_type::FLAG, pos);
                    break;
                case 'P':
                    elem = new meaningful_board_element(meaningful_type::FLAG, pos);
                    break;
                case '.':
                default:
                    break; // case vide ou caractère inconnu → on ne crée rien
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
