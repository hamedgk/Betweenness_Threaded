#include "SequenceGenerator.h"
#include <random>
#include <chrono>
#include <iostream>


SequenceGenerator::SequenceGenerator() {
	int* buf_sequence = new int[100];

	for (int i = 0; i < 100; ++i)
		buf_sequence[i] = i;

	this->sequence = buf_sequence;
	this->length = 100;
}

//TODO: handle deacllocation
int* SequenceGenerator::shuffleSequence() {
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(sequence, sequence+100, std::default_random_engine(seed));

	return sequence;
}

void SequenceGenerator::printSequence(int* sequence, std::size_t rules_count) {
	std::cout << "{";
	int i;
	for (i = 0; i < rules_count-1; ++i) {
		std::cout << sequence[i] << ", ";
	}
	std::cout << sequence[i] << "}" << std::endl;
}

