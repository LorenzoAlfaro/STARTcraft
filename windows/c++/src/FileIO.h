#pragma once
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <BWAPI.h>


using namespace std;
class FileIO
{
public:
	static bool readStatsCoordinates(int StatsCoordinates[][2]);

	static void FileIO::WriteHeaders();
};

