#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_
#include <vector>
#include <map>
#include <Event/Observable.hpp>

enum LearningStateEvents
{
	EVT_LS_DS_CHANGED
};


// All informations about a finished learning process
struct LearningState : public LightBulb::Observable<LearningStateEvents, LearningState>
{
	template <class Archive>
	friend void serialize(Archive& archive, LearningState& learningState);
private:
	int dataSaveInterval;
public:
	// Was the learning process successful
	int successful;

	double quality;
	// How many iterations were needed
	int iterationsNeeded;

	std::map<std::string, std::vector<double>> dataSets;
	LearningState(int dataSaveInterval_ = 1)
	{
		successful = 0;
		quality = 0;
		iterationsNeeded = 0;
		dataSaveInterval = dataSaveInterval_;
	}

	void addData(std::string dataSetLabel, int iteration, double data)
	{
		if (iteration % dataSaveInterval == 0)
		{
			dataSets[dataSetLabel].push_back(iteration);
			dataSets[dataSetLabel].push_back(data);
			throwEvent(EVT_LS_DS_CHANGED, this);
		}
	}

};

#endif