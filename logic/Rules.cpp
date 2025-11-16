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

Rules::Rules( map<physical_type, Property> initial_physical_props): physical_props(initial_physical_props) {}; 