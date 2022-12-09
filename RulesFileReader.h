#pragma once
#include <fstream>
#include <Windows.h>
#include "compile_time_definitions.h"

class RulesFileReader
{
public:
	RulesFileReader(char const *);
	int** parseRules();
	int* allocateSharedWindowsMemory();
	static void printRules(int**);
	static void printRulesOneDimension(int*);
	void deallocateRulesBuffer();

private:
	void allocateRulesBuffer();
	int** betweenness_data_set;
	std::ifstream rules_file;
};

