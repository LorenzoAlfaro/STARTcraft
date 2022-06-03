#include "TaskFun.h"

array<int, 12>* TaskFun::findTaskAssignedToUnit(int UnitID, list<array<int, 12>> &Tasks)
{
    bool found = false;
    array<int, 12>* mytask; //pass the address of the array//initialize first to something

    for (auto& task : Tasks)
    {
        if (task[UID] == UnitID) //
        {
            mytask = &task;
            found = true;
        }
    }

    if (found)
    {
        return mytask;
    }
    else
    {
        return nullptr;
    }
    
}

array<int, 12>* TaskFun::findTaskAssignedToID(int TaskID, list<array<int, 12>>& Tasks)
{
    bool found = false;
    array<int, 12>* mytask; //pass the address of the array//initialize first to something

    for (auto& task : Tasks)
    {
        if (task[ID] == TaskID) //
        {
            mytask = &task;
        }
    }

    if (found)
    {
        return mytask;
    }
    else
    {
        return nullptr;
    }
}

bool TaskFun::TaskQueued(list<array<int, 12>> &myTaskQueue, int taskOwner, int action)
{
    bool taskInQueue = false;
    for (auto& task : myTaskQueue)
    {
        if (task[Owner] == taskOwner)
        {
            if (task[Action] == action)//task action, build supplydepot, build barrack, etc
            {                
                //found a task that belongs to me
                if (task[Status] != Completed && task[Status] != Cancelled)
                {
                    taskInQueue = true;
                }
            }
        }
    }

    return taskInQueue;
}

array<int, 3> TaskFun::resourceCost(const int action)
{
    array<int, 3> price = { 0,0 };
    switch (action)
    {
    case action::BuildBarrack:

        price[0] = 150;
        price[1] = 0;
        price[2] = 50; //time needed in seconds

        break;
    case action::BuildSupplyDepot:

        price[0] = 100;
        price[1] = 0;
        price[2] = 25;

        break;

    default:

        break;
    }
    return price;
}

array<int, 3> TaskFun::resourceCost2(const int action)
{
    UnitType myUnit = action;
    
    array<int, 3> price = { 0,0,0 };
    price[0] = myUnit.mineralPrice();
    price[1] = myUnit.gasPrice();    
    price[2] = myUnit.buildTime(); //time needed in frames    
    return price;
}

bool TaskFun::mineralsAvailable(array<int, 12> task, int CurrentMinerals)
{    
    array<int, 3> price = resourceCost2(task[Action]);
    if (CurrentMinerals >= price[0])
    {        
        return true;
    }
    return false;    
}

bool TaskFun::gasAvailable(array<int, 12> task, int CurrentGas)
{    
    array<int, 3> price = resourceCost2(task[Action]);
    if (CurrentGas >= price[1])
    {
        return true;
    }       
    return false;
        
}

bool TaskFun::tasksWaitingResources(list<array<int, 12>> &myTaskQueue)
{
    //dont keep pumping units until we can start the building of depots or etc...
    bool waiting = false;
    for (auto& task : myTaskQueue)
    {
        int status = task[Status];
        if (status == waitingGas || status == PendingStart || status == waitingMin)//make sure production doesn't steal minerals while scv travelling
        {
            waiting = true;
        }
    }
    return waiting;
}

void TaskFun::taskStartedUpdate(list<array<int, 12>> &myTaskQueue, Unit Building)
{
    Unit builder = Building->getBuildUnit();    
    for (auto& task : myTaskQueue)
    {
        if (&task == TaskFun::findTaskAssignedToID(builder->getID(), myTaskQueue))
        {
            task[Status] = Started;
            task[UID] = Building->getID(); //updated the task scvID to the building currently in progress
        }
    }    
}

void TaskFun::taskCompleted(list<array<int, 12>> &myTaskQueue, Unit Building)
{    
    for (auto& task : myTaskQueue)
    {
        if (&task == TaskFun::findTaskAssignedToID(Building->getID(), myTaskQueue))
        {
            task[Status] = Completed;
            task[UID] = Building->getID(); //updated the task scvID to the building currently in progress
        }
    }    
}

bool TaskFun::taskStatusUpdate(int ID, list<array<int, 12>> &Tasks, int newID, int newStatus)
{
    bool updatedTask = false;
    for (auto& task : Tasks)
    {
        if (task[UID] == ID)
        {            
            task[Status] = newStatus;
            task[UID] = newID;
            updatedTask = true;
        }
    }
    return updatedTask;
}

void TaskFun::assessTask(array<int, 12>& newTask)
{
    //ok new task, what do you want?
    //do we have resources to complete your task?
    // what priority should I give you?
}



void TaskFun::CreateTask(list<array<int, 12>>& myTaskQueue,int timeStamp,int delay,int taskOwner,int action)
{
    array<int, 3> price = TaskFun::resourceCost2(action);
    array<int, 12> mytask;
    mytask[TimeStamp] = timeStamp;
    mytask[Delay] = delay;
    mytask[Action] = action;
    mytask[UID] = 0;
    mytask[Owner] = taskOwner;
    mytask[Status] = Created;
    //mytask[ID] = TaskCount;
    mytask[ID] = myTaskQueue.size();
    mytask[X] = 0;
    mytask[Y] = 0;
    mytask[Minerals] = price[0];
    mytask[Gas] = price[1];
    mytask[Duration] = price[2];
    
    myTaskQueue.push_back(mytask);
    //TaskCount += 1;
    TaskFun::logTaskUpdate(mytask);
}

void TaskFun::callBack(array<int, 12>& Task, int When, int Why)
{
    //do we have resources? assign, no? set callback time
    Task[TimeStamp] = Broodwar->getFrameCount(); //reset timer
    Task[Delay] = When; //frames, should be determined by the income rate, (miners working)
    Task[Status] = Why;
}

void TaskFun::startTask(array<int, 12>& Task, Unit builder)
{
    //Unit builder = UnitFun::returnUnitByID(Broodwar->self()->getUnits(), Task[3]); //the task has an available worker assigned
    //int builderID = builder->getID();
    //TilePosition targetBuildLocation; //TODO: improve space allocation
    //targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Supply_Depot, builder->getTilePosition());
    //TODO: better target location method needed

    const TilePosition targetBuildLocation(Task[X], Task[Y]);

    BuildManager::buildBuilding(builder, Task[Action], Colors::Blue, targetBuildLocation);

    //switch (Task[Action])
    //{

    //case action::BuildSupplyDepot:

    //    BuildManager::buildBuilding(builder, UnitTypes::Terran_Supply_Depot, Colors::Blue, targetBuildLocation);

    //    break; //optional
    //case action::BuildBarrack:

    //    BuildManager::buildBuilding(builder, UnitTypes::Terran_Barracks, Colors::Green, targetBuildLocation);

    //    break; //optional

    // // you can have any number of case statements.
    //default: //Optional
    //    //statement(s);
    //    break;
    //}

    callBack(Task, 200, PendingStart); //things can happen during travel time
}

void TaskFun::logTaskUpdate(array<int, 12>& task)
{
    ofstream myfile;
    myfile.open("TaskRecord.txt", ofstream::app);
    myfile << task[TimeStamp] << " "
        << task[Delay] << " "
        << task[Action] << " "
        << task[UID] << " "
        << task[Owner] << " "
        << task[Status] << " "
        << task[ID] << " "
        << task[X] << " "
        << task[Y] << " "
        << task[Minerals] << " "
        << task[Gas] << " "
        << task[Duration] << " "
        << Broodwar->getFrameCount() << '\n';

    myfile.close();

}