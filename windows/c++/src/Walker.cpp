#include "Walker.h"


int step = 36; //tile is 32
list<TilePosition>  walked; //Walked tiles

list<TilePosition>  unWalked; //Walked tiles

list<TilePosition>  options; //Walkable options





bool included(list<TilePosition >  walked, TilePosition currentPos)
{
    for (auto& position : walked)
    {
        if ((currentPos.x == position.x) &&
            (currentPos.y == position.y))
        {
            return true;
        }
    }

    return false;
}

TilePosition myNextMovement(list<TilePosition>  walked, Position currentPos, list<TilePosition>& Unexplored)
{
    //scan your options, only back track when there is dead end. Choose left when possible
    options.clear(); //cleanup
    //Unexplored.clear();
    
    
    
    Position Right = currentPos;
    Right.x += step;
    if (Broodwar->isWalkable((WalkPosition)Right))
    {
        options.push_back((TilePosition)Right);
    }
    
    
    
    Position Down = currentPos;
    Down.y += step;
    if (Broodwar->isWalkable((WalkPosition)Down))
    {
        options.push_back((TilePosition)Down);
    }
    
    Position Left = currentPos;
    Left.x -= step;
    if (Broodwar->isWalkable((WalkPosition)Left))
    {
        options.push_back((TilePosition)Left);
    }

    Position Up = currentPos;
    Up.y -= step;
    if (Broodwar->isWalkable((WalkPosition)Up))
    {
        options.push_back((TilePosition)Up);
    }

    for each (TilePosition myOption  in options)
    {
        if (!included(walked, myOption) && !included(Unexplored, myOption)) //what options have I walked already, remove
        {
            Unexplored.push_front(myOption); //create a stack structure FIFO
            //Broodwar->sendText("Unexplored Tiles: %d", Unexplored.size());
        }
    }

    TilePosition nextMovement;
    if (Unexplored.size() != 0)
    {

        TilePosition currentTile = (TilePosition)currentPos;
        nextMovement = Unexplored.front();
        if (currentTile == nextMovement)
        {
            Unexplored.pop_front(); //give time for the marine to get there
        }
                
    }
    else
    {
        nextMovement = (TilePosition)currentPos;
    }
    
    
    return nextMovement;
    
}



void Walker::moveLeft(Unit myUnit, bool Attack) {
    //if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    //{                    
        //Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();
        
        //TilePosition myTile = myUnit->getTilePosition();
        Position movehere = myUnit->getPosition();
        movehere.x -= step;
        if (!Attack)
        {
            myUnit->move(movehere);
        }
        else
        {
            myUnit->attack(movehere);
        }
        
        Position myPos = auxFun::getUnitPosition(myUnit);
        Broodwar->setScreenPosition(myPos);

        //Position newPosition = (Position)myTile;
        //WalkPosition walkPos = (WalkPosition)movehere;
        //if (Broodwar->isWalkable(walkPos))
        //{
            
        //}                
        return;
    //}
}
void Walker::moveRight(Unit myUnit, bool Attack) {    
    Position movehere = myUnit->getPosition();
    movehere.x += step;
    if (!Attack)
    {
        myUnit->move(movehere);
    }
    else
    {
        myUnit->attack(movehere);
    }
    Position myPos = auxFun::getUnitPosition(myUnit);
    Broodwar->setScreenPosition(myPos);    
    return;    
}
void Walker::moveUp(Unit myUnit, bool Attack) {    
    Position movehere = myUnit->getPosition();
    movehere.y -= step;
    if (!Attack)
    {
        myUnit->move(movehere);
    }
    else
    {
        myUnit->attack(movehere);
    }
    Position myPos = auxFun::getUnitPosition(myUnit);
    Broodwar->setScreenPosition(myPos);    
    return;    
}
void Walker::moveToPosition(Unit myUnit, bool Attack, Position moveHere) {        
    if (!Attack)
    {
        myUnit->move(moveHere);
    }
    else
    {
        myUnit->attack(moveHere);
    }
    Position myPos = auxFun::getUnitPosition(myUnit);
    Broodwar->setScreenPosition(myPos);    
    return;    
}

void Walker::moveDown(Unit myUnit, bool Attack) {
    Position movehere = myUnit->getPosition();
    movehere.y += step;
    if (!Attack)
    {
        myUnit->move(movehere);
    }
    else
    {
        myUnit->attack(movehere);
    }
    Position myPos = auxFun::getUnitPosition(myUnit);
    Broodwar->setScreenPosition(myPos);
    return;
}

void Walker::Walk(Unit myUnit, bool Attack, int frameCount, int& callBack, list<TilePosition>&  Unexplored)
{
    //figure logic to keep moving                           
    //TilePosition myTile = myUnit->getTilePosition();
    //Position newPosition = (Position)myTile;
    if (frameCount >= callBack && !myUnit->isUnderAttack())
    {
        
        //cout << "trying console";        
        Position currentPos = myUnit->getPosition();
        //add the new position to the list



        TilePosition tileWalked = (TilePosition)currentPos;

        if (included(Unexplored, tileWalked))
        {
            Unexplored.remove(tileWalked); //give time for the marine to get there
        }


        walked.push_back(tileWalked);

        TilePosition myNextTile = myNextMovement(walked, currentPos, Unexplored);
        
        moveToPosition(myUnit, Attack, (Position)myNextTile);

        //Broodwar->sendText("Unexplored Tiles: %d", Unexplored.size());        
        
        callBack = frameCount + 0;
        return;
    }          
}

