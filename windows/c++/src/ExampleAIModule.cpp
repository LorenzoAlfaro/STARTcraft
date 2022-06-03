#include "ExampleAIModule.h"
//TODO: instead of defining an amount of marines, define the porcentage from the total food supply quota i.e 50% marines = 100 marines or 50 vultures
//TODO: fix bug, TASK ID is not being represented corectly
//Change Task Array to use Task Enum instead of indexes
//ADD building map file, where to build my buildings location
//Fix bug, when using scan it crashes! recognize the spell unit
//Implement error handling
//Add logic to build turrets
//Able to create control groups with more than 12 units 
using namespace std;
#pragma region MainEvents
void ExampleAIModule::onFrame()
{   
    try
    {
        Player BW = Broodwar->self();
        const int frameCount = Broodwar->getFrameCount();
        const int minerals = BW->minerals();
        const int gas = BW->gas();
        const Unitset myUnits = BW->getUnits();
        const int emptySupply = BW->supplyTotal() - BW->supplyUsed();
        const int barracksCount = UnitFun::getUnitCount(myUnits, Terran_Barracks);
        const int CommandCenterCount = UnitFun::getUnitCount(myUnits, Terran_Command_Center);
        const int SCVcount = UnitFun::getUnitCount(myUnits, Terran_SCV);
        const int marineCount = UnitFun::getUnitCount(myUnits, Terran_Marine);
        const int roomNeeded = auxFun::roomNeeded(CommandCenterCount, barracksCount);
        if (displayStats)
        {
            auxFun::displayInsights2(roomNeeded, emptySupply, SCVcount, barracksCount, marineCount, StatsCoordinates, Builders.size(), deadUnits.size(), taskQueue.size(), Unexplored.size());
        }

        if (auxFun::validFrame())
        {
            Walker::Walk(JimRaynor, true, frameCount, callBack,Unexplored);
            //TaskEngine::taskManager(taskQueue, frameCount, minerals, gas, UnitFun::getUnitList(Terran_Command_Center, myUnits, deadUnits).front(), Miners, Builders);

            //ProductionManager::Manage(minerals, gas, frameCount, taskQueue, deadUnits, barracksCount, SCVcount, maxBuilding, maxUnit, roomNeeded > emptySupply, roomNeeded);
            //eventually productionManager will be another task run by taskManager            
            //CommMngr::scvManager(Miners);//go mine for me minions!

            UserInterface::ReadCommand(frameCount, callBack, deadUnits, taskQueue);

        }
    }
    catch (const std::exception&)
    {
        Broodwar->sendText("On Frame Failed");
    }

    
}

void ExampleAIModule::onUnitCreate(Unit unit)
{
    try
    {
        if (IsOwned(unit))
        {
            if (unit->getType() == Terran_SCV)
            {
                Miners.push_back(unit->getID());//assign to mine
            }

            if (!taskQueue.empty() && !unit->canAttack()
                && unit->getType() != Terran_SCV
                && unit->getType() != Terran_Marine)
            {
                Unit builder = unit->getBuildUnit();
                int builderID = builder->getID();
                int BuildingID = unit->getID();


                array<int, 12> mytask = { 0,0,0,0,0,0,0 };
                array<int, 12>* pointer = TaskFun::findTaskAssignedToUnit(builderID, taskQueue);
                if (pointer != nullptr)
                {
                    mytask = *pointer;
                }
                //only for buildings
                if (TaskFun::taskStatusUpdate(builderID, taskQueue, BuildingID, Started))
                {
                    Broodwar->sendText("Started task id: %d : %s", mytask[ID], unit->getType().c_str());
                }
                else
                {
                    Broodwar->sendText("Failed update to started task id: %d : %s", unit->getID(), unit->getType().c_str());
                }
            }
        }
    }
    catch (const std::exception&)
    {
        Broodwar->sendText("On Unite Create Failed");
    }

          
}

void ExampleAIModule::onUnitComplete(Unit unit)
{
    try
    {
        if (IsOwned(unit))
        {
            if (!taskQueue.empty() && !unit->canAttack()) //avoid running in buildings
            {
                array<int, 12> mytask = { 0,0,0,0,0,0,0 };
                array<int, 12>* pointer = TaskFun::findTaskAssignedToUnit(unit->getID(), taskQueue);
                if (pointer != nullptr)
                {
                    mytask = *pointer;
                }

                if (TaskFun::taskStatusUpdate(unit->getID(), taskQueue, unit->getID(), Completed))
                {
                    Broodwar->sendText("Completed task id: %d : %s", mytask[ID], unit->getType().c_str());
                }
                else
                {
                    Broodwar->sendText("failed update to completed task id: %d : %s", unit->getID(), unit->getType().c_str());
                }
            }
            //TODO: test remove  
          //taskQueue.remove(TaskFun::findTaskAssignedToID(unit->getID(),taskQueue));
          //updateUnitCount(true, unit);
        }
    }
    catch (const std::exception&)
    {
        Broodwar->sendText("On Unite Complete Failed");            
    }
        
}

void ExampleAIModule::onUnitDestroy(Unit unit)
{
    try
    {
        if (IsOwned(unit))
        {
            deadUnits.push_back(unit->getID());
        }
    }
    catch (const std::exception&)
    {
        Broodwar->sendText("On Unite Die Failed");
    }
    

}

void ExampleAIModule::onSendText(string text)
{     
    try
    {
        UserInterface::ReadInput(text, deadUnits, displayStats, auxFun::getMousePosition());

        // Send the text to the game if it is not being processed.
        Broodwar->sendText("%s", text.c_str());
        // Make sure to use %s and pass the text as a parameter,
        // otherwise you may run into problems when you use the %(percent) character!
    }
    catch (const std::exception&)
    {
        Broodwar->sendText("On Send Text Failed");
    }
    
}

void ExampleAIModule::onStart()
{
    cout << "Start";
    if (!FileIO::readStatsCoordinates(StatsCoordinates))
    {
        Broodwar->sendText("Unable to open file");//cout << "Unable to open file"
    }
    FileIO::WriteHeaders();//for task record      
    // Print the map name.
    // BWAPI returns string when retrieving a string, don't forget to add .c_str() when printing!
    //Broodwar << "The map is  " << Broodwar->mapName() << "!" << endl;

    // Enable the UserInput flag, which allows us to control the bot and type messages.
    Broodwar->enableFlag(Flag::UserInput);

    // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
    //Broodwar->enableFlag(Flag::CompleteMapInformation);

    // Set the command optimization level so that common commands can be grouped
    // and reduce the bot's APM (Actions Per Minute).
    Broodwar->setCommandOptimizationLevel(2);

    //AI Jim Raynor
    list<Unit> raynors = UnitFun::getUnitList(Hero_Jim_Raynor_Marine, Broodwar->self()->getUnits(), deadUnits);

    if (raynors.size() > 0)
    {
        JimRaynor = raynors.front();
    }
    
    

    // Check if this is a replay
    if (!Broodwar->isReplay())
    {
        // Retrieve you and your enemy's races. enemy() will just return the first enemy.
        // If you wish to deal with multiple enemies then you must use enemies().
        if (Broodwar->enemy()) // First make sure there is an enemy
            Broodwar << "Welcome to the Jungle v1.1 " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << endl;
        
    }   
}

#pragma endregion

#pragma region OtherEvents

void ExampleAIModule::onReceiveText(Player player, string text)
{
    // Parse the received text
    Broodwar << player->getName() << " said \"" << text << "\"" << endl;
}

void ExampleAIModule::onUnitDiscover(Unit unit)
{
}

void ExampleAIModule::onUnitEvade(Unit unit)
{
}

void ExampleAIModule::onUnitShow(Unit unit)
{
}

void ExampleAIModule::onUnitHide(Unit unit)
{
}

void ExampleAIModule::onEnd(bool isWinner)
{
    // Called when the game ends
    if (isWinner)
    {
        // Log your win here!
    }
}

#pragma endregion

#pragma region NotUsedEvents
void ExampleAIModule::onSaveGame(string gameName)
{
    Broodwar << "The game was saved to \"" << gameName << "\"" << endl;
}

void ExampleAIModule::onUnitRenegade(Unit unit)
{
}

void ExampleAIModule::onUnitMorph(Unit unit)
{
    if (Broodwar->isReplay())
    {
        // if we are in a replay, then we will print out the build order of the structures
        if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
        {
            int seconds = Broodwar->getFrameCount() / 24;
            int minutes = seconds / 60;
            seconds %= 60;
            Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
        }
    }
}

void ExampleAIModule::onPlayerLeft(Player player)
{
    // Interact verbally with the other players in the game by
    // announcing that the other player has left.
    Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(Position target)
{
    // Check if the target is a valid position
    if (target)
    {
        // if so, print the location of the nuclear strike target
        Broodwar << "Nuclear Launch Detected at " << target << endl;
    }
    else
    {
        // Otherwise, ask other players where the nuke is!
        Broodwar->sendText("Where's the nuke?");
    }
    // You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

#pragma endregion
