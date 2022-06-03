#include "UnitFun.h"

Unit UnitFun::getSCV(Unit CommandCenter, list<int> &Miners, list<int> &Builders)
{
    Unit worker = CommandCenter->getClosestUnit(GetType == Terran_Supply_Depot.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);
    Miners.remove(worker->getID());//change duty to builder
    Builders.push_back(worker->getID());
    return worker;
}

Unit UnitFun::getBuilder(list<int> Builders)
{
    Unit builder = nullptr;
    for (auto& u : Builders)
    {
        Unit myBuilder = Broodwar->getUnit(u);        
        if (myBuilder != nullptr)
        {
            if (!myBuilder->isConstructing() && myBuilder->getHitPoints() != 0)
            {
                return myBuilder;                
            }
        }        
    }
    return builder;
}

Unit UnitFun::getWorker(Unit CommandCenter, list<int> &Miners, list<int> &Builders)
{
    Unit worker;

    if (!Builders.empty())
    {
        worker = UnitFun::getBuilder(Builders);        
        if (worker == nullptr)
        {
            worker = UnitFun::getSCV(CommandCenter, Miners, Builders);
        }
    }
    else
    {
        worker = UnitFun::getSCV(CommandCenter, Miners, Builders);
    }
    return worker;
}

list<Unit> UnitFun::getUnitList(UnitType Type, Unitset allUnits, list<int>& deadUnits)
{
    //TODO: TaskManager is not assigning the SCV to build, error
    list<Unit> myUnits;
    for (auto& u : allUnits)
    {
        int type = u->getType();
        if (u->getType() == Type && auxFun::validUnit(u, deadUnits))
        {
            myUnits.push_back(u);
        }
    }
    return myUnits;
}

int UnitFun::getUnitCount(const Unitset& allUnits, UnitType myType)
{
    int unitCount = 0;

    for (auto& u : allUnits)
    {
        int type = u->getType();
        if (u->getType() == myType)
        {
            unitCount += 1;
        }
    }

    return unitCount;
}
