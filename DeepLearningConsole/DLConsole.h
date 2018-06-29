#pragma once

#include "stdafx.h"
#include <list>

// Declare namesapce
using namespace std;

class DLConsole : public Network
{
public:
	/* Dictionary to convert sentence to array
	*/
	vector<string> dictionary;


	/* Convert input to vector float array based off of inputs
	Param input:	The string to be converted
	Param size:		The size of the vector
	Returns:		Vector float of string inputs
	*/
	vector<float> ReadToArray(string input, int size);

	/* Read input to string
	Param input:	Input to convert to string
	Returns:		String representation of input
	*/
	string ReadFromArray(vector<float> input);

	/* Construct a new DLConsole
	Param size:	The neuron per layer of the network {#words, #hidden, #words
	Input and output resize with dictionary size
	*/
	DLConsole(vector<int> size);

	/* Feed string through network
	Param input:	Input to network
	*/
	string FeedForward(string input);

	/*Stoichastic Gradient Descent
	Param training_data:	3 Dimensional matrix of input and output
	Param epochs:			The number of iterations around the training data
	Param mini_batch_size:	The mini batch size
	Param eta:				The learning rate
	Param test_data:		Additional data to check against netowrk. Results output to console<
	*/
	void SGD(vector<vector<string>> training_data, int epochs, int mini_batch_size,
		float eta, vector<vector<string>> test_data = vector<vector<string>>(0),
		bool breakOnPerfect = false);

	// Needed to inherit SGD
	Network::SGD;

	// Neded to inherit FeedFowrad
	Network::FeedForward;

	/* Evaluate test data
	Param test_data:	Data to test against system (#tests)x(2)
	Returns:			Number of correct responses
	*/
	int Evaluate(vector<vector<string>> test_data);

	/* Split string based off of deliminator
	Param s:		String to split
	Param delim:	Character to split with
	Param result:	Result of split
	Thank you Evan Teran http://stackoverflow.com/questions/236129/split-a-string-in-c
	*/
	template<typename Out>
	static void Split(const string& s, char delim, Out result);

	/* Split string based off of deliminator
	Param s:		String to split
	Param delim:	Character to split with
	Returns:		Vector of split string
	*/
	static vector<string> Split(const string &s, char delim);
};