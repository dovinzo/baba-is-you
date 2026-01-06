#ifndef MODEL_HPP
#define MODEL_HPP

#include "Board.hpp"
#include "Rules.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
#include "BoardHistory.hpp"
#include "Subject.hpp"
#include "Victory.hpp"
#include <vector>
#include <set>

/* Le Model gère toute la logique du jeu. Il reçoit du Controller les inputs de l'utilisateur. 
C'est la "tête pensante" qui connait temps les règles que l'état du board à tout instant.  */
class Controller;

class Model: public Subject
{
    public:

        Model() = delete;
        ~Model() = default;
        Model& operator=(const Model& model) = delete;
        Model(const Model& model) = delete;

        int getBoardWidth() const;
        int getBoardHeight() const;
        std::vector<BoardElement*> getBoardCell(int x, int y) const;

        friend class Controller;
        friend class App;

    private:
        Board board;
        Rules rules;
        BoardHistory boardHistory;

        explicit Model(int level); // uniquement possible par l'App

        // vérifie si les conditions de victoire sont remplies par un parcours du Board au vu des Rules
        bool checkWin() const;
        void sink() ;

        // gestion de l'historique des déplacements pour undo/redo
        bool undo();
        bool redo();

        // tentative de déplacement dans une des 4 directions
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        void tryPushUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryPushDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryPushLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryPushRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryMoveUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryMoveDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryMoveLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);
        void tryMoveRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        /* Traductions (cf. Rules.hpp et Enums.hpp)*/
        // Table de traduction entre le boardElementType d'un BoardElement et ObjectToRuleSubject
        // e.g BoardElementType::ROCK -> RuleSubject::ROCK 
        static RuleSubject ObjectToRuleSubject(BoardElementType boardElementType);

        // Traduction : e.g BoardElementType::TEXT_WALL -> RuleProperty::WALL
        static RuleProperty TextPropertyToRuleProperty(BoardElementType boardElementType);

        // E.g BoardElementType::TEXT_BABA -> RuleSubject::BABA
        static RuleSubject TextObjectToRuleSubject(BoardElementType boardElementType);


        // vérifie si un BoardElement possède une RuleProperty donnée au vu des Rules courantes
        bool boardElementHasProperty(BoardElement& boardElement, RuleProperty ruleProperty) const;

        // renvoie tous les BoardElement possédant une RuleProperty donnée au vu des Rules courantes
        std::vector<BoardElement*> getBoardElements(RuleProperty ruleProperty);
   
        bool isCellFree(int x, int y) const;

        // met à jour les règles en fonction des TextElements présents sur le Board
        void updateRules();
        void updateHorizontalRuleFromCell(int x, int y);
        void updateVerticalRuleFromCell(int x, int y);

};

#endif
