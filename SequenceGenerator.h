#pragma once
#include <cstddef>
#include <Windows.h>
#include "compile_time_definitions.h"

struct SequenceDetails {
	DWORD threadID;
	std::size_t sequnce_score;
	unsigned short creation_order;
	int sequence_addr[SEQUENCE_SIZE];
};

class SequenceGenerator
{

private:
	int* sequence;
	int length;

public:
	SequenceGenerator();
	~SequenceGenerator();
	int* shuffleSequence();
	static void printSequence(int*, std::size_t);
};

