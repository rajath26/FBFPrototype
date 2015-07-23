/*
 * Driver.h
 *
 *  Created on: Nov 27, 2014
 *      Author: rajatsub
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "Common.h"
#include<chrono>
#include "Results.h"

/*
 * FBF classes
 */
#include "FBF.h"
#include "RecycleBloomFilter.h"

/*
 * Timer class
 */
#include "Timer.h"

/*
 * Trace class
 */
#include "Trace.h"

/*
 * Macros
 */
#define SLEEP_TIME 2
#define DEF_NUM_INSERTS 2000
#define DEF_TABLE_SIZE 6250
#define LARGE_TABLE_SIZE 12500
#define DEF_NUM_OF_HASH 5
#define DEF_REFRESH_RATE 5
#define DEF_BATCH_OPS 200
#define DEF_NUM_INVALIDS 2500
#define SIMPLE_FBF 3
#define MAX_TOLERABLE_FPR 0.001
#define SIMPLE_FBF 3

using namespace std;

/*
 * Global variables
 */
Trace trace;
enum testcase {smartVsDumbTestCase, numElementsTestCase, BFsizeTestCase, numHashesTestCase, refreshRateTestCase, numBloomFiltersTestCase, dynamicResizingTestCase, recyclableBloomFilterTestCase};

/*
 * Function declaration
 */
void usage(string);

/**
 * CLASS NAME: Driver
 *
 * DESCRIPTION: This class is main driver class that drives the experiments
 */
class Driver {
public:
	Driver();
	void dumbVsSmartMembershipCheck(testcase t,
									unsigned long numberOfBFs,
									unsigned long long int numElements,
									unsigned long long int tableSize,
									unsigned int numOfHashes,
									unsigned long refreshRate,
									unsigned long long int batchOps,
									testType test,
									unsigned long long int numberOfInvalids,
								    vector<Results *> resultsVector);
	void FPRMethodsAnalysis(testcase t,
			                unsigned long numberOfBFs,
						   unsigned long long int numElements,
						   unsigned long long int tableSize,
						   unsigned int numOfHashes,
						   unsigned long refreshRate,
						   unsigned long long int batchOps,
						   testType test,
						   unsigned long long int numberOfInvalids,
						   vector<Results *> resultsVector);
	void opsPerSecTests(testcase t,
							    unsigned long numberOfBFs,
								unsigned long long int numElements,
	                            unsigned long long int tableSize,
								unsigned int numOfHashes,
								unsigned long refreshRate,
								unsigned long long int batchOps,
								testType test,
								unsigned long long int numberOfInvalids,
								vector<Results *> resultsVector);
	void dynamicResizing(unsigned long long int numElements,
					    unsigned long long int tableSize,
					    unsigned int numOfHashes,
					    unsigned long initialRefreshRate,
					    unsigned long long int batchOps,
					    vector<Results *> resultsVector);
	void recyclableBloomFilterRun(unsigned long long int numElements,
								  unsigned long long int tableSize,
								  unsigned int numOfHashes,
								  unsigned long long int batchOps,
								  vector<Results *> resultsVector);
	void dumbVsSmartMemTest();
	void varyNumElements();
	void varyBFsize();
	void varyHashes();
	void varyRefreshRate();
	void varyConstituentBFNumbers();
	void dynamicResizingExperiment();
	void recyclableBloomFilterExperiment();
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
