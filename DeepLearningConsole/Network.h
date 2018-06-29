#pragma once

#include <vector>

using namespace std;

class Network
{
public:
	//The number of layers of the network
	int numLayers;

	//The size of the network
	vector<int> sizes;

	//The biases for each layer of the network
	vector<vector<float>> biases;

	//The weights for each neuron
	vector<vector<vector<float>>> weights;

	/* Initialize a new bias value
	Param min:	The minimum value
	Param max:	The maximum value
	Returns:	The new value
	*/
	static float NewValue(float min, float max);

	/*Logistic function
	Param z: The input to logistic function
	Returns: Result of logistic function
	*/
	static float LogicF(float z);

	/*Calculate cost of result from ideal
	Param realOut:	The result of the network
	Param idealOut:	The ideal result
	Returns:		Cost array
	*/
	static vector<float> Cost(vector<float> realOut, vector<float> idealOut);

	/*Calculate costs of results from ideal
	Param reaOuts:		The results of the network
	Param idealOuts:	The ideal results
	Returns:			Cost array
	*/
	static vector<vector<float>> Cost(vector<vector<float>> realOuts, vector<vector<float>> idealOuts);

	/*Calculate derivative of logic function given array
	Param z:	Array to calculate derivative of logic function with
	Returns:	Derivative of logic function array
	*/
	static vector<float> LogicFPrime(vector<float>z);

	/*Calculate derivative of logic function given array
	Param zs:	Array to calculate derivative of logic function with
	Returns:	Derivative of logic function array
	*/
	static vector<vector<float>> LogicFPrime(vector<vector<float>>zs);

	/*Construct network with random bias and weights of size sizes
	Param sizes: Array of number of neurons per layer
	*/
	Network(vector<int> sizes);

	/*Feed input through network
	Param input:	The input to network
	Returns:		Result of network
	*/
	vector<float> FeedForward(vector<float> input);

	/*Stoichastic Gradient Descent
	Param training_data:	3 Dimensional matrix of input and output
	Param epochs:			The number of iterations around the training data
	Param mini_batch_size:	The mini batch size
	Param eta:				The learning rate
	Param test_data:		Additional data to check against netowrk. Results output to console<
	*/
	void SGD(vector<vector<vector<float>>> training_data, int epochs, int mini_batch_size,
		float eta, vector<vector<vector<float>>> test_data = vector<vector<vector<float>>>(0),
		bool breakOnPerfect = false);
	
	/*Update Mini Batch
	Param mini_batch:	3 dimensional matrix of input and desired output
	Param eta:			The learning rate
	*/
	void UpdateMiniBatch(vector<vector<vector<float>>> mini_batch, float eta);

	/*Back propagation of input and desire output for gradients in biases and weights
	Param ins:				The inputs to the network
	Param outs:				The corresponding results of the network
	Param nabla_b:			The gradient result for biases
	Param nabla_w:			The gradietn result for weights
	*/
	void Backprop(vector<vector<float>> ins, vector<vector<float>> outs,
		vector<vector<float>>& nabla_b, vector<vector<vector<float>>>& nabla_w);

	/*Evalaute test data agains netowrk.
	Param test_data:	3 dimentisonal array of input and output to test against
	Returns:			Number of testing data the passed
	*/
	int Evaluate(vector<vector<vector<float>>> test_data);
};