#include "MatchEngine.h"
#include "compile_time_definitions.h"	
#include "SequenceGenerator.h"
#include <iostream>



MatchEngine::MatchEngine() {
	maximum_score = 0;
}

void MatchEngine::matchAgainst(int* sequence, int** rules) {
	std::size_t score = 0;
	for (int i = 0; i < RULES_COUNT; i++) {
		for (int j = 0; j < 100; j++) {
			if (rules[i][1] == sequence[j]) {
				if (
					(isBeforeIndex(sequence, rules[i][0], j) && isAfterIndex(sequence, rules[i][2], j)) ||
					(isBeforeIndex(sequence, rules[i][2], j) && isAfterIndex(sequence, rules[i][0], j))
					) {
					score++;
					break;
				}
			}
		}
	}
	overwriteMaximum(sequence, score);
	score = 0;
}



inline bool MatchEngine::isBeforeIndex(int* sequence, int number, std::size_t index) {
	for (int i = 0; i < index; ++i) {
		if (number == sequence[i])
			return true;
	}
	return false;
}


inline bool MatchEngine::isAfterIndex(int* sequence, int number, std::size_t index) {
	for (int i = index + 1; i < 100; ++i) {
		if (number == sequence[i])
			return true;
	}
	return false;
}

inline void MatchEngine::overwriteMaximum(int* sequence, std::size_t number) {
	if (maximum_score < number) {
		maximum_score = number;
		//best_sequence = sequence;
		for (int i = 0; i < 100; ++i) {
			best_sequence[i] = sequence[i];
		}
	}
}
