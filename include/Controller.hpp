#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"
#include "App.hpp"

class Controller
{
    public:
        Controller() = delete;
        Controller(App& app, Model& model);
        void handleEvent();
    private:
        App& app;
        Model& model;
};

#endif
