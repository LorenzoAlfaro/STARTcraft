#pragma once
#include <BWAPI.h>
//#include "UnitFun.h"
//#include "CommMngr.h"
//#include "auxFun.h"
#include "TaskFun.h"
#include "TaskEngine.h"
#include "ProductionManager.h"
#include "FileIO.h"
#include "UserInterface.h"
#include "Walker.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;
using namespace UnitTypes;

// Remember not to use "Broodwar" in any global class constructor!

class ExampleAIModule : public BWAPI::AIModule
{
public:
  // Virtual functions for callbacks, leave these as they are.
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual void onSendText(std::string text);
  virtual void onReceiveText(BWAPI::Player player, std::string text);
  virtual void onPlayerLeft(BWAPI::Player player);
  virtual void onNukeDetect(BWAPI::Position target);
  virtual void onUnitDiscover(BWAPI::Unit unit);
  virtual void onUnitEvade(BWAPI::Unit unit);
  virtual void onUnitShow(BWAPI::Unit unit);
  virtual void onUnitHide(BWAPI::Unit unit);
  virtual void onUnitCreate(BWAPI::Unit unit);
  virtual void onUnitDestroy(BWAPI::Unit unit);
  virtual void onUnitMorph(BWAPI::Unit unit);
  virtual void onUnitRenegade(BWAPI::Unit unit);
  virtual void onSaveGame(std::string gameName);
  virtual void onUnitComplete(BWAPI::Unit unit);
  // Everything below this line is safe to modify.
  list<array<int, 12>>  taskQueue;                 //0=TS,1=Delay,2=Action,3=UID,4=Owner,5=Status,6=ID,7=X,8=Y,9=Mineral,10=Gas,11=Time
  list<int>             Miners;
  list<int>             Builders;
  list<int>             deadUnits;
  int                   StatsCoordinates[14][2];                      //used to set the display metrics
  int                   maxUnit[2] = { 50, 150 };                 //SCV,Marines, Medics, etc
  int                   maxBuilding[3] = { 3, 20, 4 };                //CC, supplydepots, barracks
  int                   TaskCount = 0;                                //unique Task ID
  bool                  displayStats = true;
  bool                  busy = false;
  int                   callBack = 0;
  Unit					JimRaynor;
  list<TilePosition>  Unexplored; //Walkable options
};
