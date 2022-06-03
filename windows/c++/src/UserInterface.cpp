#include "UserInterface.h"

void UserInterface::ReadCommand(int frameCount, int& callBack, list<int> deadUnits, list<array<int, 12>>& taskQueue)
{
    int step = 24;
    if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {      
            //Broodwar->sendText("A");
            Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();
            TilePosition myTile = myMarine->getTilePosition();
            Position movehere = myMarine->getPosition();
            movehere.x -= step;
            
            Position newPosition = (Position)myTile;
            WalkPosition walkPos = (WalkPosition)movehere;
            if (Broodwar->isWalkable(walkPos))
            {                
               myMarine->move(movehere);                
               Position myPos = auxFun::getUnitPosition(myMarine);
               Broodwar->setScreenPosition(myPos);
            }
            else
            {
                //Broodwar->sendText("Cant walk there");
                callBack = frameCount + 1;
            }
        }
        return;
    }
    if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {         
            //Broodwar->sendText("D"); //it is subtracting Y
            Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();
            TilePosition myTile = myMarine->getTilePosition();
            Position movehere = myMarine->getPosition();
            movehere.x += step;            
            Position newPosition = (Position)myTile;
            WalkPosition walkPos = (WalkPosition)movehere;
            if (Broodwar->isWalkable(walkPos))
            {                
                myMarine->move(movehere);
                Position myPos = auxFun::getUnitPosition(myMarine);
                Broodwar->setScreenPosition(myPos);                
            }
            else
            {
                //Broodwar->sendText("Cant walk there");
                callBack = frameCount + 1;
            }
        }
        return;
    }
    if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {            
           // Broodwar->sendText("S");
            Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();
            TilePosition myTile = myMarine->getTilePosition();
            Position movehere = myMarine->getPosition();
            movehere.y += step;            
            Position newPosition = (Position)myTile;
            WalkPosition walkPos = (WalkPosition)movehere;
            if (Broodwar->isWalkable(walkPos))
            {                
                myMarine->move(movehere);
                Position myPos = auxFun::getUnitPosition(myMarine);
                Broodwar->setScreenPosition(myPos);                
            }
            else
            {
                //Broodwar->sendText("Cant walk there");
                callBack = frameCount + 1;
            }
        }
        return;

    }
    if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)//it is subtracting X
        {      
            //Broodwar->sendText("W");
            Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();
            TilePosition myTile = myMarine->getTilePosition();
            Position movehere = myMarine->getPosition();
            movehere.y -= step;
            
            Position newPosition = (Position)myTile;
            WalkPosition walkPos = (WalkPosition)movehere;
            if (Broodwar->isWalkable(walkPos))
            {
            
                myMarine->move(movehere);                
                Position myPos = auxFun::getUnitPosition(myMarine);
                Broodwar->setScreenPosition(myPos);            
            }
            else
            {
                //Broodwar->sendText("Cant walk there");
                callBack = frameCount + 5;
            }
        }
        return;
    }
    if (GetKeyState('I') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            Broodwar->sendText("ATTACK!");
            Unit myMarine = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits).front();

            TilePosition myTile = myMarine->getTilePosition();

             

            Broodwar->sendText("Tile X %d :", myTile.x);
            Broodwar->sendText("Tile Y %d :", myTile.y);

            myTile.x += 3;            
            myTile.y += 3;

            Position newPosition = (Position)myTile;

            WalkPosition walkPos = (WalkPosition)myTile;
            

            if (Broodwar->isWalkable(walkPos))
            {
                Position myPos = auxFun::getMousePosition();
                CommMngr::attackUnits(UnitFun::getUnitList(Terran_Marine, Broodwar->self()->getUnits(), deadUnits), newPosition);
                callBack = frameCount + 30;
            }
            else
            {
                Broodwar->sendText("Cant walk there");
                callBack = frameCount + 60;
                    
            }

            
        }
        return;

    }
    if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15) LEFT CLICK*/)
    {
        if (frameCount >= callBack)
        {
            auxFun::LeftClick();// I cant believe this works!   
            callBack = frameCount + 60;
        }
        return;
    }
    if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            auxFun::RightClick();
            callBack = frameCount + 60;
        }
        return;
    }
    if (GetKeyState('U') & 0x8000)
    {
        if (frameCount >= callBack)
        {
            TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, Terran_Engineering_Bay);
            callBack = frameCount + 60;
        }
        return;
    }
    if (GetKeyState('Y') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, Terran_Command_Center);
            callBack = frameCount + 60;
        }
        return;

    }
    if (GetKeyState('T') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, Terran_Missile_Turret);
            callBack = frameCount + 60;
        }
        //The code here executes ONCE at the moment the other key was released            
        return;
    }
    if (GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, Terran_Refinery);
            callBack = frameCount + 60;
        }
        return;
    }
    if (GetKeyState('E') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        if (frameCount >= callBack)
        {
            TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, Terran_Barracks);
            callBack = frameCount + 60;
        }
        return;
    }
}

void UserInterface::ReadInput(string text, list<int> deadUnits, bool& displayStats, Position myPos)
{
    if (text == "b")
    {
        Broodwar->sendText("power overwhelming");
    }
    if (text == "stats")
    {
        displayStats = !displayStats;
    }
    if (text == "'")
    {
        CommMngr::attackUnits(UnitFun::getUnitList(Terran_Marine, Broodwar->self()->getUnits(), deadUnits), myPos);
    }
    if (text == ";")
    {
        CommMngr::moveUnits(UnitFun::getUnitList(Terran_Marine, Broodwar->self()->getUnits(), deadUnits), myPos);
    }
    if (text == "p")
    {
        CommMngr::setRallyPoint(UnitFun::getUnitList(Terran_Barracks, Broodwar->self()->getUnits(), deadUnits), myPos);
    }
    if (text == "q")
    {
        //for (auto& u : Miners)
        //{
           // Unit miner = Broodwar->getUnit(u);
            //miner->move(myPos);
           // miner->stop(true);
            //miner->gather(miner->getClosestUnit(IsMineralField), true); //the everyframe logic messes up this
       // }
    }
    if (text == "w")
    {
        //Unit builder = UnitFun::getBuilder(Builders);
        //builder->move(myPos);
        //builder->build(Terran_Command_Center, builder->getTilePosition());
    }
    if (text == "e")
    {
        //TaskFun::CreateTask(taskQueue, Broodwar->getFrameCount(), 0, taskOwner::Commander, action::BuildEngineeringBay);
        //Unit builder = UnitFun::getBuilder(Builders);
        //builder->move(myPos);
        //builder->build(Terran_Engineering_Bay, builder->getTilePosition());
    }

    if (text == "u")
    {
        static bool setGui = false;
        Broodwar->setGUI(setGui);
        setGui = !setGui;
        Broodwar->printf("Map x: %d y: %d", Broodwar->mapWidth(), Broodwar->mapHeight());
        Unitset myUnits = Broodwar->getSelectedUnits();
        for (auto& u : myUnits)
        {
            int x = u->getTilePosition().x;
            int y = u->getTilePosition().y;
            Broodwar->printf("x: %d y: %d", x, y);
        }
    }

}
