CFLAGS = -Wall -g -std=c++11  -stdlib=libc++
COMPILER = g++

all: Simulation

Simulation: Driver.o Trace.o FBF.o Timer.o Results.o RecycleBloomFilter.o
	${COMPILER} -o Simulation Driver.o Trace.o FBF.o Timer.o Results.o RecycleBloomFilter.o ${CFLAGS}

Driver.o: Driver.cpp Driver.h FBF.cpp Timer.cpp Common.h Results.h
	${COMPILER} -c Driver.cpp ${CFLAGS}

FBF.o: FBF.cpp FBF.h bloom_filter.hpp Common.h 
	${COMPILER} -c FBF.cpp ${CFLAGS}
	
RecycleBloomFilter.o: RecycleBloomFilter.cpp RecycleBloomFilter.h bloom_filter.hpp Common.h
	${COMPILER} -c RecycleBloomFilter.cpp ${CFLAGS}

Timer.o: Timer.cpp Timer.h Common.h 
	${COMPILER} -c Timer.cpp ${CFLAGS} 
	
Trace.o: Trace.cpp Trace.h
	${COMPILER} -c Trace.cpp ${CFLAGS}
	
Results.o: Results.cpp Results.h
	${COMPILER} -c Results.cpp ${CFLAGS}

clean: 
	rm -rf *.o Simulation
