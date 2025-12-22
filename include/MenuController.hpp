#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "App.hpp"
#include "MenuModel.hpp"
#include "MenuView.hpp"

class MenuController
{
    public:
        MenuController() = delete;
        MenuController(App& app, MenuModel& model, MenuView& view);
        void handleEvent();
        void selectLevel();
    private:
        App& app;
        MenuModel& model;
        MenuView& view;
};

#endif
