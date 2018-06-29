#include "stdafx.h"
// Needed for cin and cout
#include <iostream>
// Needed for string
#include <string>
// Needed for vectors
#include <vector>
// Needed for transform
#include <algorithm>
// Needed for back_inserter
#include <iterator>
// Needed for string stream
#include <sstream>

// Declare namespace
using namespace std;


/* Convert input to vector float array based off of inputs
Param input:	The string to be converted
Param size:		The size of the array
Returns:		Vector float of string inputs
*/
vector<float> DLConsole::ReadToArray(string input, int size)
{
	// Create vector of size of inputs
	vector<float> fInput = vector<float>(size, -1.0f);

	// Convert string to substring deliminated by space
	vector<string> vInput = Split(input, ' ');

	// Calculate which is smaller input size of sizes[0]
	int iMinSize = min(size, static_cast<int>(vInput.size()));

	// Cycle through response
	for (int i = 0; i < iMinSize; i++)
	{
		// Declare iterator for dictioanry
		list<string>::iterator iterator;

		// Cycle through dictionary
		for (int j = 0; j < dictionary.size(); j++)
		{
			// If equal
			if (vInput[i] == dictionary[j])
			{
				// Assign index in dictionary
				fInput[i] = j;
				
				// Break dictionary search
				break;
			}
		}
		
	}

	// Return float array
	return fInput;
}

/* Read input to string
Param input:	Input to convert to string
Param inputs:	Vector string used to convert
Returns:		String representation of input
*/
string DLConsole::ReadFromArray(vector<float> input)
{
	// Test dictionary is not empty
	if (dictionary.size() == 0)
	{
		// If empty return empty string
		return "";
	}

	// Declare results
	string result;

	// Cycle through words
	for (int i = 0; i < input.size(); i++)
	{
		// If negative skip
		if (round(input[i]) < 0)
		{
			break;
		}

		// Append to result. Round
		result += dictionary[round(input[i])];

		// If not end, add space
		if (i != input.size() - 1)
		{
			result += " ";
		}
	}

	// Return result
	return result;
}

/* Construct a new DLConsole
Param size:	The neuron per layer of the network {#words, #hidden, #words
Input and output resize with dictionary size
*/
DLConsole::DLConsole(vector<int> size) : Network::Network(size)
{
	// Initialize to input size with first element as space
	dictionary = vector<string>();
}

/* Feed string through network
Param input:	Input to network
*/
string DLConsole::FeedForward(string input)
{
	// Get output
	vector<float> output = FeedForward(ReadToArray(input, sizes[0]));
	// Return string output
	return ReadFromArray(output);
}

/*Stoichastic Gradient Descent
Param training_data:	3 Dimensional matrix of input and output
Param epochs:			The number of iterations around the training data
Param mini_batch_size:	The mini batch size
Param eta:				The learning rate
Param test_data:		Additional data to check against netowrk. Results output to console<
*/
void DLConsole::SGD(vector<vector<string>> training_data, int epochs, int mini_batch_size,
	float eta, vector<vector<string>> test_data,
	bool breakOnPerfect)
{
	// Convert training data to vector float
	vector<vector<vector<float>>> fTraining_data = vector<vector<vector<float>>>(training_data.size());

	// Convert test data to vector float
	vector<vector<vector<float>>> fTest_data = vector<vector<vector<float>>>(test_data.size());

	// Cycle through each training piece
	for (int i = 0; i < training_data.size(); i++)
	{
		// Initialize vector (input, output)
		fTraining_data[i] = vector<vector<float>>(2);

		// Populate dictionary
		// Cycle through input and output
		for (int j = 0; j < training_data[i].size(); j++)
		{
			// Split sentence to vector string
			vector<string> sentence = Split(training_data[i][j], ' ');

			// Cycle through sentence
			for (int k = 0; k < sentence.size(); k++)
			{
				// Declare flag if new word
				bool bNewWord = true;

				// Cycle through dictionary
				for (int l = 0; l < dictionary.size(); l++)
				{
					// If word exists
					if (sentence[k] == dictionary[l])
					{
						// Set new word to false
						bNewWord = false;

						// Break dictionary search
						break;
					}
				}

				// If new word
				if (bNewWord)
				{
					// Add to end of dictionary
					dictionary.emplace_back(sentence[k]);
				}
			}
		}

		// Convert input
		fTraining_data[i][0] = ReadToArray(training_data[i][0], sizes[0]);

		// Convert output
		fTraining_data[i][1] = ReadToArray(training_data[i][1], sizes.back());
	}

	// Cycle through test_data if present
	if (test_data.size() != 0)
	{
		for(int i = 0; i < test_data.size(); i++)
		{
			// Initialize vector (input, output)
			fTest_data[i] = vector<vector<float>>(2);

			// Convert input
			fTest_data[i][0] = ReadToArray(test_data[i][0], sizes[0]);

			// Conver output
			fTest_data[i][1] = ReadToArray(test_data[i][1], sizes.back());
		}
	}

	// Perform SGD
	// Cycle through epochs
	for (int i = 0; i < epochs; i++)
	{
		// Do not break on perfect
		SGD(fTraining_data, 1, mini_batch_size, eta);

		// If test data
		if (test_data.size() != 0)
		{
			// Evaluate test data
			int iPasses = Evaluate(test_data);
			// Write to console
			cout << StringTable.at(StringEpoch) << i << 
				StringTable.at(StringColon) << iPasses <<
				StringTable.at(StringOf) << test_data.size() << endl;

			// If break on perfect
			if (breakOnPerfect && (iPasses == test_data.size()))
			{
				// Return
				return;
			}
		}
		// Else write complete
		else
		{
			// Write complete
			// cout << "Epoch " << i << " complete" << endl;
		}
	}
}

/* Evaluate test data
Param test_data:	Data to test against system (#tests)x(2)
Returns:			Number of correct responses
*/
int DLConsole::Evaluate(vector<vector<string>> test_data)
{
	// Declare number of correct tests
	int iPasses = 0;

	// Cycle through training data
	for (int i = 0; i < test_data.size(); i++)
	{
		// Get input
		string sInput = test_data[i][0];
		// Get ideal output
		string sIdealOut = test_data[i][1];

		int iSize = sizes.back() - (int)sIdealOut.size();

		// Convert to string
		string sRealOut = FeedForward(sInput);

		// Check against ideal output
		if (sIdealOut == sRealOut)
		{
			// Increment counter
			iPasses++;
		}
	}

	// Return iPasses
	return iPasses;
}

/* Split string based off of deliminator
Param s:		String to split
Param delim:	Character to split with
Param result:	Result of split
Thank you Evan Teran http://stackoverflow.com/questions/236129/split-a-string-in-c
*/
template<typename Out>
void DLConsole::Split(const string& s, char delim, Out result)
{
	// Declare string stream
	stringstream ss;

	// Initialize string stream to given string
	ss.str(s);

	// Declare string to hold substring pieces
	string item;

	// Loop through string stream.
	// Substring based off delim and assign to item
	while (getline(ss, item, delim))
	{
		// If not empty
		if (!item.empty())
		{
			// Assign to end of result
			*(result++) = item;
		}
	}
}

/* Split string based off of deliminator
Param s:		String to split
Param delim:	Character to split with
Returns:		Vector of split string
*/
vector<string> DLConsole::Split(const string &s, char delim)
{
	// Declare result
	vector<string> elems;

	// Split string
	Split(s, delim, back_inserter(elems));

	// Return elems
	return elems;
}