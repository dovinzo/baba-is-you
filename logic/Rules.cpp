#include "Rules.hpp"

const Property& Rules::operator[](physical_type type) const
{
    static const Property default_property{};  // tout à false
    map<physical_type, Property>::const_iterator it = physical_props.find(type);
    // const_iterator car la méthode est const 
    
    if (it != physical_props.end()) {
        return it->second;
    } else {
        return default_property;
    } 
    
}


static Property make_push_only()
{
    Property p;        // tous les bool à false par défaut
    p.is_push = true;  // seul push = true
    return p;
} 



Rules::Rules( map<physical_type, Property> initial_physical_props): physical_props(initial_physical_props) {

    const Property push_only = make_push_only();

    for (std::size_t i = 0;
         i < static_cast<size_t>(meaningful_type::COUNT);
         ++i)
    {
        meaningful_type t = static_cast<meaningful_type>(i);
        meaningful_props[t] = push_only;
    } 
}; 

void Rules::reset_all()
{
    map<physical_type, Property>::iterator it;
    for (it = physical_props.begin(); it != physical_props.end(); it++) {
        it->second = Property{}; // réinitialise toutes les propriétés à false
    }


}

Property& Rules::access(physical_type type)
{
    return physical_props[type];
} 


 

// treaducteur de meaningful_type vers physical_type 
static bool to_physical(meaningful_type word, physical_type& out)
{
    switch (word) {
    case meaningful_type::BABA: out = physical_type::BABA; return true;
    case meaningful_type::FLAG: out = physical_type::FLAG; return true;
    case meaningful_type::ROCK: out = physical_type::ROCK; return true;
    case meaningful_type::WALL: out = physical_type::WALL; return true;
    default: return false;
    }
}

// traducteur de meaningful_type vers property_type
static bool to_property(meaningful_type word, property_type& out)
{
    switch (word) {
    case meaningful_type::YOU:  out = property_type::YOU;  return true;
    case meaningful_type::PUSH: out = property_type::PUSH; return true;
    case meaningful_type::STOP: out = property_type::STOP; return true;
    case meaningful_type::WIN:  out = property_type::WIN;  return true;
    default: return false;
    }
}
 

// a ce stade, on gère juste les règles de la forme "X IS Y" où X est dans 
// physical_type et Y dans property_type
void Rules::new_rule(meaningful_type word1,
                     meaningful_type word2,
                     meaningful_type word3)
{
    if (word2 != meaningful_type::IS) {
        return; // on ne gère que "X IS Y"
    }

    physical_type  phys;
    property_type  prop;

    if (!to_physical(word1, phys)) {
        return; // word1 n'est pas un type physique connu
    }
    if (!to_property(word3, prop)) {
        return; // word3 n'est pas une propriété connue
    }

    // on a maintenant un type physique et une propriété -> on l’active
    Property& p = access(phys);
    switch (prop) {
    case property_type::YOU:  p.is_you  = true; break;
    case property_type::PUSH: p.is_push = true; break;
    case property_type::STOP: p.is_stop = true; break;
    case property_type::WIN:  p.is_win  = true; break;
    }
}

vector<physical_type> Rules::get_you_objets()
{
    vector<physical_type> you_objects;
    set<physical_type> seen;

    for (map<physical_type, Property>::const_iterator it = physical_props.begin(); it != physical_props.end(); ++it) {
        physical_type type = it->first;
        const Property& prop = it->second;

        if (prop.is_you && seen.find(type) == seen.end()) {
            you_objects.push_back(type);
            seen.insert(type);
        }
    }

    return you_objects;
}