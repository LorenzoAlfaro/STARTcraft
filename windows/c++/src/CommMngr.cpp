#include "CommMngr.h"


void CommMngr::attackUnits(list<Unit> units, Position myPos)
{
    for (auto& u : units)
    {        
        u->attack(myPos, false);
    }
}

void CommMngr::moveUnits(list<Unit> units, Position myPos)
{
    for (auto& u : units)
    {
        u->move(myPos, false);
    }
}

void CommMngr::setRallyPoint(list<Unit> buildings, Position myPos)
{
    for (auto& u : buildings)
    {
        u->setRallyPoint(myPos);
    }
}

void CommMngr::scvManager(list<int> Miners)
{
    for (auto& ID : Miners)
    {        
        Unit u = Broodwar->getUnit( ID);
        if (u != NULL)
        {
            if (u->isIdle())
            {
                u->gather(u->getClosestUnit(IsMineralField || IsRefinery));
            }
        }        
    }
}

void CommMngr::buildSCVs(list<Unit> commandCenters)
{
    for (auto& u : commandCenters)
    {
        if (u->isIdle())
        {
            u->train(BWAPI::UnitTypes::Terran_SCV);
        }
    }
}

void CommMngr::trainMarines(list<Unit> barracks)
{
    for (auto& u : barracks)
    {
        if (u->isIdle() && !u->train(BWAPI::UnitTypes::Terran_Marine))
        {
            //supplyBlock(u);

        } // closure: failed to train idle unit
    }
}
