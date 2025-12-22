#include "Model.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

Model::Model(int level): board{level}, rules{}
{
    this->updateRules();
}

void Model::moveUp()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveUp(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
        this->updateRules();
}

void Model::moveDown()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveDown(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
        this->updateRules();
}

void Model::moveLeft()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveLeft(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
        this->updateRules();
}

void Model::moveRight()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveRight(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
        this->updateRules();
}

bool Model::checkWin() const
{
    bool hasYou{false}, hasWin{false};
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            hasYou = false;
            hasWin = false;
            for (int i = 0 ; i < static_cast<int>(board.grid[x][y].size()) ; i++)
            {
                if (this->boardElementHasProperty(*(board.grid[x][y][i]), RuleProperty::YOU))
                    hasYou = true;
                if (this->boardElementHasProperty(*(board.grid[x][y][i]), RuleProperty::WIN))
                    hasWin = true;
            }
            if (hasYou and hasWin)
                return true;
        }
    }
    return false;
}

std::vector<BoardElement*> Model::getBoardElements(RuleProperty ruleProperty)
{
    std::vector<BoardElement*> boardElements;
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            for (int i = 0 ; i < static_cast<int>(board.grid[x][y].size()) ; i++)
            {
                if (this->boardElementHasProperty(*(board.grid[x][y][i]), ruleProperty))
                {
                    boardElements.push_back(board.grid[x][y][i]);
                }
            }
        }
    }
    return boardElements;
}

void Model::updateRules()
{
    rules.clearRules();
    for (int x = 0 ; x < board.getWidth() - 2 ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            this->updateHorizontalRuleFromCell(x, y);
        }
    }
    for (int x = 0 ; x < board.getWidth(); x++)
    {
        for (int y = 0 ; y < board.getHeight() - 2 ; y++)
        {
            this->updateVerticalRuleFromCell(x, y);
        }
    }
}

RuleSubject Model::ObjectToRuleSubject(BoardElementType boardElementType)
{
    RuleSubject ruleSubject;
    switch (boardElementType)
    {
        case BoardElementType::BABA:
            ruleSubject = RuleSubject::BABA;
            break;
        case BoardElementType::WALL:
            ruleSubject = RuleSubject::WALL;
            break;
        case BoardElementType::FLAG:
            ruleSubject = RuleSubject::FLAG;
            break;
        case BoardElementType::ROCK:
            ruleSubject = RuleSubject::ROCK;
            break;
        default:
            break;
    }
    return ruleSubject;
}

RuleProperty Model::TextPropertyToRuleProperty(BoardElementType boardElementType)
{
    RuleProperty ruleProperty;
    switch (boardElementType)
    {
        case BoardElementType::TEXT_BABA:
            ruleProperty = RuleProperty::BABA;
            break;
        case BoardElementType::TEXT_WALL:
            ruleProperty = RuleProperty::WALL;
            break;
        case BoardElementType::TEXT_FLAG:
            ruleProperty = RuleProperty::FLAG;
            break;
        case BoardElementType::TEXT_ROCK:
            ruleProperty = RuleProperty::ROCK;
            break;
        case BoardElementType::TEXT_PUSH:
            ruleProperty = RuleProperty::PUSH;
            break;
        case BoardElementType::TEXT_YOU:
            ruleProperty = RuleProperty::YOU;
            break;
        case BoardElementType::TEXT_STOP:
            ruleProperty = RuleProperty::STOP;
            break;
        case BoardElementType::TEXT_WIN:
            ruleProperty = RuleProperty::WIN;
            break;
        default:
            break;
    }
    return ruleProperty;
}  

RuleSubject Model::TextObjectToRuleSubject(BoardElementType boardElementType)
{
    RuleSubject ruleSubject;
    switch (boardElementType)
    {
        case BoardElementType::TEXT_BABA:
            ruleSubject = RuleSubject::BABA;
            break;
        case BoardElementType::TEXT_WALL:
            ruleSubject = RuleSubject::WALL;
            break;
        case BoardElementType::TEXT_FLAG:
            ruleSubject = RuleSubject::FLAG;
            break;
        case BoardElementType::TEXT_ROCK:
            ruleSubject = RuleSubject::ROCK;
            break;
        default:
            break;
    }
    return ruleSubject;
}

// ENCOURS
bool Model::boardElementHasProperty(BoardElement& boardElement, RuleProperty ruleProperty) const
{
    RuleSubject ruleSubject;
    if (boardElement.getCategory() == BoardElementCategory::TEXT_OBJECT or boardElement.getCategory() == BoardElementCategory::TEXT_IS or boardElement.getCategory() == BoardElementCategory::TEXT_PROPERTY)
    {
        if (ruleProperty == RuleProperty::PUSH)
            return true;
        else
            return false;
    }
    else
    {
        ruleSubject = Model::ObjectToRuleSubject(boardElement.getType());
        return rules.haveRule(ruleSubject, ruleProperty);
    }
}

void Model::updateHorizontalRuleFromCell(int x, int y)
{
    RuleSubject ruleSubject;
    RuleProperty ruleProperty;
    for (int i = 0 ; i < static_cast<int>(board.grid[x][y].size()) ; i++)
    {
        if (board.grid[x][y][i]->getCategory() == BoardElementCategory::TEXT_OBJECT)
        {
            for (int j = 0 ; j < static_cast<int>(board.grid[x+1][y].size()) ; j++)
            {
                if (board.grid[x+1][y][j]->getCategory() == BoardElementCategory::TEXT_IS)
                {
                    for (int k = 0 ; k < static_cast<int>(board.grid[x+2][y].size()) ; k++)
                    {
                        if (board.grid[x+2][y][k]->getCategory() == BoardElementCategory::TEXT_PROPERTY)
                        {
                            ruleSubject = Model::TextObjectToRuleSubject(board.grid[x][y][i]->getType());
                            ruleProperty = Model::TextPropertyToRuleProperty(board.grid[x+2][y][k]->getType());
                            rules.setRule(ruleSubject, ruleProperty);
                        }
                    }
                }
            }
        }
    }
}

void Model::updateVerticalRuleFromCell(int x, int y)
{
    RuleSubject ruleSubject;
    RuleProperty ruleProperty;
    for (int i = 0 ; i < static_cast<int>(board.grid[x][y].size()) ; i++)
    {
        if (board.grid[x][y][i]->getCategory() == BoardElementCategory::TEXT_OBJECT)
        {
            for (int j = 0 ; j < static_cast<int>(board.grid[x][y+1].size()) ; j++)
            {
                if (board.grid[x][y+1][j]->getCategory() == BoardElementCategory::TEXT_IS)
                {
                    for (int k = 0 ; k < static_cast<int>(board.grid[x][y+2].size()) ; k++)
                    {
                        if (board.grid[x][y+2][k]->getCategory() == BoardElementCategory::TEXT_PROPERTY)
                        {
                            ruleSubject = Model::TextObjectToRuleSubject(board.grid[x][y][i]->getType());
                            ruleProperty = Model::TextPropertyToRuleProperty(board.grid[x][y+2][k]->getType());
                            rules.setRule(ruleSubject, ruleProperty);
                        }
                    }
                }
            }
        }
    }
}

bool Model::isCellFree(int x, int y)
{
    for (int i = 0 ; i < static_cast<int>(board.grid[x][y].size()) ; i++)
    {
        if (this->boardElementHasProperty(*(board.grid[x][y][i]), RuleProperty::STOP))
            return false;
        if (this->boardElementHasProperty(*(board.grid[x][y][i]), RuleProperty::PUSH))
            return false;
    }
    return true;
}

void Model::tryPushUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasStop{false}, hasYou{false}, hasPush{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::STOP))
            hasStop = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            hasPush = true;
    }
    if (hasStop or not hasPush or hasYou or y == 0)
        return;
    this->tryPushUp(x, y-1, visitedBoardElementsYou);
    this->tryMoveUp(x, y-1, visitedBoardElementsYou);
    if (not this->isCellFree(x, y-1))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            board.setNewPosition(cell[i], x, y-1);
    }
}


void Model::tryPushDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasStop{false}, hasYou{false}, hasPush{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::STOP))
            hasStop = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            hasPush = true;
    }
    if (hasStop or not hasPush or hasYou or y == board.getHeight() - 1)
        return;
    this->tryPushDown(x, y+1, visitedBoardElementsYou);
    this->tryMoveDown(x, y+1, visitedBoardElementsYou);
    if (not this->isCellFree(x, y+1))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            board.setNewPosition(cell[i], x, y+1);
    }
}

void Model::tryPushLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasStop{false}, hasYou{false}, hasPush{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::STOP))
            hasStop = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            hasPush = true;
    }
    if (hasStop or not hasPush or hasYou or x == 0)
        return;
    this->tryPushLeft(x-1, y, visitedBoardElementsYou);
    this->tryMoveLeft(x-1, y, visitedBoardElementsYou);
    if (not this->isCellFree(x-1, y))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            board.setNewPosition(cell[i], x-1, y);
    }
}

void Model::tryPushRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasStop{false}, hasYou{false}, hasPush{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::STOP))
            hasStop = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            hasPush = true;
    }
    if (hasStop or not hasPush or hasYou or x == board.getWidth() - 1)
        return;
    this->tryPushRight(x+1, y, visitedBoardElementsYou);
    this->tryMoveRight(x+1, y, visitedBoardElementsYou);
    if (not this->isCellFree(x+1, y))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
            board.setNewPosition(cell[i], x+1, y);
    }
}

void Model::tryMoveUp(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasYou{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
    }
    if (not hasYou or y == 0)
        return;
    this->tryPushUp(x, y-1, visitedBoardElementsYou);
    this->tryMoveUp(x, y-1, visitedBoardElementsYou);
    if (not this->isCellFree(x, y-1))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
        {
            board.setNewPosition(cell[i], x, y-1);
            visitedBoardElementsYou.insert(cell[i]);
        }
    }
}

void Model::tryMoveDown(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasYou{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
    }
    if (not hasYou or y == board.getHeight() - 1)
        return;
    this->tryPushDown(x, y+1, visitedBoardElementsYou);
    this->tryMoveDown(x, y+1, visitedBoardElementsYou);
    if (not this->isCellFree(x, y+1))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
        {
            board.setNewPosition(cell[i], x, y+1);
            visitedBoardElementsYou.insert(cell[i]);
        }
    }
}

void Model::tryMoveLeft(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasYou{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
    }
    if (not hasYou or x == 0)
        return;
    this->tryPushLeft(x-1, y, visitedBoardElementsYou);
    this->tryMoveLeft(x-1, y, visitedBoardElementsYou);
    if (not this->isCellFree(x-1, y))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
        {
            board.setNewPosition(cell[i], x-1, y);
            visitedBoardElementsYou.insert(cell[i]);
        }
    }
}

void Model::tryMoveRight(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou)
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    bool hasYou{false};
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
            hasYou = true;
    }
    if (not hasYou or x == board.getWidth() - 1)
        return;
    this->tryPushRight(x+1, y, visitedBoardElementsYou);
    this->tryMoveRight(x+1, y, visitedBoardElementsYou);
    if (not this->isCellFree(x+1, y))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
        {
            board.setNewPosition(cell[i], x+1, y);
            visitedBoardElementsYou.insert(cell[i]);
        }
    }
}
