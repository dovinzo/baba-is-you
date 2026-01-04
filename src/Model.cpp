#include "Model.hpp"
#include "Enums.hpp"
#include "BoardElement.hpp"
#include "Victory.hpp"
#include <vector>
#include <algorithm>

Model::Model(int level): board{level}, rules{}, boardHistory{}
{
    this->updateRules();
    boardHistory.push(board.makeSnapshot());
}

void Model::moveUp()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);


    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (boardElementHasProperty(*boardElementsYou[i], RuleProperty::STOP))
            continue;
            


        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveUp(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
    {
        this->updateRules();
        this->sink();
        boardHistory.push(board.makeSnapshot());
        if (this->checkWin())
            this->notifyObservers(Victory{});
    }
}

void Model::moveDown()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (boardElementHasProperty(*boardElementsYou[i], RuleProperty::STOP))
            continue;
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveDown(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
    {
        this->updateRules();
        this->sink();
        boardHistory.push(board.makeSnapshot());
        if (this->checkWin())
            this->notifyObservers(Victory{});
    }
}

void Model::moveLeft()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (boardElementHasProperty(*boardElementsYou[i], RuleProperty::STOP))
            continue;
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveLeft(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
    {
        this->updateRules();
        this->sink();
        boardHistory.push(board.makeSnapshot());
        if (this->checkWin())
            this->notifyObservers(Victory{});
    }
}

void Model::moveRight()
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = this->getBoardElements(RuleProperty::YOU);
    std::set<BoardElement*> visitedBoardElementsYou;
    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (boardElementHasProperty(*boardElementsYou[i], RuleProperty::STOP))
            continue;
        if (visitedBoardElementsYou.count(boardElementsYou[i]))
            continue;
        x = boardElementsYou[i]->getPositionX();
        y = boardElementsYou[i]->getPositionY();
        this->tryMoveRight(x, y, visitedBoardElementsYou);
    }
    if (not visitedBoardElementsYou.empty())
    {
        this->updateRules();
        this->sink();
        boardHistory.push(board.makeSnapshot());
        if (this->checkWin())
            this->notifyObservers(Victory{});
    }
}

bool Model::undo()
{
    const BoardSnapshot* boardSnapshot = boardHistory.undo();
    if (boardSnapshot == nullptr)
        return false;
    board = *boardSnapshot;
    this->updateRules();
    return true;
}

bool Model::redo()
{
    const BoardSnapshot* boardSnapshot = boardHistory.redo();
    if (boardSnapshot == nullptr)
        return false;
    board = *boardSnapshot;
    this->updateRules();
    return true;
}

bool Model::checkWin() const
{
    bool hasYou{false}, hasWin{false};
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            hasYou = false;
            hasWin = false;
            cell = board.getCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                if (this->boardElementHasProperty(*(cell[i]), RuleProperty::YOU))
                    hasYou = true;
                if (this->boardElementHasProperty(*(cell[i]), RuleProperty::WIN))
                    hasWin = true;
            }
            if (hasYou and hasWin)
                return true;
        }
    }
    return false;
}

void Model::sink()  {
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            cell = board.getCell(x, y);
            bool killCell = false;
            if (cell.size() == 0)
                if (this->boardElementHasProperty(*(cell[0]), RuleProperty::SINK) && this->boardElementHasProperty(*(cell[0]), RuleProperty::YOU)) 
                    killCell = true;

            if (cell.size() > 1) {
                for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
                {
                    if (this->boardElementHasProperty(*(cell[i]), RuleProperty::SINK))
                    {
                        killCell = true;
                        break;
                    }
                }
            }
           
            if (killCell) {
                for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
                {
                    board.killCell(x,y); 
                }
            }
        }
    }

}

int Model::getBoardWidth() const
{
   return board.getWidth();
}

int Model::getBoardHeight() const
{
    return board.getHeight();
}

std::vector<BoardElement*> Model::getBoardCell(int x, int y) const
{
    return board.getCell(x, y);
}

std::vector<BoardElement*> Model::getBoardElements(RuleProperty ruleProperty)
{
    std::vector<BoardElement*> boardElements;
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            cell = board.getCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                if (this->boardElementHasProperty(*(cell[i]), ruleProperty))
                {
                    boardElements.push_back(cell[i]);
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
        case BoardElementType::WATER:
            ruleSubject = RuleSubject::WATER;
            break;
        default:
            throw std::invalid_argument("Problème de convertion BoardElementType -> RuleSubject (Model)");
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
        case BoardElementType::TEXT_SINK:
            ruleProperty = RuleProperty::SINK;
            break;
        default:
            throw std::invalid_argument("Problème de convertion BoardElementType -> RuleProperty (Model)");
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
        case BoardElementType::TEXT_WATER:
            ruleSubject = RuleSubject::WATER;
            break;
        default:
            throw std::invalid_argument("Problème de convertion BoardElementType -> RuleSubject (Model)");
            break;
    }
    return ruleSubject;
}

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
    std::vector<BoardElement*> cellxy = board.getCell(x, y);
    std::vector<BoardElement*> cellxplus1y = board.getCell(x+1, y);
    std::vector<BoardElement*> cellxplus2y = board.getCell(x+2, y);
    for (int i = 0 ; i < static_cast<int>(cellxy.size()) ; i++)
    {
        if (cellxy[i]->getCategory() == BoardElementCategory::TEXT_OBJECT)
        {
            for (int j = 0 ; j < static_cast<int>(cellxplus1y.size()) ; j++)
            {
                if (cellxplus1y[j]->getCategory() == BoardElementCategory::TEXT_IS)
                {
                    for (int k = 0 ; k < static_cast<int>(cellxplus2y.size()) ; k++)
                    {
                        if (cellxplus2y[k]->getCategory() == BoardElementCategory::TEXT_PROPERTY)
                        {
                            ruleSubject = Model::TextObjectToRuleSubject(cellxy[i]->getType());
                            ruleProperty = Model::TextPropertyToRuleProperty(cellxplus2y[k]->getType());
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
    std::vector<BoardElement*> cellxy = board.getCell(x, y);
    std::vector<BoardElement*> cellxyplus1 = board.getCell(x, y+1);
    std::vector<BoardElement*> cellxyplus2 = board.getCell(x, y+2);
    for (int i = 0 ; i < static_cast<int>(cellxy.size()) ; i++)
    {
        if (cellxy[i]->getCategory() == BoardElementCategory::TEXT_OBJECT)
        {
            for (int j = 0 ; j < static_cast<int>(cellxyplus1.size()) ; j++)
            {
                if (cellxyplus1[j]->getCategory() == BoardElementCategory::TEXT_IS)
                {
                    for (int k = 0 ; k < static_cast<int>(cellxyplus2.size()) ; k++)
                    {
                        if (cellxyplus2[k]->getCategory() == BoardElementCategory::TEXT_PROPERTY)
                        {
                            ruleSubject = Model::TextObjectToRuleSubject(cellxy[i]->getType());
                            ruleProperty = Model::TextPropertyToRuleProperty(cellxyplus2[k]->getType());
                            rules.setRule(ruleSubject, ruleProperty);
                        }
                    }
                }
            }
        }
    }
}

bool Model::isCellFree(int x, int y) const
{
    std::vector<BoardElement*> cell = board.getCell(x, y);
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::STOP))
            return false;
        if (this->boardElementHasProperty(*(cell[i]), RuleProperty::PUSH))
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
