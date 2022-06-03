#pragma once
#include <BWAPI.h>
#include "UnitFun.h"
using namespace Filter;
using namespace std;
using namespace BWAPI;


class CommMngr
{
	public:
		static void attackUnits(std::list<Unit> units, Position myPos);
		static void moveUnits(std::list<Unit> units, Position myPos);
		static void setRallyPoint(std::list<Unit> buildings, Position myPos);
		static void scvManager(std::list<int> Miners);
		static void buildSCVs(std::list<Unit> commandCenters);
		static void trainMarines(std::list<Unit> barracks);

};

