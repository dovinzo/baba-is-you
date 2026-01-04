#ifndef MODEL_HPP
#define MODEL_HPP

#include "Board.hpp"
#include "Rules.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
#include "BoardHistory.hpp"
#include "Subject.hpp"
#include <vector>
#include <set>

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

        Model(int level);

        bool checkWin() const;

        // supprime les éléments qui doivent disappear
        void sink() ;

        bool undo();
        bool redo();

    /**
         * @brief Essaie de déplacer vers  les éléments du board constituant le joueur.
         */
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        /**
         * @brief Table d'association entre le boardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::OBJECT et le RuleSubject associé :
         *            BoardElementType::BABA -> RuleSubject::BABA
         *            BoardElementType::WALL -> RuleSubject::WALL
         *            BoardElementType::FLAG -> RuleSubject::FLAG
         *            BoardElementType::ROCK -> RuleSubject::ROCK
         *
         * @param boardElementType
         *        Le BoardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::OBJECT.
         */
        static RuleSubject ObjectToRuleSubject(BoardElementType boardElementType);

        /**
         * @brief Table d'association entre le boardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::TEXT_PROPERTY et le RuleProperty associé :
         *            BoardElementType::TEXT_BABA -> RuleProperty::BABA
         *            BoardElementType::TEXT_WALL -> RuleProperty::WALL
         *            BoardElementType::TEXT_FLAG -> RuleProperty::FLAG
         *            BoardElementType::TEXT_ROCK -> RuleProperty::ROCK
         *            BoardElementType::TEXT_PUSH -> RuleProperty::PUSH
         *            BoardElementType::TEXT_YOU -> RuleProperty::YOU
         *            BoardElementType::TEXT_STOP -> RuleProperty::STOP
         *            BoardElementType::TEXT_WIN -> RuleProperty::WIN
         *
         * @param boardElementType
         *        Le BoardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::TEXT_PROPERTY.
         */
        static RuleProperty TextPropertyToRuleProperty(BoardElementType boardElementType);

        /**
         * @brief Table d'association entre le boardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::TEXT_OBJECT et le RuleSubject associé :
         *            BoardElementType::TEXT_BABA -> RuleSubject::BABA
         *            BoardElementType::TEXT_WALL -> RuleSubject::WALL
         *            BoardElementType::TEXT_FLAG -> RuleSubject::FLAG
         *            BoardElementType::TEXT_ROCK -> RuleSubject::ROCK
         *
         * @param boardElementType
         *        Le BoardElementType d'un BoardElement appartenant à
         *        la catégorie BoardElementCategory::TEXT_OBJECT.
         */
        static RuleSubject TextObjectToRuleSubject(BoardElementType boardElementType);

        bool boardElementHasProperty(BoardElement& boardElement, RuleProperty ruleProperty) const;

        /**
         * @brief Récupère tous les éléments du board qui ont la propriété ruleProperty.
         *
         * @param ruleProperty
         *        La propriété en question.
         */
        std::vector<BoardElement*> getBoardElements(RuleProperty ruleProperty);

        /**
         * @brief Met à jour la règle codée horizontalement et commençant sur la case (x, y), si elle existe.
         *
         * @param x
         *        Entier compris entre 0 et board.getWidth() inclus.
         * @param y
         *        Entier compris entre 0 et board.getHeight() inclus.
         */


        /**
         * @brief Renvoie vrai si la case (x, y) est libre, sinon faux.
         *        Une case est libre si :
         *            - tous les éléments se trouvant sur cette case ne possèdent pas la propriété STOP ;
         *            - tous les éléments se trouvant sur cette case ne possèdent pas la propriété PUSH.
         *
         * @param x
         *        Entier compris entre 0 et board.getWidth() inclus.
         * @param y
         *        Entier compris entre 0 et board.getHeight() inclus.
         */
        bool isCellFree(int x, int y) const;

        
        void updateRules();
        void updateHorizontalRuleFromCell(int x, int y);
        void updateVerticalRuleFromCell(int x, int y);

        /**
         * @brief Essaie de pousser vers le haut les éléments de la case (x, y).
         *
         * @param x
         *        Entier compris entre 0 et board.getWidth() inclus.
         * @param y
         *        Entier compris entre 0 et board.getHeight() inclus.
         * @param visitedBoardElementsYou
         *        On y ajoutera les éléments constituant le joueur qui ont dû
         *        se déplacer vers le haut pour pouvoir pousser vers le haut les
         *        éléments de la case (x, y).
         */
        void tryPushUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryPushDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryPushLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryPushRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);


        /**
         * @brief Essaie de déplacer vers le haut les éléments de la case (x, y) constituant le joueur.
         *
         * @param x
         *        Entier compris entre 0 et board.getWidth() inclus.
         * @param y
         *        Entier compris entre 0 et board.getHeight() inclus.
         * @param visitedBoardElementsYou
         *        On y ajoutera les éléments constituant le joueur qui ont dû
         *        se déplacer vers le haut pour pouvoir déplacer vers le haut les
         *        éléments de la case (x, y) constituant le joueur.
         */
        void tryMoveUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryMoveDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryMoveLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        void tryMoveRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou);

        Board board;

        Rules rules;

        BoardHistory boardHistory;
};

#endif
