// Include standard library
#include "stdafx.h"
// Needed for vector
#include <vector>
// Needed for string
#include <string>

/* Return training data as a vector vector string
Return:	The training data as a vector vector string
*/
template<typename hookPatt>
vector<vector<string>> TrainingData<hookPatt>::Get()
{
	// Return readonly training data
	return trainingData;
}

/* Set the training data and call hook
Param trainingData:	The training data to assign
*/
template<typename hookPatt>
void TrainingData<hookPatt>::Set(bool &exitTest, DLConsole &console,
	vector<vector<string>> &train_data, int &mini_batch_size, float &eta);
{
	// Assign training data
	this->trainingData = trainingData;
	// Call hook
	this->hook();
}

template<typename hookPatt>
void TrainingData<hookPatt>::Hook<hookPatt>(function<hookPatt> func)
{
	// Assign hook
}