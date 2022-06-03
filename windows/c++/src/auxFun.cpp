#include "auxFun.h"


int auxFun::SupplyTotal(int commandCenterCount, int supplyDepotCount)
{
    return (commandCenterCount * 10) + (supplyDepotCount * 8);    
}

int auxFun::usedSupplyTotal(int marineCount, int scvCount)
{
    return (marineCount * 1) + (scvCount * 1);    
}

int auxFun::roomNeeded(int commandCenterCount, int barrackCount)
{
    int offset = 1;
    int supply = offset + commandCenterCount * 1 + barrackCount * 1; //will need finer adjuments per individual units

    return supply*2;
}

bool auxFun::validUnit(Unit u, list<int> deadUnits)
{
    bool valid = false;
    // Ignore the unit if it no longer exists
    // Make sure to include this block when handling any Unit pointer!
    if (!isUnitDead(deadUnits, u->getID()))
    {
        if (u->exists())
        {
            if (!u->isLockedDown() && !u->isMaelstrommed() && !u->isStasised())
            {
                if (!u->isLoaded() && u->isPowered() && !u->isStuck())
                {
                    if (u->isCompleted() && !u->isConstructing())
                    {
                        return true;
                    }
                }
            }
        }
    }    
    return valid;
}

bool auxFun::validFrame()
{
    bool valid = false;
    // Return if the game is a replay or is paused
    if (!Broodwar->isReplay() && !Broodwar->isPaused() && Broodwar->self())
    {
        // Prevent spamming by only running our onFrame once every number of latency frames.
        // Latency frames are the number of frames before commands are processed.
        if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() == 0)
        {
            valid = true;
        }
    }
    return valid;
}

bool auxFun::isUnitDead(list<int> &deadUnits, int id)
{
    bool isDead = false;
    for (auto& unit : deadUnits)
    {
        if (unit == id) 
        {
            return true;
        }
    }
    return isDead;
}

Position auxFun::getMousePosition()
{
    Position myPos(Broodwar->getScreenPosition().x + Broodwar->getMousePosition().x,
                            Broodwar->getScreenPosition().y + Broodwar->getMousePosition().y);
    return myPos;
}

Position auxFun::getUnitPosition(Unit centerHere)
{
    Position myPos(centerHere->getPosition().x - 320,
        centerHere->getPosition().y- 120);
    return myPos;
}

void auxFun::displayInsights2(int roomNeeded, int supplyLeft2, int SCVcount, int barracksCount, int marineCount, int StatsCoordinates[][2], int Builders, int deadUnits,int taskQueueCount, int Unexplored)
{
    //int supplyLeft2 = Broodwar->self()->supplyTotal() - Broodwar->self()->supplyUsed();
    Broodwar->drawTextScreen(StatsCoordinates[0][0], StatsCoordinates[0][1], "FPS: %d", Broodwar->getFPS());
    //Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS());
    //Broodwar->drawTextScreen(StatsCoordinates[1][0], StatsCoordinates[1][1], "Brks: %d", barracksCount);
    Broodwar->drawTextScreen(StatsCoordinates[1][0], StatsCoordinates[1][1], "Tiles to explore: %d", Unexplored);
    //Broodwar->drawTextScreen(StatsCoordinates[2][0], StatsCoordinates[2][1], "Mrn: %d", marineCount);
    //Broodwar->drawTextScreen(StatsCoordinates[3][0], StatsCoordinates[3][1], "SCV: %d", SCVcount);
    //Broodwar->drawTextScreen(StatsCoordinates[4][0], StatsCoordinates[4][1], "Bldrs: %d", Builders);
    Broodwar->drawTextScreen(StatsCoordinates[5][0], StatsCoordinates[5][1], "Dead: %d ", deadUnits);
    //Broodwar->drawTextScreen(StatsCoordinates[6][0], StatsCoordinates[6][1], "Mouse Cursor: %d  %d", Broodwar->getMousePosition().x, Broodwar->getMousePosition().y);
    //Broodwar->drawTextScreen(StatsCoordinates[7][0], StatsCoordinates[7][1], "Screen: %d  %d", Broodwar->getScreenPosition().x, Broodwar->getScreenPosition().y);

    //Broodwar->drawTextScreen(StatsCoordinates[8][0], StatsCoordinates[8][1], "supply limit: %d ", supplyLeft);
    //Broodwar->drawTextScreen(StatsCoordinates[9][0], StatsCoordinates[9][1], "Empty Supply: %d ", supplyLeft2 / 2);
    //Broodwar->drawTextScreen(StatsCoordinates[10][0], StatsCoordinates[10][1], "Room Needed: %d ", roomNeeded / 2);
    //Broodwar->drawTextScreen(StatsCoordinates[11][0], StatsCoordinates[11][1], "Tasks: %d ", taskQueueCount);
    //Broodwar->drawTextScreen(StatsCoordinates[12][0], StatsCoordinates[12][1], "APM: %d ", Broodwar->getAPM());
    //Broodwar->drawTextScreen(StatsCoordinates[13][0], StatsCoordinates[13][1], "FrameCount: %d ", Broodwar->getFrameCount());

}

void auxFun::LeftClick()
{
    INPUT    Input = { 0 };
    // left down 
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));

    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void auxFun::RightClick()
{
    INPUT    Input = { 0 };
    // left down 
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));

    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void MouseMove(int x, int y)
{
    double fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = x * (65535.0f / fScreenWidth);
    double fy = y * (65535.0f / fScreenHeight);
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE;
    //Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    ::SendInput(1, &Input, sizeof(INPUT));
}

