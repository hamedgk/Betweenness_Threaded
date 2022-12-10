
#include <iostream>
#include "RulesFileReader.h"
#include "SequenceGenerator.h"
#include "WindowsHelpers.h"
#include "MatchEngine.h"

struct PackedData {
	SequenceDetails* sequence_details_addr;
	int** rules_addr;
	int iteration;
};

DWORD WINAPI calculateBetweenness(LPVOID Param)
{
	auto global_data = (PackedData*) Param;
	auto cpu_count = WindowsHelpers::systemCpuCount();

	auto sequence_generator = SequenceGenerator();
	auto match_engine = MatchEngine();
	for (int i = 0; i < global_data->iteration; ++i)
	{
		int* sg = sequence_generator.shuffleSequence();
		match_engine.matchAgainst(sg, global_data->rules_addr);
	}

	for (int i = 0; i < cpu_count; ++i) {
		if (global_data->sequence_details_addr[i].threadID == GetCurrentThreadId()) {
			global_data->sequence_details_addr[i].sequnce_score = match_engine.maximum_score;
			for (int j = 0; j < SEQUENCE_SIZE; ++j) {
				global_data->sequence_details_addr[i].sequence_addr[j] = match_engine.best_sequence[j];
			}
			//don't invade other cpu cores space
			break;
		}
	}
	return 0;
}

int main()
{
	RulesFileReader rules = RulesFileReader(RULES_PATH);
	auto rules_dataset = rules.parseRules();
	int cpu_count = WindowsHelpers::systemCpuCount();
	DWORD* thread_IDs = new DWORD[cpu_count];
	HANDLE* hThreadArray = new HANDLE[cpu_count];

	auto results = new SequenceDetails[cpu_count];


	PackedData* packed_data = new PackedData;
	packed_data->rules_addr = rules_dataset;
	packed_data->sequence_details_addr = results;
	packed_data->iteration = 100000;

	for (int i = 0; i < cpu_count; ++i) {
		// Start the child process.
		hThreadArray[i] = CreateThread(NULL, 0, calculateBetweenness, packed_data, 0, &thread_IDs[i]);
		if (!hThreadArray[i])
		{
			std::cerr << "Create Process failed at CPU: " << i << std::endl;
			return 1;
		}
		results[i].threadID = thread_IDs[i];
		results[i].creation_order = i;
	}


	for (int i = 0; i < cpu_count; ++i) {
		// Wait until child process exits.
		WaitForSingleObject(hThreadArray[i], INFINITE);
		std::cout << "THREAD " << thread_IDs[i] << " COMPLETED!" << std::endl;
	}


	for (int i = 0; i < cpu_count; ++i) {

		// Close process and thread handles. 
		CloseHandle(hThreadArray[i]);
	}

	//compare results
	for (int i = 0; i < cpu_count; ++i) {
		std::cout << "thread ID: " << results[i].threadID << std::endl;
		std::cout << "score: " << results[i].sequnce_score << std::endl;
		std::cout << "creation order: " << results[i].creation_order << std::endl;
		std::cout << std::endl;
	}

	SequenceDetails* best = NULL;
	std::size_t max_score = 0;

	for (int i = 0; i < cpu_count; ++i) {
		if (results[i].sequnce_score > max_score) {
			max_score = results[i].sequnce_score;
			best = &results[i];
		}
	}

	if (!best) exit(1);
	std::cout << "\n==========================================" << std::endl;
	std::cout << "best child is:" << std::endl;
	std::cout << "process ID: " << best->threadID << std::endl;
	std::cout << "score: " << best->sequnce_score << std::endl;
	std::cout << "creation order: " << best->creation_order << std::endl;
	SequenceGenerator::printSequence(best->sequence_addr, SEQUENCE_SIZE);

	rules.close();
	delete[] thread_IDs;
	delete[] hThreadArray;
}

