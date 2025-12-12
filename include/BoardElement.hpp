#ifndef BOARDELEMENT_HPP
#define BOARDELEMENT_HPP

#include "Enums.hpp"
#include "Rules.hpp"

class BoardElement
{
    public:
        BoardElement() = delete;
        BoardElement(BoardElementType type, int x, int y);
        BoardElementCategory getCategory() const;
        BoardElementType getType() const;
        static BoardElementType intToBoardElementType(int typeCode);
        //void setPosition(int i, int j);
        int getPositionX() const;
        int getPositionY() const;
        void setPositionX(int x);
        void setPositionY(int y);
        bool hasProperty(RuleProperty ruleProperty, Rules& rules) const;
        //int findPositionI() const;
        //int findPositionJ() const;
    private:
        //static int idCounter;
        //const int id; Son adresse est déjà un id
        BoardElementType type;
        int x;
        int y;
        //const Board& board;
};

#endif
