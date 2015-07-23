/*
 * Timer.h
 *
 *  Created on: Nov 20, 2014
 *      Author: rajatsub
 */

#ifndef TIMER_H_
#define TIMER_H_

#include<time.h>
#include<sys/time.h>

#include "Common.h"

/*
 * Trace class
 */
#include "Trace.h"

/*
 * Global variables
 */
extern Trace trace;

/**
 * CLASS NAME: Timer
 *
 * DESCRIPTION: This class maintains the timer
 */
class Timer {
private:
	struct timeval startTime;
	double startSeconds;

public:
	Timer();
	virtual ~Timer();
	void start();
	void printStartName();
	void printElapsedTime();
	double getElapsedTime();
};

#endif /* TIMER_H_ */
