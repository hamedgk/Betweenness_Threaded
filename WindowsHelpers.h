#pragma once
#include <map>
#include "SequenceGenerator.h"

class WindowsHelpers
{
public:
	static int* openSharedMemory();
	static SequenceDetails* createResultsSharedMemory();
	static SequenceDetails* openResultsSharedMemory();
	static int systemCpuCount();
};

