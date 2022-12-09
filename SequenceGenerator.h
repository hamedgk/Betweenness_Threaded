#pragma once
#include <cstddef>
#include <Windows.h>

struct SequenceDetails {
	DWORD threadID;
	std::size_t sequnce_score;
	unsigned short creation_order;
	int sequence_addr[100];
};

class SequenceGenerator
{

private:
	int* sequence;
	int length;

public:
	SequenceGenerator();
	int* shuffleSequence();
	static void printSequence(int*, std::size_t);
};

