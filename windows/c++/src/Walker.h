#pragma once
#include <BWAPI.h>
#include "UnitFun.h"
#include "TaskEngine.h"
#include "ExampleAIModule.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
using namespace Filter;
using namespace std;
using namespace BWAPI;
class Walker
{
public:

	static void Walk(Unit myUnit, bool Attack,int frameCount, int& callBack, list<TilePosition>& Unexplored);
	static void moveRight(Unit myUnit, bool Attack);
	static void moveLeft(Unit myUnit, bool Attack);
	static void moveUp(Unit myUnit, bool Attack);
	static void moveDown(Unit myUnit, bool Attack);
	static void moveToPosition(Unit myUnit, bool Attack, Position moveHere);

};

