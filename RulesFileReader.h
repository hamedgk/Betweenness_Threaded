#pragma once
#include <fstream>
#include <Windows.h>
#include "compile_time_definitions.h"

class RulesFileReader
{
public:
	RulesFileReader(char const *);
	int** parseRules();
	static void printRules(int**);
	void close();

private:
	void allocateRulesBuffer();
	int** betweenness_data_set;
	std::ifstream rules_file;
};

