#ifndef LOGIC_RULES_HPP
#define LOGIC_RULES_HPP

#include "Enums.hpp"
#include <map>
using namespace std;




struct Property
{
    bool is_you  = false;
    bool is_push = false;
    bool is_stop = false;
    bool is_win  = false;

    bool is(property_type p) const {
        switch (p) {
            case property_type::YOU:  return is_you;
            case property_type::PUSH: return is_push;
            case property_type::STOP: return is_stop;
            case property_type::WIN:  return is_win;
        }
        return false;
    }
};


class Rules
{
private:

    // ici que sont stockées les règles pour chaque type

    // physical props c'est pour les types physiques : "pour tout type physique, pour toute propriété, true or false ?"
    map<physical_type, Property> physical_props;

    // meaningful props c'est pour les mots, c'est const : un mot est pushable toujours, mais jamais win par exemple. 
    const map<meaningful_type, Property> meaningful_props = {
        {meaningful_type::YOU, Property{false, true, false, false}},
        {meaningful_type::PUSH, Property{false, true, false, false}},
        {meaningful_type::IS, Property{false, true, false, false}},
        {meaningful_type::FLAG, Property{false, true, false, false}},
        {meaningful_type::BABA, Property{false, true, false, false}},
        {meaningful_type::ROCK, Property{false, true, false, false}}
    };

    // c'est moche 
    
public:
    Rules( map<physical_type, Property> initial_physical_props); // TO DO : faut que ça soit secure, qu'on puisse qu'en créer un. 
    ~Rules();


    // objectif : pouvoir faire rules[physical_type::BABA].is_push pour savoir si BABA est pushable.
    const Property& operator[](physical_type type) const; // 
    // utilisation : rules[physical_type::WALL].is(push);
    // renvoie true or false selon que WALL est pushable ou pas.
 


};


#endif // LOGIC_RULES_HPP
