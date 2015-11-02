#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_

// All informations about a finished learning process
struct LearningResult
{
	// Was the learning process successful
	int successful;
	// How many iterations were needed
	int iterationsNeeded;
	LearningResult()
	{
		successful = 0;
		iterationsNeeded = 0;
	}
};

#endif