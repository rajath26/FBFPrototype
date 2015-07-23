/*
 * Timer.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: rajatsub
 */

#include "Timer.h"

/**
 * Constructor
 */
Timer::Timer() {
	trace.funcEntry("Timer::Timer");
	startSeconds = 0;
	trace.funcExit("Timer::Timer");
}

/**
 * Destructor
 */
Timer::~Timer() {
	trace.funcEntry("Timer::~Timer");
	trace.funcExit("Timer::~Timer");
}

/**
 * FUNCTION NAME: start
 *
 * DESCRIPTION: Start the timer
 */
void Timer::start() {
	trace.funcEntry("Timer::start");
	gettimeofday(&startTime, NULL);
	startSeconds = startTime.tv_sec + (startTime.tv_usec/1000000.0);
	trace.funcExit("Timer::start");
}

/**
 * FUNCTION NAME: printStartTime
 *
 * DESCRIPTION: Print the start seconds
 */
void Timer::printStartName() {
	trace.funcEntry("Timer::printStartName");
	cout<<"  INFO :: Start seconds: "<<startSeconds <<endl;
	trace.funcExit("Timer::printStartName");
}

/**
 * FUNCTION NAME: printElapsedTime
 *
 * DESCRIPTION: Print the elapsed time since start time
 */
void Timer::printElapsedTime() {
	trace.funcEntry("Timer::printElapsedTime");
	struct timeval now;
	gettimeofday(&now, NULL);
	double nowSeconds = now.tv_sec + (now.tv_usec/1000000.0);
	cout<<"  INFO :: Elapsed seconds: "<<(nowSeconds - startSeconds) <<endl;
	trace.funcExit("Timer::printElapsedTime");
}

/**
 * FUNCTION NAME: getElapsedTime
 *
 * DESCRIPTION: Get the elapsed time
 */
double Timer::getElapsedTime() {
	trace.funcEntry("Timer::getElapsedTime");
	struct timeval now;
	gettimeofday(&now, NULL);
	double nowSeconds = now.tv_sec + (now.tv_usec/1000000.0);
	return (nowSeconds - startSeconds);
	trace.funcExit("Timer::getElapsedTime");
}
