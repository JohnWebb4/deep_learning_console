#pragma once
// Include standard library
#include "stdafx.h"
// Needed for vector
#include <vector>
// Needed for string
#include <string>
// Needed for function
#include <functional>

/* Holds training data
*/
class TrainingData
{
public:

	// 
	/* Get training data
	*/
	vector<vector<string>> Get();

	/* Set training data
	*/
	void Set(function<bool> func, bool &exitTest, DLConsole &console, vector<vector<string>> &train_data, int &mini_batch_size, float &eta);

	/*
	*/
	void Hook>(function func<hookPattern>);

private:
	vector<vector<string>> trainingData;
};
