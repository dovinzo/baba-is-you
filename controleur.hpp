
//#include "logic/model.hpp"
//#include "logic/vue.hpp"

// TO DO le src 

class Model;
class Vue;

class controleur
{
private:
    Model* modele;
    Vue* vue;

public:
    controleur();
    // 

    void pull_input(/* touche clavier */);
    // enum toucne clavier ?
    // modele->move(direction);
    
    void is_notified(Model& modele);
    // view->update(modele);

    ~controleur();
};


/* 

TODO : 

recuper l'input de la part de la vue, traduire en terme d'action à effectuer  
l'envoyer à la logique

récupérer le modèle mis à jour de la logique

le traduire pour la vue
l'envoyer à la vue

*/