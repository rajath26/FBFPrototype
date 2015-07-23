/*
 * Results.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: rajatsub
 */

#include "Results.h"

/**
 * Constructor
 */
Results::Results(string name, string testcase) {
	fileName = "./Results/" + testcase + name + "_" + retCurrentTime() + ".csv";
	file.open(fileName, std::ios_base::out);
}

/**
 * FUNCTION NAME: retCurrentTime
 *
 * DESCRIPTION: This function returns current time as string
 */
string Results::retCurrentTime() {
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char buffer[80];
	strftime(buffer, 80, "%F:%H:%M:%S", timeinfo);
	return string(buffer);
}

/**
 * Destructor
 */
Results::~Results() {
	file.close();
}

/**
 * FUNCTION NAME: numElementsVsFPR
 *
 * DESCRIPTION: Writes results into csv for numElementsVsFPR
 */
void Results::numElementsVsFPR(long long int numElements, double fpr) {
	file << numElements <<"," <<fpr <<endl;
	file.flush();
}

/**
 * FUNCTION NAME: writeTestParameters
 *
 * DESCRIPTION: This function writes the Test Parameters into the csv file
 */
void Results::writeTestParameters(string buffer) {
	file << buffer <<endl;
	file.flush();
}

/**
 * FUNCTION NAME: BFsizeVSFPR
 *
 * DESCRIPTION: Writes results into csv for BFsizeVSFPR
 */
void Results::BFsizeVSFPR(unsigned long bits, double fpr) {
	file << bits <<"," <<fpr <<endl;
	file.flush();
}

/**
 * FUNCTION NAME: numHashesVSFPR
 *
 * DESCRIPTION: Writes results into csv for numHashesVSFPR
 */
void Results::numHashesVSFPR(unsigned long numHashes, double fpr) {
	file << numHashes <<"," <<fpr <<endl;
	file.flush();
}

/**
 * FUNCTION NAME: refreshRateOpsPerSecondFPR
 *
 * DESCRIPTION: Writes results in csv for refreshRateOpsPerSecondFPR
 */
void Results::refreshRateOpsPerSecondFPR(unsigned long refreshRate, double opsPerSecond, double fpr) {
	file << refreshRate <<"," <<opsPerSecond <<"," <<fpr <<endl;
	file.flush();
}

/**
 * FUNCTION NAME: dynResizingRecord
 *
 * DESCRIPTION: Writes results in csv for dynamic resizing experiment
 */
void Results::dynResizingRecord(double num, double fpr, unsigned long refreshRate, unsigned long numberOfBFs) {
	file << num <<"," <<fpr <<"," <<refreshRate <<"," <<numberOfBFs <<endl;
	file.flush();
}
