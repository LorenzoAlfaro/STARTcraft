#pragma once
#include <array>
#include <BWAPI.h>
#include "BuildManager.h"
#include <fstream>
using namespace std;
using namespace BWAPI;

class TaskFun
{
public:
	static array<int, 12>* findTaskAssignedToUnit(int ID, list<array<int, 12>>& Tasks);
    static array<int, 12>* findTaskAssignedToID(int TaskID, list<array<int, 12>>& Tasks);
	static bool TaskQueued(list<array<int, 12>>& myTaskQueue, int taskOwner, int action);
    static array<int, 3> TaskFun::resourceCost(const int action);
    static array<int, 3> TaskFun::resourceCost2(const int action);
    static bool mineralsAvailable(array<int, 12> task, int CurrentMinerals);
    static bool gasAvailable(array<int, 12> task, int CurrentMinerals);
    static bool tasksWaitingResources(list<array<int, 12>>& myTaskQueue);
    static void taskStartedUpdate(list<array<int, 12>>& myTaskQueue, Unit Building);
    static void taskCompleted(list<array<int, 12>>& myTaskQueue, Unit Building);
    static bool taskStatusUpdate(int ID, list<array<int, 12>>& Tasks, int newID, int newStatus);  
    static void assessTask(array<int, 12>& newTask);    
    static void CreateTask(list<array<int, 12>>& myTaskQueue,int timeStamp,int delay,int taskOwner,int action);
    static void callBack(array<int, 12>& Task, int When, int Why);
    static void startTask(array<int, 12>& Task, Unit builder);
    static void logTaskUpdate(array<int, 12>& task);
};

enum  taskStatus {
    Created,        //try to assign
    //Reviewed,       //-Not being used    
    waitingMin,     //* the task is waiting for minerals, set callback time, try to assign after callbacktime
    waitingGas,     //-Not being used the task is waiting for gas
    //waitingClear,   //-Not being used the task is waiting for the building place to clear, or the building to stop to add-on
    PendingStart,   //* has an SCV ID assign to build, or the building ID to research upgrade 
    Started,        //* unit started building,  OnUnitCreate()
    Completed,      //* onUnitComplete(), this task could be removed from queue
    Cancelled       //-Something interrupted the building, this task could be removed from queue
    //Paused,         //-Not being used
    
};

//Created ->PendingStart or ->waitingMin
//PendingStart -> Started //if nothing interrupts the SCV
//PendingStart -> Cancelled //if SCV got blocked
//Started -> Completed //if building completes

enum  action {
    BuildSupplyDepot = 109,
    BuildBarrack = 111,
    BuildExtractor = 110,
    BuildEngineeringBay = 122,
    BuildTurret = 124,
    researchStim
};

enum  taskOwner {
    ProductionManager,
    StratManager,
    Commander
};

enum  tsk
{
    TimeStamp,
    Delay,
    Action,
    UID,
    Owner,
    Status,
    ID,
    X,
    Y,
    Minerals,
    Gas,
    Duration
};


