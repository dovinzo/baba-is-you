#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Model.hpp"

int main() {
    cout << " before model \n";
    int level = 1;
    

    string path = "1.txt";

    Model model(path);
    cout << " after model \n";

    // le modele créer son board et initialise les règles
    // puis les calcules. 


    char input;
    while (true)
    {
        // Efface le terminal
        cout << "\033[2J\033[1;1H";

        cout << "=== Niveau " << level << " ===\n";
        cout <<" avant render \n";
                const vector<string> board_lines = model.render_board();
        for (size_t i = 0; i < board_lines.size(); ++i) {
            cout << board_lines[i] << '\n';
        }

        // Affiche les mots trouvés (ex: biy, fip, ...)
        cout << "\n \n \n ";

        const vector<string> triples = model.get_word_triples();
        for (size_t i = 0; i < triples.size(); ++i) {
            cout << triples[i] << '\n';
        }

        cout << "\nCommande (z q s d), x pour quitter : ";
        cin >> input;


        if (input == 'x')
            break;

        char direction = '\0';
        switch (input) {
            case 'q': direction = 'L'; break;
            case 'd': direction = 'R'; break;
            case 'z': direction = 'U'; break;
            case 's': direction = 'D'; break;
            default:
                cout << "Commande inconnue.\n";
                continue;
        }

        model.move(direction);
    }
    
    return 0;
}
