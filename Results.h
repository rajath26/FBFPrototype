/*
 * Results.h
 *
 *  Created on: Nov 29, 2014
 *      Author: rajatsub
 */

#ifndef RESULTS_H_
#define RESULTS_H_

#include "Common.h"
#include <time.h>
#include<sstream>
#include<fstream>

/**
 * CLASS NAME: Results
 *
 * DESCRIPTION: Writes results into csv files
 */
class Results {
private:
	ofstream file;
	string fileName;
public:
	Results(string name, string testcase);
	virtual ~Results();
	static string retCurrentTime();
	void numElementsVsFPR(long long int numElements, double fpr);
	void BFsizeVSFPR(unsigned long numBits, double fpr);
	void numHashesVSFPR(unsigned long numHashes, double fpr);
	void refreshRateOpsPerSecondFPR(unsigned long refreshRate, double opsPerSecond, double fpr);
	void dynResizingRecord(double num, double fpr, unsigned long refreshRate, unsigned long numberOfBFs);
	void writeTestParameters(string buffer);
};

#endif /* RESULTS_H_ */
