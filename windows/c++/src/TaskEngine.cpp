#include "TaskEngine.h"

void assessTask(array<int, 12>& myTask, int frameCount, int minerals, int gas, Unit CommandCenter, list<int>& Miners, list<int>& Builders)
{
    int taskStatus = myTask[tsk::Status];
    int callBackTime = myTask[tsk::TimeStamp] + myTask[tsk::Delay];

    if (taskStatus == taskStatus::Created || taskStatus == taskStatus::waitingMin)
    {
        if (frameCount > callBackTime)
        {
            if (TaskFun::mineralsAvailable(myTask, minerals) && TaskFun::gasAvailable(myTask, gas)) //and location available
            {
                //assign SCV, instead of SCV just get the ID directly, remove BWAPI 
                Unit SCV = UnitFun::getWorker(CommandCenter, Miners, Builders);
                //pass the worker id to the task
                myTask[tsk::UID] = SCV->getID();

                if (myTask[tsk::X] == 0 && myTask[tsk::Y] == 0)
                {
                    const TilePosition targetBuildLocation = BuildManager::returnBuildPosition(myTask[tsk::Action], SCV, 20);
                    myTask[tsk::X] = targetBuildLocation.x;
                    myTask[tsk::Y] = targetBuildLocation.y;
                }
                TaskFun::startTask(myTask, SCV);//set to PendingStart, onUnitCreate set to Start, onUnitComplete set to Complete
            }
            else
            {
                //do we have resources? assign, no? set callback time
                TaskFun::callBack(myTask, 200, taskStatus::waitingMin);
            }
        }
    }
    else if (taskStatus == taskStatus::PendingStart)
    {
        if (frameCount > callBackTime)
        {
            myTask[tsk::Status] = taskStatus::Cancelled;
            Broodwar->sendText("TaskMngr: Failed to start task id: %d : ", myTask[tsk::ID]); //remove the log to broodwar, send a error code
        }
    }
    else
    {

    }
}


void TaskEngine::taskManager(list<array<int, 12>>& myTaskQueue, int frameCount, int minerals, int gas, Unit CommandCenter, list<int>& Miners, list<int>& Builders)
{
    //TODO: eliminate the need to pass a commandcenter unit
    //if my task status is 0, not started, check timestamp
    //0 created, 1 reviewed but no resources to assign, 2 assigned with resources, 3 started, 4 completed, 5 cancel
    //production manager checks if there are tasks waiting for minerals before pumping units
    //assessTask(task) will determine wich task has high priority, for now if resources available just start them
    for (auto& task : myTaskQueue)
    {
        //assessTask(task,frameCount,minerals,gas,CommandCenter,Miners,Builders);
        int taskStatus = task[tsk::Status];
        int callBackTime = task[tsk::TimeStamp] + task[tsk::Delay];

        if (taskStatus == taskStatus::Created || taskStatus == taskStatus::waitingMin)
        {
            if (frameCount > callBackTime)
            {
                if (TaskFun::mineralsAvailable(task, minerals) && TaskFun::gasAvailable(task, gas)) //and location available
                {
                    //assign SCV, instead of SCV just get the ID directly, remove BWAPI 
                    Unit SCV = UnitFun::getWorker(CommandCenter, Miners, Builders);
                    //pass the worker id to the task
                    task[tsk::UID] = SCV->getID();

                    if (task[tsk::X] == 0 && task[tsk::Y] == 0)
                    {
                        const TilePosition targetBuildLocation = BuildManager::returnBuildPosition(task[tsk::Action], SCV, 20);
                        task[tsk::X] = targetBuildLocation.x;
                        task[tsk::Y] = targetBuildLocation.y;
                    }
                    TaskFun::startTask(task, SCV);//set to PendingStart, onUnitCreate set to Start, onUnitComplete set to Complete
                }
                else
                {
                    //do we have resources? assign, no? set callback time
                    TaskFun::callBack(task, 200, taskStatus::waitingMin);
                }
            }
        }
        else if (taskStatus == taskStatus::PendingStart)
        {
            if (frameCount > callBackTime)
            {
                task[tsk::Status] = taskStatus::Cancelled;
                Broodwar->sendText("TaskMngr: Failed to start task id: %d : ", task[tsk::ID]); //for some error 
            }
        }
        else
        {
                
        }        
    }   
}



