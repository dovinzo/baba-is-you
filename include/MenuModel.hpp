#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "Enums.hpp"
#include "App.hpp"

class MenuModel
{
    public:
        MenuModel();
        void next();
        void previous();
        MenuItem getMenuItem() const;
    private:
        MenuItem item;
};

#endif