#ifndef LOGIC_MODEL_HPP
#define LOGIC_MODEL_HPP


#include "Rules.hpp"
#include "Board.hpp"


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
    


public:
    Model(/* constuit le board, et calcule les règles pour chaque niveau */);
    ~Model();

    void compute_rules();

};

#endif // LOGIC_MODEL_HPP

/* 
le modèle doit : 
A) au début de la partie
- construire le board (via un loader de niveau)
- initilaiser les règles d'après ce board


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