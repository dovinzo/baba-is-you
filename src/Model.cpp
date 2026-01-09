#include "Model.hpp"
#include <vector>

Model::Model(int level): board{level}, rules{}, boardHistory{}
{
    this->updateRules();
    boardHistory.push(board.makeSnapshot());
}

std::vector<BoardElement*> Model::operator[](RuleProperty property) const
{
    std::vector<BoardElement*> elements;
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < board.getWidth() ; x++)
    {
        for (int y = 0 ; y < board.getHeight() ; y++)
        {
            cell = board(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                if (this->boardElementHasProperty(*(cell.at(i)), property))
                {
                    elements.push_back(cell.at(i));
                }
            }
        }
    }
    return elements;
}

void Model::move(Direction direction)
{
    int x, y;
    std::vector<BoardElement*> boardElementsYou = (*this)[RuleProperty::YOU];
    std::set<BoardElement*> visitedBoardElementsYou;

    for (int i = 0 ; i < static_cast<int>(boardElementsYou.size()) ; i++)
    {
        if (boardElementHasProperty(*boardElementsYou.at(i), RuleProperty::STOP))
            continue;
        if (visitedBoardElementsYou.count(boardElementsYou.at(i)))
            continue; // on saute si déjà visité
        x = boardElementsYou.at(i)->getPositionX();
        y = boardElementsYou.at(i)->getPositionY();
        this->tryMove(x, y, visitedBoardElementsYou, direction);
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

void Model::tryPush(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou, Direction direction)
{
    std::vector<BoardElement*> cell = board(x, y);
    bool hasStop{false}, hasYou{false}, hasPush{false};
    bool edge;
    int dx, dy;
    switch (direction)
    {
        case Direction::UP:
            edge = (y == 0);
            dx = 0;
            dy = -1;
            break;
        case Direction::DOWN:
            edge = (y == board.getHeight() - 1);
            dx = 0;
            dy = 1;
            break;
        case Direction::LEFT:
            edge = (x == 0);
            dx = -1;
            dy = 0;
            break;
        case Direction::RIGHT:
            edge = (x == board.getWidth() - 1);
            dx = 1;
            dy = 0;
            break;
    }
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::STOP))
            hasStop = true;
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::YOU))
            hasYou = true;
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::PUSH))
            hasPush = true;
    }
    if (hasStop or not hasPush or hasYou or edge)
        return;
    this->tryPush(x+dx, y+dy, visitedBoardElementsYou, direction);
    this->tryMove(x+dx, y+dy, visitedBoardElementsYou, direction);
    if (not this->isCellFree(x+dx, y+dy))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::PUSH))
            board.setNewPosition(cell.at(i), x+dx, y+dy);
    }
}

void Model::tryMove(int x, int y, std::set<BoardElement*>& visitedBoardElementsYou, Direction direction)
{
    std::vector<BoardElement*> cell = board(x, y);
    bool hasYou{false};
    bool edge;
    int dx, dy;
    switch (direction)
    {
        case Direction::UP:
            edge = (y == 0);
            dx = 0;
            dy = -1;
            break;
        case Direction::DOWN:
            edge = (y == board.getHeight() - 1);
            dx = 0;
            dy = 1;
            break;
        case Direction::LEFT:
            edge = (x == 0);
            dx = -1;
            dy = 0;
            break;
        case Direction::RIGHT:
            edge = (x == board.getWidth() - 1);
            dx = 1;
            dy = 0;
            break;
    }
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::YOU))
            hasYou = true;
    }
    if (not hasYou or edge)
        return;
    this->tryPush(x+dx, y+dy, visitedBoardElementsYou, direction);
    this->tryMove(x+dx, y+dy, visitedBoardElementsYou, direction);
    if (not this->isCellFree(x+dx, y+dy))
        return;
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::YOU))
        {
            board.setNewPosition(cell.at(i), x+dx, y+dy);
            visitedBoardElementsYou.insert(cell.at(i));
        }
    }
}

bool Model::isCellFree(int x, int y) const
{
    std::vector<BoardElement*> cell = board(x, y);
    for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
    {
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::STOP))
            return false;
        if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::PUSH))
            return false;
    }
    return true;
}

const std::vector<BoardElement*>& Model::operator()(int x, int y) const
{
    return board(x, y);
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
            cell = board(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::YOU))
                    hasYou = true;
                if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::WIN))
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
            cell = board(x, y);
            bool killCell = false;

            if (cell.size() == 1 && this->boardElementHasProperty(*(cell.at(0)), RuleProperty::SINK) && this->boardElementHasProperty(*(cell.at(0)), RuleProperty::YOU)) 
                killCell = true;

            else if (cell.size() > 1) {
                for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
                {
                    if (this->boardElementHasProperty(*(cell.at(i)), RuleProperty::SINK))
                    {
                        killCell = true;
                        break;
                    }
                }
            }
           
            if (killCell) {
                
                    board.killCell(x,y); 
                
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


void Model::updateHorizontalRuleFromCell(int x, int y)
{
    RuleSubject ruleSubject;
    RuleProperty ruleProperty;
    std::vector<BoardElement*> cellxy = board(x, y);
    std::vector<BoardElement*> cellxplus1y = board(x+1, y);
    std::vector<BoardElement*> cellxplus2y = board(x+2, y);
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
    std::vector<BoardElement*> cellxy = board(x, y);
    std::vector<BoardElement*> cellxyplus1 = board(x, y+1);
    std::vector<BoardElement*> cellxyplus2 = board(x, y+2);
    for (int i = 0 ; i < static_cast<int>(cellxy.size()) ; i++)
    {
        if (cellxy.at(i)->getCategory() == BoardElementCategory::TEXT_OBJECT)
        {
            for (int j = 0 ; j < static_cast<int>(cellxyplus1.size()) ; j++)
            {
                if (cellxyplus1.at(j)->getCategory() == BoardElementCategory::TEXT_IS)
                {
                    for (int k = 0 ; k < static_cast<int>(cellxyplus2.size()) ; k++)
                    {
                        if (cellxyplus2.at(k)->getCategory() == BoardElementCategory::TEXT_PROPERTY)
                        {
                            ruleSubject = Model::TextObjectToRuleSubject(cellxy.at(i)->getType());
                            ruleProperty = Model::TextPropertyToRuleProperty(cellxyplus2.at(k)->getType());
                            rules.setRule(ruleSubject, ruleProperty);
                        }
                    }
                }
            }
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




