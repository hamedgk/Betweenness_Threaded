#include "RulesFileReader.h"
#include "compile_time_definitions.h"
#include <iostream>
#include <Windows.h>

RulesFileReader::RulesFileReader(char const* file_path) {
	//initialize data_set
	betweenness_data_set = NULL; 

	rules_file.open(file_path);
	if (!rules_file.is_open()) {
		std::cerr << "specified file not found!";
		rules_file.close();
		exit(1);
	}
}

void RulesFileReader::close() {
	if (!betweenness_data_set)
		return;

	for (int i = 0; i < RULES_COUNT; ++i) {
		delete[] betweenness_data_set[i];
	}
	delete betweenness_data_set;

	//set it back to default state
	betweenness_data_set = NULL;
	rules_file.close();
}

void RulesFileReader::allocateRulesBuffer() {
	betweenness_data_set = new int* [RULES_COUNT];

	for (int i = 0; i < RULES_COUNT; ++i) {
		betweenness_data_set[i] = new int[3];
	}
}


void RulesFileReader::printRules(int** betweenness_data_set) {
	if (!betweenness_data_set) {
		std::cerr << "data set is empty or not initialized.." << std::endl;
		return;
	}

	for (int column = 0; column < RULES_COUNT; column++) {
		std::cout << "["
			<< betweenness_data_set[column][0]
			<< ", "
			<< betweenness_data_set[column][1]
			<< ", "
			<< betweenness_data_set[column][2]
			<< "]"
			<< std::endl;
	}


}


int** RulesFileReader::parseRules() {
	allocateRulesBuffer();

	for (int column = 0; column < RULES_COUNT; column++)
		rules_file >> betweenness_data_set[column][0] >> betweenness_data_set[column][1] >> betweenness_data_set[column][2];

	return betweenness_data_set;
}

