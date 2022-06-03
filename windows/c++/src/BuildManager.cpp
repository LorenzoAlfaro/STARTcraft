#include "BuildManager.h"


void BuildManager::createEventTag(const Unit &Building, Error lastErr)
{
    // If building scv fails, draw the error at the location so that you can visibly see what went wrong!
    // However, drawing the error once will only appear for a single frame
    // so create an event that keeps it on the screen for some frames
    const Position pos = Building->getPosition();
    //
    Broodwar->registerEvent([pos, lastErr](Game*) { Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
        nullptr,    // condition
        Broodwar->getLatencyFrames());  // frames to run

}

void BuildManager::createSupplyBox(const TilePosition targetBuildLocation, const UnitType Building, const  Color color)
{
    // Register an event that draws the target build location
    Broodwar->registerEvent([targetBuildLocation, Building, color](Game*)
        {
            Broodwar->drawBoxMap(Position(targetBuildLocation),
                Position(targetBuildLocation + Building.tileSize()),
                color);
        },
        nullptr,  // condition
            Building.buildTime() + 100);  // frames to run

}

void BuildManager::buildBuilding(const Unit &supplyBuilder, const UnitType Building, const Color color, const TilePosition targetBuildLocation)
{    
    if (targetBuildLocation)
    {
        BuildManager::createSupplyBox(targetBuildLocation, Building, color); //draw where to build
        // Order the builder to construct the supply structure
        if (!supplyBuilder->build(Building, targetBuildLocation))
        {
            Broodwar->sendText("Failed building %s :", Building.c_str());
            Broodwar->sendText(Broodwar->getLastError().c_str());
            //Broodwar << Broodwar->getLastError() << std::endl;;
        }
    }
}

TilePosition BuildManager::returnBuildPosition(int action, Unit SCV, int maxRange)
{
    TilePosition myBuildingLocation;

    return Broodwar->getBuildLocation(action, SCV->getTilePosition(), maxRange); //action maps to the unit type enum
    //switch (action)
    //{
    //case action::BuildSupplyDepot:

    //    myBuildingLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, SCV->getTilePosition(), maxRange);
    //    break; //optional
    //case action::BuildBarrack:

    //    myBuildingLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, SCV->getTilePosition(), maxRange);
    //    break; //optional

    // // you can have any number of case statements.
    //default: //Optional
    //    myBuildingLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, SCV->getTilePosition(), maxRange);
    //    //statement(s);
    //    break;
    //}
    //return myBuildingLocation;
}