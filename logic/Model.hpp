#ifndef LOGIC_MODEL_HPP
#define LOGIC_MODEL_HPP


#include "Rules.hpp"
#include "Board.hpp"

#include "Board_elements.hpp"
// besoin de Board_elements pour construire le board à partir d'un fichier de niveau
// c'est ok ? 


class Model
{
private:
    Board board;
    Rules rules;
    // c'est fort : le model contient le board et les rules.
    // c'est surement là que va se jouer l'initialisation du niveau
    
    void compute_rules();
    void move(); // un push est un move

    void send_new_state_to_controller(); // après chaque move, on envoie l'état du board et des règles au controller pour affichage

    Board load_level_from_file(const string& path); // fonction utilitaire pour charger un niveau à partir d'un fichier ASCII   
    // déclarée ici parce que comme c'est une fonction de board, 
    // elle à accès aux membres privés de board (genre add_element) car friend 

    void compute_rules();

public:
    Model(const string& level_file_path); // on initialise le model avec un fichier de niveau
    ~Model(); // TO DO  


};

#endif // LOGIC_MODEL_HPP

/* 
le modèle doit : 
A) au début de la partie
- construire le board (via un loader de niveau) 
    c'est à dire sa dimension et ses éléments.
- initilaiser les règles d'après ce board

DONE 


B) pendant la partie
- récupérer l'input via le contrôleur
- faire bouger les objets controlables (si possible)
- si push, faire bouger les objets pushables
- si un objet meaningful_type à été bougé :
    - recalculer les règles
        - mettre à jour les règles dans Rules
    - vérifier les conditions de victoire/défaite
- renvoyer l'état du board et des règles au controleur pour affichage 
*/