#ifndef APP_HPP
#define APP_HPP

#include "MenuModel.hpp"
#include "MenuView.hpp"
#include "MenuController.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "Observer.hpp"
#include "Notification.hpp"
#include "Victory.hpp"
#include "Quit.hpp"
#include <SFML/Graphics.hpp>

class App : public Observer
{
public:
    App();
    /* Construit l'App : fenêtre graphique se met dans l'état menu,
    crée le MVC du menu en liant entre eux les trois éléments */
    ~App(); // détruit le model ou le niveau en fonction de l'état du jeu.

    void run(); // lance la boucle principale du jeu.
    void update(const Notification &notification) override;
    /* met à jour l'app selon la notification reçue. e.g se
    met dans l'état QUIT si notification Quit reçue. */

private:
    void updateFromVictory();                // met à jour l'état de l'application post victoire.
    void updateFromQuit();                   // met à jour l'état de l'application post quit.
    void changeState(AppState nextAppState); // met l'application dans l'état nextApp
    void initMenu();                         // initialise le menu, et détruit le niveau si besoin.
    void processMenu();                      // boucle de traitement du menu.
    void initLevel();                        // initialise le niveau, et détruit le menu si besoin.
    void processLevel();                     // boucle de traitement du niveau.

private:
    sf::RenderWindow *window;

    AppState appState;

    MenuModel *menuModel;
    MenuView *menuView;
    MenuController *menuController;

    Model *levelModel;
    View *levelView;
    Controller *levelController;
};

#endif
