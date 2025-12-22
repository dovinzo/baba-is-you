#include "MenuModel.hpp"
#include "Enums.hpp"

MenuModel::MenuModel(): item{MenuItem::LEVEL1}
{
}

void MenuModel::next()
{
    switch (item)
    {
        case MenuItem::LEVEL1:
            item = MenuItem::LEVEL2;
            break;
        case MenuItem::LEVEL2:
            item = MenuItem::LEVEL3;
            break;
        case MenuItem::LEVEL3:
            item = MenuItem::LEVEL1;
            break;
    }
}

void MenuModel::previous()
{
    switch (item)
    {
        case MenuItem::LEVEL1:
            item = MenuItem::LEVEL3;
            break;
        case MenuItem::LEVEL2:
            item = MenuItem::LEVEL1;
            break;
        case MenuItem::LEVEL3:
            item = MenuItem::LEVEL2;
            break;
    }
}

MenuItem MenuModel::getMenuItem() const
{
    return item;
}