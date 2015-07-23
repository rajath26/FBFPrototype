/*
 * Driver.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: rajatsub
 */

#include "Driver.h"

/**
 * Constructor
 */
Driver::Driver() {
	trace.funcEntry("Driver::Driver");
	trace.funcExit("Driver::Driver");
}

/**
 * Destructor
 */
Driver::~Driver() {
	trace.funcEntry("Driver::~Driver");
	trace.funcExit("Driver::~Driver");
}

/***********************************************************************
 * FUNCTION NAME: dumbVsSmartMembershipCheck
 *
 * DESCRIPTION: This function compares the false positive rate (FPR) calculated using
 * 				using smart membership check that leverages the traits of an FBF
 * 				versus a dumb membership check that sees the FBF as a naive union
 * 				of Bloom filters
 *
 * PARAMETERS:
 *  		  testcase: This specifies which testcase this function is running:
 *  		  			1) Number of elements variance
 *  		  			2) Filter size variance
 *  		  			3) Number of hash functions variance
 * 			  numberOfBFs: Number of constituent bloom filters in the FBF
 *            numElements: Number of elements to be inserted into the
 *                         FBF
 *            tableSize: constituent BFs size i.e. number of bits
 *            numOfHashes: Number of hashes in each constituent BFs in
 *                         FBF
 *            refreshRate: time in seconds after which the FBF is
 *                         refreshed
 *            batchOps: number of inserts after which a sleep should be
 *                      induced to simulate real world scenario
 *            testType: For calculating false positive probability emperically,
 *            			this parameter mentions whether it should do so by:
 *            			1) number of total invalid key tries OR
 *            			2) try until you get number of false positives
 *            numberOfInvalids: number of false positives to be found
 *            resultsVector: vector holding pointers to Results objects
 ***********************************************************************/
void Driver::dumbVsSmartMembershipCheck(testcase t,
		                       unsigned long numberOfBFs,
							   unsigned long long int numElements,
							   unsigned long long int tableSize,
							   unsigned int numOfHashes,
							   unsigned long refreshRate,
							   unsigned long long int batchOps,
							   testType test,
							   unsigned long long int numberOfInvalids,
							   vector<Results *> resultsVector) {
	trace.funcEntry("Driver::dumbVsSmartMembershipCheck");
	cout<<" ----------------------------------------------------------- " <<endl;
	cout<<" INFO :: Test Execution Info " <<endl;
	cout<<" INFO :: NUMBER OF ELEMENTS: " <<numElements <<endl;
	// Table size and number of hash functions printed by compute_optimal function
	// in FBF constructor. Dont print here
	cout<<" INFO :: REFRESH RATE: " <<refreshRate <<endl;
	cout<<" INFO :: BATCH OPERATIONS: " <<batchOps <<endl;

	unsigned long long int i;

	/*
	* STEP 1: Create the FBF
	*/
	FBF simpleFBF(numberOfBFs, tableSize, numOfHashes, refreshRate, MAX_TOLERABLE_FPR, false);

	/*
	 * STEP 2: Insert some numbers into the FBF
	 */
	for ( i = 0; i < numElements; i++ ) {
		 //For every batch operations done induce some sleep time
		if ( 0 == i % batchOps ) {
			this_thread::sleep_for(chrono::seconds(SLEEP_TIME));
		}
		//Insert number into the FBF
		simpleFBF.insert(i);
	} // End of for that inserts elements into the FBF

	cout<<endl<<"Finished inserting test elements";
	cout<<endl<<"Stopping FBF threads";
	simpleFBF.stopThreads();

	/*
	 * STEP 3: Check for False Positives (FPs) using smart rules
	 */
	double smartFPR = simpleFBF.checkSmartFBF_FPR(numberOfInvalids, test);
	resultsVector[0]->numElementsVsFPR(numElements, smartFPR);

	/*
	 * STEP 4: Check for False Positives (FPs) using dumb rules
	 */
	double dumbFPR = simpleFBF.checkDumbFBF_FPR(numberOfInvalids, test);
	resultsVector[1]->numElementsVsFPR(numElements, dumbFPR);

	cout<<" -----------------------------------------------------------" <<endl <<endl;
	trace.funcExit("Driver::dumbVsSmartMembershipCheck");
} // End of dumbVsSmartMembershipCheck()

/***********************************************************************
 * FUNCTION NAME: FPRMethodsAnalysis
 *
 * DESCRIPTION: This function compares the false positive rate (FPR) calculated using
 * 				different strategies with variance in number of elements /
 * 				constituent bloom filter size / number of hash functions
 *
 * PARAMETERS:
 *  		  testcase: This specifies which testcase this function is running:
 *  		  			1) Number of elements variance
 *  		  			2) Filter size variance
 *  		  			3) Number of hash functions variance
 * 			  numberOfBFs: Number of constituent bloom filters in the FBF
 *            numElements: Number of elements to be inserted into the
 *                         FBF
 *            tableSize: constituent BFs size i.e. number of bits
 *            numOfHashes: Number of hashes in each constituent BFs in
 *                         FBF
 *            refreshRate: time in seconds after which the FBF is
 *                         refreshed
 *            batchOps: number of inserts after which a sleep should be
 *                      induced to simulate real world scenario
 *            testType: For calculating false positive probability emperically,
 *            			this parameter mentions whether it should do so by:
 *            			1) number of total invalid key tries OR
 *            			2) try until you get number of false positives
 *            numberOfInvalids: number of false positives to be found
 *            resultsVector: vector holding pointers to Results objects
 ***********************************************************************/
void Driver::FPRMethodsAnalysis(testcase t,
		                       unsigned long numberOfBFs,
							   unsigned long long int numElements,
							   unsigned long long int tableSize,
							   unsigned int numOfHashes,
							   unsigned long refreshRate,
							   unsigned long long int batchOps,
							   testType test,
							   unsigned long long int numberOfInvalids,
							   vector<Results *> resultsVector) {
	trace.funcEntry("Driver::FPRMethodsAnalysis");
	cout<<" ----------------------------------------------------------- " <<endl;
	cout<<" INFO :: Test Execution Info " <<endl;
	cout<<" INFO :: NUMBER OF ELEMENTS: " <<numElements <<endl;
	// Table size and number of hash functions printed by compute_optimal function
	// in FBF constructor. Dont print here
	cout<<" INFO :: REFRESH RATE: " <<refreshRate <<endl;
	cout<<" INFO :: BATCH OPERATIONS: " <<batchOps <<endl;

	unsigned long long int i;

	/*
	* STEP 1: Create the FBF
	*/
	FBF simpleFBF(numberOfBFs, tableSize, numOfHashes, refreshRate, MAX_TOLERABLE_FPR, false);

	/*
	 * STEP 2: Insert some numbers into the FBF
	 */
	for ( i = 0; i < numElements; i++ ) {
		 //For every batch operations done induce some sleep time
		if ( 0 == i % batchOps ) {
			this_thread::sleep_for(chrono::seconds(SLEEP_TIME));
		}
		//Insert number into the FBF
		simpleFBF.insert(i);
	} // End of for that inserts elements into the FBF

	cout<<endl<<"Finished inserting test elements";
	cout<<endl<<"Stopping FBF threads";
	simpleFBF.stopThreads();

	/*
	 * STEP 3: Check for False Positives (FPs) using smart rules
	 */
	double smartFPR = simpleFBF.checkSmartFBF_FPR(numberOfInvalids, test);
	if ( t == numElementsTestCase ) {
		resultsVector[0]->numElementsVsFPR(numElements, smartFPR);
	}
	else if ( t == BFsizeTestCase ) {
		resultsVector[0]->BFsizeVSFPR(tableSize, smartFPR);
	}
	else if ( t == numHashesTestCase ) {
		resultsVector[0]->numHashesVSFPR(numOfHashes, smartFPR);
	}

	/*
	 * STEP 4: Check for False Positives (FPs) using dumb rules
	 */
	//simpleFBF.checkDumbFBF_FPR(numberOfInvalids);

	/*
	 * STEP 5: Check the False Positives (FPs) using conditional probability
	 */
	double effectiveFPR = simpleFBF.checkEffectiveFPR();
	if ( t == numElementsTestCase ) {
		resultsVector[1]->numElementsVsFPR(numElements, effectiveFPR);
	}
	else if ( t == BFsizeTestCase ) {
		resultsVector[1]->BFsizeVSFPR(tableSize, effectiveFPR);
	}
	else if ( t == numHashesTestCase ) {
			resultsVector[1]->numHashesVSFPR(numOfHashes, effectiveFPR);
		}

	/*
	 * STEP 6: Check the False Positive Rate (FPR) using FBF analysis
	 */
	double fbfAnalysisFPR = simpleFBF.fbfAnalysis();
	if ( t == numElementsTestCase ) {
		resultsVector[2]->numElementsVsFPR(numElements, fbfAnalysisFPR);
	}
	else if ( t == BFsizeTestCase ) {
		resultsVector[2]->BFsizeVSFPR(tableSize, fbfAnalysisFPR);
	}
	else if ( t == numHashesTestCase ) {
		resultsVector[2]->numHashesVSFPR(numOfHashes, fbfAnalysisFPR);
	}

	cout<<" -----------------------------------------------------------" <<endl <<endl;
	trace.funcExit("Driver::FPRMethodsAnalysis");
} // End of FPRMethodsAnalysis()

/******************************************************************************
 * FUNCTION NAME: opsPerSecTests
 *
 * DESCRIPTION: This function maps the false positive rate for a given refresh
 *              rate / number of bloom filters and also keeps a tab on the
 *              operations per second
 *
 * PARAMETERS:
 *  		  testcase: This specifies which testcase this function is running:
 *  		  			1) Refresh rate variance
 *  		  			2) Number of bloom filters variance
 * 			  numberOfBFs: Number of constituent bloom filters in the FBF
 *            numElements: Number of elements to be inserted into the
 *                         FBF
 *            tableSize: constituent BFs size i.e. number of bits
 *            numOfHashes: Number of hashes in each constituent BFs in
 *                         FBF
 *            refreshRate: time in seconds after which the FBF is
 *                         refreshed
 *            batchOps: number of inserts after which a sleep should be
 *                      induced to simulate real world scenario
 *            testType: For calculating false positive probability emperically,
 *            			this parameter mentions whether it should do so by:
 *            			1) number of total invalid key tries OR
 *            			2) try until you get number of false positives
 *            numberOfInvalids: number of false positives to be found
 *            resultsVector: vector holding pointers to Results objects
 ******************************************************************************/
void Driver::opsPerSecTests(testcase t,
		                    unsigned long numberOfBFs,
							unsigned long long int numElements,
							unsigned long long int tableSize,
							unsigned int numOfHashes,
							unsigned long refreshRate,
							unsigned long long int batchOps,
							testType test,
							unsigned long long int numberOfInvalids,
							vector<Results *> resultsVector) {
	trace.funcEntry("Driver::opsPerSecTests");
	cout<<" ----------------------------------------------------------- " <<endl;
	cout<<" INFO :: Test Execution Info " <<endl;
	cout<<" INFO :: NUMBER OF ELEMENTS: " <<numElements <<endl;
	// Table size and number of hash functions printed by compute_optimal function
	// in FBF constructor. Dont print here nnnnnn
	cout<<" INFO :: REFRESH RATE: " <<refreshRate <<endl;
	cout<<" INFO :: BATCH OPERATIONS: " <<batchOps <<endl;

	unsigned long long int i;
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsedSeconds;
	double opsPerSecond = 0.0;

	/*
	* STEP 1: CREATE THE FBF
	*/
	FBF simpleFBF(numberOfBFs, tableSize, numOfHashes, refreshRate, MAX_TOLERABLE_FPR, false);

	/*
	 * STEP 2: Insert some numbers into the FBF
	 */
	start = chrono::system_clock::now();
	for ( i = 0; i < numElements; i++ ) {
		 // For every batch operations done induce some
		if ( 0 == i % batchOps ) {
			this_thread::sleep_for(chrono::seconds(SLEEP_TIME));
		}

		// Insert number into the FBF
		simpleFBF.insert(i);
	} // End of for that inserts elements into the FBF

	/*
     * STEP 3: Measure the operations per second done
	 */
	end = chrono::system_clock::now();
	elapsedSeconds = end - start;
	opsPerSecond = (double)numElements / elapsedSeconds.count();
	cout<<endl<<"Finished inserting test elements";
	cout<<endl<<"Stopping FBF threads";
	simpleFBF.stopThreads();

	cout<<" INFO :: Time elapsed in for loop: " <<elapsedSeconds.count() <<endl;
	cout<<" INFO :: Rate of insertion: " <<opsPerSecond <<" per second" <<endl;

	/*
	 * STEP 4: Check for FPR using smart rules
	 */
	/*
	double smartFPR = simpleFBF.checkSmartFBF_FPR(numberOfInvalids, test);
	if ( t == refreshRateTestCase ) {
		resultsVector[0]->refreshRateOpsPerSecondFPR(refreshRate, opsPerSecond, smartFPR);
	}
	else if ( t == numBloomFiltersTestCase ) {
		resultsVector[0]->refreshRateOpsPerSecondFPR(numberOfBFs, opsPerSecond, smartFPR);
	}
	*/

	/*
	 * STEP 5: Check FPR using conditional probability
	 */
	double effectiveFPR = simpleFBF.checkEffectiveFPR();
	if ( t == refreshRateTestCase ) {
		resultsVector[1]->refreshRateOpsPerSecondFPR(refreshRate, opsPerSecond, effectiveFPR);
	}
	else if ( t == numBloomFiltersTestCase ) {
		resultsVector[1]->refreshRateOpsPerSecondFPR(numberOfBFs, opsPerSecond, effectiveFPR);
	}

	/*
	 * STEP 6: Check the FPR using FBF analysis
	 */
	/*
	if ( t == refreshRateTestCase ) {
		double fbfAnalysisFPR = simpleFBF.fbfAnalysis();
		resultsVector[2]->refreshRateOpsPerSecondFPR(refreshRate, opsPerSecond, fbfAnalysisFPR);
	}
	*/

	cout<<" -----------------------------------------------------------" <<endl <<endl;
	trace.funcExit("Driver::opsPerSecTests");
}

/***********************************************************************
 * FUNCTION NAME: dynamicResizing
 *
 * DESCRIPTION: This function compares the false positive rate (FPR) calculated using
 * 				different strategies with variance in number of elements /
 * 				constituent bloom filter size / number of hash functions
 *
 * PARAMETERS:
 *  		  testcase: This specifies which testcase this function is running:
 *  		  			1) Number of elements variance
 *  		  			2) Filter size variance
 *  		  			3) Number of hash functions variance
 * 			  numberOfBFs: Number of constituent bloom filters in the FBF
 *            numElements: Number of elements to be inserted into the
 *                         FBF
 *            tableSize: constituent BFs size i.e. number of bits
 *            numOfHashes: Number of hashes in each constituent BFs in
 *                         FBF
 *            refreshRate: time in seconds after which the FBF is
 *                         refreshed
 *            batchOps: number of inserts after which a sleep should be
 *                      induced to simulate real world scenario
 *            testType: For calculating false positive probability emperically,
 *            			this parameter mentions whether it should do so by:
 *            			1) number of total invalid key tries OR
 *            			2) try until you get number of false positives
 *            numberOfInvalids: number of false positives to be found
 *            resultsVector: vector holding pointers to Results objects
 ***********************************************************************/
void Driver::dynamicResizing(unsigned long long int numElements,
						     unsigned long long int tableSize,
						     unsigned int numOfHashes,
						     unsigned long initialRefreshRate,
						     unsigned long long int batchOps,
						     vector<Results *> resultsVector) {
	trace.funcEntry("Driver::dynamicResizing");
	cout<<" ----------------------------------------------------------- " <<endl;
	cout<<" INFO :: Test Execution Info " <<endl;
	cout<<" INFO :: NUMBER OF ELEMENTS: " <<numElements <<endl;
	// Table size and number of hash functions printed by compute_optimal function
	// in FBF constructor. Dont print here
	cout<<" INFO :: INITIAL REFRESH RATE: " <<initialRefreshRate <<endl;
	cout<<" INFO :: BATCH OPERATIONS: " <<batchOps <<endl;

	std::array<int,4> random_time;
	random_time[0]=3;random_time[1]=3;random_time[2]=2;random_time[3]=2;
	unsigned long long int i;
	chrono::time_point<chrono::system_clock> starT, end;
	chrono::duration<double> elapsedSeconds;
	//double opsPerSecond = 0.0;
	//unsigned int frequency_results=2;

	string target="TARGET,"+to_string(MAX_TOLERABLE_FPR);
	resultsVector[0]->writeTestParameters(target);
	/*
	* STEP 1: Create the FBF
	*/
	FBF dynFBF(SIMPLE_FBF, tableSize, numOfHashes, initialRefreshRate, MAX_TOLERABLE_FPR, true);

	/*
	 * STEP 2: Insert some numbers into the FBF
	 */
	//for ( int j = 0; j < step; j++ ) {
		starT = chrono::system_clock::now();
		//std::cout<<std::endl<<"start:"<<startT<<std::endl;
		for ( i = 0; i < numElements; i++ ) {
			 //For every batch operations done induce some sleep time
			if ( 0 == i % batchOps && i != 0) {
				/*end = chrono::system_clock::now();
				elapsedSeconds = end - starT;
				resultsVector[0]->dynResizingRecord(elapsedSeconds.count(), dynFBF.checkEffectiveFPR(), dynFBF.getRefreshRate(), dynFBF.getPastEnd()+1);*/
				srand(time(NULL));
				size_t sz = random_time.size();
				this_thread::sleep_for(chrono::seconds(random_time[rand()%sz]));
			}

			//if ( 0 == i % frequency_results && i != 0 ) {
				end = chrono::system_clock::now();
				elapsedSeconds = end - starT;
				resultsVector[0]->dynResizingRecord(elapsedSeconds.count(), dynFBF.checkEffectiveFPR(), dynFBF.getRefreshRate(), dynFBF.getPastEnd()+1);
				//end = chrono::system_clock::now();
				//std::cout<<std::endl<<"end:"<<end<<std::endl;
				//elapsedSeconds = end - starT;
				/*std::cout<<std::endl<<"Elapsed seconds are: "<<elapsedSeconds.count()<<std::endl;
				std::cout<<std::endl<<"Operations completed: "<<i<<std::endl;*/
				//opsPerSecond = (double)i / elapsedSeconds.count();
				//std::cout<<std::endl<<"Operations per second: "<<opsPerSecond<<std::endl;
				//cout<<endl<<"in driver: "<<dynFBF.getRefreshRate();
				//resultsVector[0]->dynResizingRecord(elapsedSeconds.count(), dynFBF.checkEffectiveFPR(), dynFBF.getRefreshRate(), dynFBF.getPastEnd()+1);
			//}
			//Insert number into the FBF
			dynFBF.insert(i);
		} // End of for that inserts elements into the FBF
	//}
	cout<<" -----------------------------------------------------------" <<endl <<endl;
	trace.funcExit("Driver::dynamicResizing");
} // End of dynamicResizing()

/***********************************************************************
 * FUNCTION NAME: recyclableBloomFilterRun
 *
 * DESCRIPTION: This function compares runs the recyclable Bloom Filter simulation run
 *
 * PARAMETERS:
 *            numElements: Number of elements to be inserted into the
 *                         FBF
 *            tableSize: constituent BFs size i.e. number of bits
 *            numOfHashes: Number of hashes in each constituent BFs in
 *                         FBF
 *            refreshRate: time in seconds after which the FBF is
 *                         refreshed
 *            batchOps: number of inserts after which a sleep should be
 *                      induced to simulate real world scenario
 *            resultsVector: vector holding pointers to Results objects
 ***********************************************************************/
void Driver::recyclableBloomFilterRun(unsigned long long int numElements,
								  unsigned long long int tableSize,
								  unsigned int numOfHashes,
								  unsigned long long int batchOps,
								  vector<Results *> resultsVector) {
	trace.funcEntry("Driver::recyclableBloomFilterRun");
	cout<<" ----------------------------------------------------------- " <<endl;
	cout<<" INFO :: Test Execution Info " <<endl;
	cout<<" INFO :: NUMBER OF ELEMENTS: " <<numElements <<endl;
	// Table size and number of hash functions printed by compute_optimal function
	// in FBF constructor. Dont print here
	cout<<" INFO :: BATCH OPERATIONS: " <<batchOps <<endl;

	unsigned int i;

	/*
	 * STEP 1: Create the recyclable Bloom Filter
	 */
	RecycleBloomFilter rBF(tableSize, numOfHashes, MAX_TOLERABLE_FPR);

	/*
	 * STEP 2: Insert some elements into the FBF
	 */
	for ( i = 0; i < numElements; i++ ) {
		 //For every batch operations done induce some sleep time
		if ( 0 == i % batchOps ) {
			this_thread::sleep_for(chrono::seconds(SLEEP_TIME));
		}
		//Insert number into the FBF
		rBF.insert(i);
	} // End of for that inserts elements into the recyclable BF

	cout<<endl<<"Finished inserting test elements";
	cout<<endl<<"Stopping FBF threads"<<std::endl;
	rBF.stopThreads();

	trace.funcExit("Driver::recyclableBloomFilterRun");
} // End of recyclableBloomFilterRun()

/******************************************************************************
 * FUNCTION NAME: dumbVsSmartMemTest
 *
 * DESCRIPTION: This function runs the test case where the number of elements are varied
 * 				ie increased while the constituent BF size and the number of hash functions
 * 				are kept constant. The insertion rate is also kept constant.The smart
 * 				membership check is compared with dumb membership check
 ******************************************************************************/
void Driver::dumbVsSmartMemTest() {
	trace.funcEntry("Driver::dumbVsSmartMemTest");
	string test = "dumbVsSmartMemTest" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartMemCheckFPR", test);
	Results * dumbFPR = new Results("dumbmemCheckFPR", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(dumbFPR);

	int numElements = 100;
	int increments = 100;
	int batch = 75;
	testType testT = numberOfTrials;
	unsigned long long int invCheck = 0;
	int counterLength = 6;

	if ( testT == falsePositiveNumber ) {
		invCheck = 10;
		for ( int counter = 0; counter < counterLength; counter++ ) {
			dumbVsSmartMembershipCheck(smartVsDumbTestCase, SIMPLE_FBF, (numElements + counter * increments), DEF_TABLE_SIZE, DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}
	else if ( testT == numberOfTrials ) {
		invCheck = 200000;
		for ( int counter = 0; counter < counterLength; counter++ ) {
			dumbVsSmartMembershipCheck(smartVsDumbTestCase, SIMPLE_FBF, (numElements + counter * increments), DEF_TABLE_SIZE, DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	dumbFPR->writeTestParameters("TEST PARAMETERS");
	string testparams = "Number of bloom filters in FBF," + to_string(SIMPLE_FBF) + "\n" + "Constituent Filter bits, " + to_string(DEF_TABLE_SIZE) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Refresh Rate," + to_string(DEF_REFRESH_RATE) + "\n" + "Batch Operations," + to_string(batch) + "\n" + "Invalid check," + to_string(invCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	dumbFPR->writeTestParameters(testparams);

	delete smartFPR;
	delete dumbFPR;
	trace.funcExit("Driver::dumbVsSmartMemTest");
}

/******************************************************************************
 * FUNCTION NAME: varyNumElements
 *
 * DESCRIPTION: This function runs the test case where the number of elements are varied
 * 				ie increased while the constituent BF size and the number of hash functions
 * 				are kept constant. The insertion rate is also kept constant.
 ******************************************************************************/
void Driver::varyNumElements() {
	trace.funcEntry("Driver::varyNumElements");
	string test = "numElementstest" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartFPR", test);
	Results * effFPR = new Results("effectiveFPR", test);
	Results * fbfAnalysis = new Results("fbfAnalysis", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(effFPR);
	resultsVector.emplace_back(fbfAnalysis);

	int numElements = 100;
	int increments = 100;
	int batch = 75;
	testType testT = numberOfTrials;
	unsigned long long int invCheck = 0;
	int counterLength = 6;

	if ( testT == falsePositiveNumber ) {
		invCheck = 10;
		for ( int counter = 0; counter < counterLength; counter++ ) {
			FPRMethodsAnalysis(numElementsTestCase, SIMPLE_FBF, (numElements + counter * increments), DEF_TABLE_SIZE, DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}
	else if ( testT == numberOfTrials ) {
		invCheck = 200000;
		for ( int counter = 0; counter < counterLength; counter++ ) {
			FPRMethodsAnalysis(numElementsTestCase, SIMPLE_FBF, (numElements + counter * increments), DEF_TABLE_SIZE, DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	effFPR->writeTestParameters("TEST PARAMETERS");
	fbfAnalysis->writeTestParameters("TEST PARAMETERS");
	string testparams = "Number of bloom filters in FBF," + to_string(SIMPLE_FBF) + "\n" + "Constituent Filter bits, " + to_string(DEF_TABLE_SIZE) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Refresh Rate," + to_string(DEF_REFRESH_RATE) + "\n" + "Batch Operations," + to_string(batch) + "\n" + "Invalid check," + to_string(invCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	effFPR->writeTestParameters(testparams);
	fbfAnalysis->writeTestParameters(testparams);

	delete smartFPR;
	delete effFPR;
	delete fbfAnalysis;
	trace.funcExit("Driver::varyNumElements");
}

/******************************************************************************
 * FUNCTION NAME: varyBFsize
 *
 * DESCRIPTION: This function runs the test case where the constituent BF size are varied
 * 				ie increased while the number of elements inserted and the number of hash
 * 				functions are kept constant. The insertion rate is also kept constant.
 ******************************************************************************/
void Driver::varyBFsize() {
	trace.funcEntry("Driver::varyBFsize");
	string test = "BFsizetest" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartFPR", test);
	Results * effFPR = new Results("effectiveFPR", test);
	Results * fbfAnalysis = new Results("fbfAnalysis", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(effFPR);
	resultsVector.emplace_back(fbfAnalysis);

	int numElements = 300;
	int batch = 1000;
	testType testT = numberOfTrials;
	unsigned long long int invCheck = 0;
	vector<int> filterSizes = {6250, 8750, 12500, 15000, 25000, 27500};

	if ( testT == falsePositiveNumber ) {
		invCheck = 10;
		for ( int counter = 0; counter < filterSizes.size(); counter++ ) {
			FPRMethodsAnalysis(BFsizeTestCase, SIMPLE_FBF, numElements, filterSizes[counter] , DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}
	else if ( testT == numberOfTrials ) {
		invCheck = 20000;
		for ( int counter = 0; counter < filterSizes.size(); counter++ ) {
			FPRMethodsAnalysis(BFsizeTestCase, SIMPLE_FBF, numElements, filterSizes[counter], DEF_NUM_OF_HASH, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	effFPR->writeTestParameters("TEST PARAMETERS");
	fbfAnalysis->writeTestParameters("TEST PARAMETERS");
	string testparams = "Number of bloom filters in FBF," + to_string(SIMPLE_FBF) + "\n" + "Number of insertions, " + to_string(numElements) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Refresh Rate," + to_string(DEF_REFRESH_RATE) + "\n" + "Batch Operations," + to_string(batch) + "\n" + "Invalid check," + to_string(invCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	effFPR->writeTestParameters(testparams);
	fbfAnalysis->writeTestParameters(testparams);

	delete smartFPR;
	delete effFPR;
	delete fbfAnalysis;
	trace.funcExit("Driver::varyBFsize");
}

/******************************************************************************
 * FUNCTION NAME: varyHashes
 *
 * DESCRIPTION: This function runs the test case where the number of hashes are varied
 * 				ie increased while the number of elements inserted and the constituent
 * 				BF size are kept constant. The insertion rate is also kept constant.
 ******************************************************************************/
void Driver::varyHashes() {
	trace.funcEntry("Driver::varyHashes");
	string test = "Hashes" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartFPR", test);
	Results * effFPR = new Results("effectiveFPR", test);
	Results * fbfAnalysis = new Results("fbfAnalysis", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(effFPR);
	resultsVector.emplace_back(fbfAnalysis);

	int numElements = 600;
	int batch = 200;
	//testType testT = numberOfTrials;
	testType testT = falsePositiveNumber;
	unsigned long long int invCheck = 0;
	int counterStart = 3;
	int counterLength = 18;

	if ( testT == falsePositiveNumber ) {
		invCheck = 20;
		for ( int counter = counterStart; counter <= counterLength; counter++ ) {
			FPRMethodsAnalysis(numHashesTestCase, SIMPLE_FBF, numElements, DEF_TABLE_SIZE , counter, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}
	else if ( testT == numberOfTrials ) {
		invCheck = 2000000;
		for ( int counter = counterStart; counter <= counterLength; counter++ ) {
			FPRMethodsAnalysis(numHashesTestCase, SIMPLE_FBF, numElements, DEF_TABLE_SIZE, counter, DEF_REFRESH_RATE, batch, testT, invCheck, resultsVector);
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	effFPR->writeTestParameters("TEST PARAMETERS");
	fbfAnalysis->writeTestParameters("TEST PARAMETERS");
	string testparams = "Number of bloom filters in FBF," + to_string(SIMPLE_FBF) + "\n" + "Number of insertions, " + to_string(numElements) + "\n" + "Number of bits in filters," + to_string(DEF_TABLE_SIZE) + "\n" + "Refresh Rate," + to_string(DEF_REFRESH_RATE) + "\n" + "Batch Operations," + to_string(batch) + "\n" + "Invalid check," + to_string(invCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	effFPR->writeTestParameters(testparams);
	fbfAnalysis->writeTestParameters(testparams);

	delete smartFPR;
	delete effFPR;
	delete fbfAnalysis;
	trace.funcExit("Driver::varyHashes");
}

/******************************************************************************
 * FUNCTION NAME: varyRefreshRate
 *
 * DESCRIPTION: This function runs the test case where the operations per second is varied
 * 				while the rest is kept constant. This is to check how false positive rate
 * 				reacts for different refresh rates
 ******************************************************************************/
void Driver::varyRefreshRate() {
	trace.funcEntry("Driver::varyRefreshRate");
	string test = "refreshRate" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartFPR", test);
	Results * effFPR = new Results("effectiveFPR", test);
	Results * fbfAnalysis = new Results("fbfAnalysis", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(effFPR);
	resultsVector.emplace_back(fbfAnalysis);

	unsigned long int numElements = 5000;
	unsigned long int tableSize = 25000;
	vector<int> refreshRateList = {20,10,5,3,2,1};
	testType testT = numberOfTrials;
	unsigned long invalidCheck = 0;
	vector<int> batches = {100, 250, 500, 750, 900, 1000};

	for ( int i = 0; i < batches.size(); i++ ) {
		if ( testT == falsePositiveNumber ) {
			invalidCheck = 10;
			for ( int counter = 0; counter < refreshRateList.size(); counter++ ) {
				opsPerSecTests(refreshRateTestCase, SIMPLE_FBF, numElements, tableSize, DEF_NUM_OF_HASH, refreshRateList[counter], batches[i], testT, invalidCheck, resultsVector);
			}
		}
		else if ( testT == numberOfTrials ) {
			invalidCheck = 100000;
			for ( int counter = 0; counter < refreshRateList.size(); counter++ ) {
				opsPerSecTests(refreshRateTestCase, SIMPLE_FBF, numElements, tableSize, DEF_NUM_OF_HASH, refreshRateList[counter], batches[i], testT, invalidCheck, resultsVector);
			}
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	effFPR->writeTestParameters("TEST PARAMETERS");
	fbfAnalysis->writeTestParameters("TEST PARAMETERS");
	string testparams = "Number of bloom filters in FBF," + to_string(SIMPLE_FBF) + "\n" + "Constituent Filter bits, " + to_string(tableSize) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Number of elements," + to_string(numElements) + "\n"  + "Invalid check," + to_string(invalidCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	effFPR->writeTestParameters(testparams);
	fbfAnalysis->writeTestParameters(testparams);

	delete smartFPR;
	delete effFPR;
	delete fbfAnalysis;
	trace.funcExit("Driver::varyRefreshRate");
}

/******************************************************************************
 * FUNCTION NAME: varyConstituentBFNumbers
 *
 * DESCRIPTION: This function runs the test case where the operations per second is varied
 * 				while the rest is kept constant. This is to check how false positive rate
 * 				reacts for different number of constituent BFs in the FBF
 ******************************************************************************/
void Driver::varyConstituentBFNumbers() {
	trace.funcEntry("Driver::varyConstituentBFNumbers");
	string test = "numOfFilters" + Results::retCurrentTime();
	Results * smartFPR = new Results("smartFPR", test);
	Results * effFPR = new Results("effectiveFPR", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(smartFPR);
	resultsVector.emplace_back(effFPR);
	//unsigned long int numElements = 3000;
	unsigned long int numElements = 3000;
	unsigned long int tableSize = 6250;
	vector<int> numberOfBloomFilters = {3,6,12,24};
	testType testT = numberOfTrials;
	unsigned long invalidCheck = 0;
	vector<int> batches = {100, 150, 200, 300, 500};
	//vector<int> batches = {125, 175, 200, 300};
	int numHash = 5;

	for ( int i = 0; i < batches.size(); i++ ) {
		if ( testT == falsePositiveNumber ) {
			invalidCheck = 10;
			for ( int counter = 0; counter < numberOfBloomFilters.size(); counter++ ) {
				opsPerSecTests(numBloomFiltersTestCase, numberOfBloomFilters[counter], numElements, tableSize, numHash, DEF_REFRESH_RATE, batches[i], testT, invalidCheck, resultsVector);
			}
		}
		else if ( testT == numberOfTrials ) {
			invalidCheck = 100000;
			for ( int counter = 0; counter < numberOfBloomFilters.size(); counter++ ) {
				opsPerSecTests(numBloomFiltersTestCase, numberOfBloomFilters[counter], numElements, tableSize, numHash, DEF_REFRESH_RATE, batches[i], testT, invalidCheck, resultsVector);
			}
		}
	}

	smartFPR->writeTestParameters("TEST PARAMETERS");
	effFPR->writeTestParameters("TEST PARAMETERS");
	string testparams = "Refresh rate," + to_string(DEF_REFRESH_RATE) + "\n" + "Constituent Filter bits, " + to_string(tableSize) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Number of elements," + to_string(numElements) + "\n"  + "Invalid check," + to_string(invalidCheck) + "\n";
	smartFPR->writeTestParameters(testparams);
	effFPR->writeTestParameters(testparams);

	delete smartFPR;
	delete effFPR;
	trace.funcExit("Driver::varyConstituentBFNumbers");
}

/**
 * FUNCTION NAME: dynamicResizingExperiment
 *
 * DESCRIPTION: This function runs the dynamic resizing experiments
 */
void Driver::dynamicResizingExperiment() {
	trace.funcEntry("Driver::dynamicResizingExperiment");
	string test = "dynamicResizing" + Results::retCurrentTime();
	Results * effFPR = new Results("effectiveFPR", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(effFPR);

	int numElements = 1000;
	int batch = 50;
	unsigned long initialRefreshRate = 7;

	dynamicResizing(numElements, DEF_TABLE_SIZE, DEF_NUM_OF_HASH, initialRefreshRate, batch, resultsVector);

	effFPR->writeTestParameters("TEST PARAMETERS");
	string testparams = "Constituent Filter bits, " + to_string(DEF_TABLE_SIZE) + "\n" + "Number of hash functions," + to_string(DEF_NUM_OF_HASH) + "\n" + "Initial Refresh Rate," + to_string(initialRefreshRate) + "\n" + "Batch Operations," + to_string(batch) + "\n";
	effFPR->writeTestParameters(testparams);

	delete effFPR;
	trace.funcExit("Driver::dynamicResizingExperiment");
}

/**
 * FUNCTION NAME: recyclableBloomFilterExperiment
 *
 * DESCRIPTION: This function runs the recyclable Bloom Filter experiment
 */
void Driver::recyclableBloomFilterExperiment() {
	trace.funcEntry("Driver::recyclableBloomFilterExperiment");
	string test = "recylableBloomFilter" + Results::retCurrentTime();
	Results * recyclBF = new Results("recyclableBloomFilter", test);
	vector<Results *> resultsVector;
	resultsVector.emplace_back(recyclBF);

	unsigned long long int numElements = 10000;
	int batch = 50;

	recyclableBloomFilterRun(numElements, DEF_TABLE_SIZE, DEF_NUM_OF_HASH, batch, resultsVector);

	recyclBF->writeTestParameters("TEST PARAMETERS");
	string testparams="Constituent Filter bits, " + to_string(DEF_TABLE_SIZE) + "\n" + "Number of hash functions, " + to_string(DEF_NUM_OF_HASH) + "\n" + "Batch Operations," + to_string(batch) + "\n";
	recyclBF->writeTestParameters(testparams);

	delete recyclBF;
	trace.funcExit("Driver::recyclableBloomFilterExperiment");
}

/**
 * FUNCTION NAME: usage
 *
 * DESCRIPTION: Describes the usage
 */
void usage(string exec) {
	cout<<endl<<"  ERROR :: Usage: " <<exec<<" <test_case>"<<endl;
	cout<<"  "<<smartVsDumbTestCase<<": Smart VS Dumb membership check"<<endl;
	cout<<"  "<<numElementsTestCase<<": Number of elements VS FPP"<<endl;
	cout<<"  "<<BFsizeTestCase<<": Filter size VS FPP"<<endl;
	cout<<"  "<<numHashesTestCase<<" : Number of hashes VS FPP"<<endl;
	cout<<"  "<<refreshRateTestCase<<" : Refresh Rate VS FPP"<<endl;
	cout<<"  "<<numBloomFiltersTestCase<<" : Number of Constituent Bloom Filter VS FPP"<<endl;
	cout<<"  "<<dynamicResizingTestCase<<" : Dynamic Resizing"<<endl<<endl;
	cout<<"  "<<recyclableBloomFilterTestCase<<" : Recyclable Bloom Filter Experiment"<<endl<<endl;
}

/*
 * Main function
 */
int main(int argc, char *argv[]) {

	trace.traceFileCreate();
	trace.funcEntry("Driver::main");

	if ( 2 != argc ) {
		usage(string(argv[0]));
		return FAILURE;
	}

	string testcase(argv[1]);

	Driver driver;
	if ( testcase == to_string(smartVsDumbTestCase) ) {
		/*
		 * Smart membership check vs dumb membership check
		 */
		cout<<endl<<"  INFO :: smart membership check vs dumb membership check"<<endl;
		driver.dumbVsSmartMemTest();
	}
	else if ( testcase == to_string(numElementsTestCase) ) {
		/*
		 * FPR Methods vs number of elements inserted into FBF
		 */
		cout<<endl<<"  INFO :: FPR Methods vs number of elements inserted into FBF"<<endl;
		driver.varyNumElements();
	}
	else if ( testcase == to_string(BFsizeTestCase) ) {
		/*
		 * FPR Methods vs constituent filter size
		 */
		cout<<endl<<"  INFO :: FPR Methods vs constituent filter size"<<endl;
		driver.varyBFsize();
	}
	else if ( testcase == to_string(numHashesTestCase) ) {
		/*
		 * FPR Methods vs number of hashes
		 */
		cout<<endl<<"  INFO :: FPR Methods vs number of hashes"<<endl;
		driver.varyHashes();
	}
	else if ( testcase == to_string(refreshRateTestCase) ) {
		/*
		 * Vary refresh rate
		 */
		cout<<endl<<"  INFO :: Vary refresh rate"<<endl;
		driver.varyRefreshRate();
	}
	else if ( testcase == to_string(numBloomFiltersTestCase) ) {
		/*
		 * Vary number of constituent bloom filters
		 */
		cout<<endl<<"  INFO :: Vary number of constituent bloom filters"<<endl;
		driver.varyConstituentBFNumbers();
	}
	else if ( testcase == to_string(dynamicResizingTestCase) ) {
		cout<<endl<<"  INFO :: Dynamic resizing experiment"<<endl;
		driver.dynamicResizingExperiment();
	}
	else if ( testcase == std::to_string(recyclableBloomFilterTestCase) ) {
		std::cout<<std::endl<<"  INFO :: Recyclable Bloom Filter experiment"<<std::endl;
		driver.recyclableBloomFilterExperiment();
	}
	else {
		cout<<endl<<"  INFO :: Invalid argument"<<endl;
		usage(string(argv[0]));
	}

	trace.funcExit("Driver::main", SUCCESS);
	return SUCCESS;

} // End of main()

/*
 * EOF
 */
