#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "Enums.hpp"

class App; 
class MenuController;

class MenuModel
{
    friend class App;
    friend class MenuController;   

    
    public:
        MenuItem getMenuItem() const;

        
    private:
        MenuModel();
        void next();
        void previous();
        MenuItem item;
};

#endif
