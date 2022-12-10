#pragma once
#include <cstddef>
#include "SequenceGenerator.h"
#include <Windows.h>

class MatchEngine
{
private:
	bool isBeforeIndex(int*, int, std::size_t);
	bool isAfterIndex(int*, int, std::size_t);

public:
	std::size_t maximum_score;
	int best_sequence[SEQUENCE_SIZE];
	MatchEngine();
	void matchAgainst(int*, int**);
	void overwriteMaximum(int*, std::size_t);
};

