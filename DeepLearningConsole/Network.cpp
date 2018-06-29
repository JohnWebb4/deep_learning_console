#include "stdafx.h"

#include <vector>
#include <random>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

// Calculate cost of output
// Param realOut:	The neural network result of the input
// Param idealOut:	The desired result
vector<float> Network::Cost(vector<float> realOut, vector<float> idealOut)
{
	// Initialize cost vector to zero
	vector<float> cost = vector<float>(idealOut.size(), 0.0f);

	// Cycle through array
	for (int i = 0; i < idealOut.size(); i++)
	{
		cost[i] = realOut[i] - idealOut[i];
	}

	// Return cost
	return cost;
}

/*Calculate costs of results from ideal
Param reaOuts:		The results of the network
Param idealOuts:	The ideal results
Returns:			Cost array
*/
vector<vector<float>> Network::Cost(vector<vector<float>> realOuts, vector<vector<float>> idealOuts)
{
	// Initialize cost vector to zero
	vector<vector<float>> costs = vector<vector<float>>(idealOuts.size());

	// Cycle through array
	for (int i = 0; i < idealOuts.size(); i++)
	{
		// Initialize cost to size of batch
		costs[i] = vector<float>(idealOuts[i].size(), 0.0f);
		
		// Cycle through array
		for (int j = 0; j < idealOuts[i].size(); j++)
		{
			// Calculate cost
			costs[i][j] = realOuts[i][j] - idealOuts[i][j];
		}
	}

	// Return costs
	return costs;
}

// Logistic Sigmoid function
float Network::LogicF(float z)
{
	// Identity function
	return z;
}

/* Calculate derivative of logic function
Param z:	Input to logic function
Returns:	Derivative of logic function
*/
vector<float> Network::LogicFPrime(vector<float> z)
{
	// Initailize result to size of z
	vector<float> result = vector<float>(z.size(), 0.0f);

	// Return derivative
	// Cycle through array
	for (int i = 0; i < z.size(); i++)
	{
		// Calculate result of ramp function
		result[i] = 1;
	}

	// Return result
	return result;
}

/*Calculate derivative of logic function given array
Param zs:	Array to calculate derivative of logic function with
Returns:	Derivative of logic function array
*/
vector<vector<float>> Network::LogicFPrime(vector<vector<float>>zs)
{
	// Initialize result to size of z
	vector<vector<float>> results = vector<vector<float>>(zs.size());

	// Cycle through array
	for (int i = 0; i < zs.size(); i++)
	{
		// Initialize result[i] to size of z[i]
		results[i] = vector<float>(zs[i].size(), 0.0f);

		// Cycle through array
		for (int j = 0; j < zs[i].size(); j++)
		{
			// Calculate result of ramp function
			results[i][j] = 1;
		}
	}

	// Return results
	return results;
}

/* Initialize a new bias value
Param min:	The minimum value
Param max:	The maximum value
Returns:	The new value
*/
float Network::NewValue(float min, float max)
{
	// Calculate value between 0 and 1
	float i = static_cast<float>(rand() & 1000) / 100000.0f;

	// Scale and return
	return (max - min) * i + min;
}

// Construct Neural network of size sizes
Network::Network(vector<int> sizes)
{
	// Calculate number of layers
	numLayers = sizes.size();
	// Set to sizes
	this->sizes = sizes;
	// Initialize biases and weights. First layer is input so no bias or weights
	biases = vector<vector<float>>(numLayers-1);
	weights = vector<vector<vector<float>>>(numLayers-1);
	// Generate random biases and weights
	// Cycle through layers
	for (int i = 0; i < numLayers-1; i++)
	{
		// Initialize biases[i]
		biases[i] = vector<float>(sizes[i+1]);
		// Initialzie weights[i]
		weights[i] = vector<vector<float>>(sizes[i+1]);

		// Cycle through nuerons
		for (int j = 0; j < sizes[i+1]; j++)
		{
			// Define random bias between 0 and 1
			biases[i][j] = NewValue(0.0f, 1.0f);

			// Allocate size for weights
			weights[i][j] = vector<float>(sizes[i]);

			// Cycle through weights and assign a value from 0 to 1
			for (int k = 0; k < sizes[i]; k++)
				weights[i][j][k] = NewValue(0.0f, 1.0f);
		}
	}
}

// Feed input through network
vector<float> Network::FeedForward(vector<float> input)
{
	// Declare vector a
	vector<float> in = input;
	vector<float> out;

	// Cycle through layers
	for (int i = 0; i < numLayers-1; i++)
	{
		// Initialize out vector to size of layer (output)
		out = vector<float>(sizes[i+1]);

		// Cycle through neurons in this layer
		for (int j = 0; j < sizes[i+1]; j++)
		{
			// Initialize value to zero
			float value = 0;

			// Cycle through input
			for (int k = 0; k < in.size(); k++)
			{
				value += weights[i][j][k] * in[k];
			}

			// Increment value by bias
			value += biases[i][j];

			// Assign out[k]
			out[j] = LogicF(value);
		}

		// Assign new in
		in = out;
	}
	// Return out
	return out;
}

// Train using mini-batch stochastic gradient descent
// Param Training Data:		Tuples (x,y) input and desired output
// Param epochs:			Number of cycles around data
// Param mini_batch_size:	Size of batch
// Param eta:				Learning Rate
// Param test_data:			After epoch cycle run against this data (slows process)
void Network::SGD(vector<vector<vector<float>>> training_data, int epochs, int mini_batch_size,
	float eta, vector<vector<vector<float>>> test_data, bool breakOnPerfect)
{
	// Declare test data size (null if no test data)
	int n_test;
	// If test data, calculate size of data
	if (test_data.size() != 0) n_test = test_data.size();
	// Calculate training_data size
	int n = training_data.size();
	// Define number of mini_batches
	int num_batches = floor((int) training_data.size() / min(mini_batch_size, static_cast<int>(training_data.size())));
	if (num_batches == 0) throw new exception(StringTable.at(StringMiniBatchLessTotal).c_str());
	// Cycle through epochs
	for (int i = 0; i < epochs; i++)
	{
		// Declare mini_batches
		vector<vector<vector<vector<float>>>> mini_batches = 
			vector<vector<vector<vector<float>>>>(num_batches);

		// Shuffle contents
		random_shuffle(training_data.begin(), training_data.end());

		// Cycle through number of batches
		for (int j = 0; j < num_batches; j++)
		{
			// Calculate first in mini_batch
			vector<vector<vector<float>>>::const_iterator first = training_data.begin() + j * mini_batch_size;
			// Calculate last in mini_batch
			vector<vector<vector<float>>>::const_iterator last = training_data.begin() + (j+1) * mini_batch_size;
			// Assign mini_batch
			mini_batches[j] = vector<vector<vector<float>>>(first, last);
		}

		// Cycle through mini_batches and update
		for (int k = 0; k < mini_batches.size(); k++)
			UpdateMiniBatch(mini_batches[k], eta);

		// If there is test data, print results
		if (test_data.size() != 0)
		{
			// Evaluate system
			int eval = Evaluate(test_data);
			cout << StringTable.at(StringEpoch) << i <<
				StringTable.at(StringColon) << eval <<
				StringTable.at(StringOf) << n_test << endl;

			// If perfect run return
			if ((breakOnPerfect) && (eval == n_test))
			{
				// Return
				return;
			}
		}
		// else print complete
		else
		{
			// cout << "Epoch " << i << " complete." << endl;
		}
	}
}

// Update weights and biases for mini_batch
// Param mini_batch:	Tuples (x,y) of input and desired output
// Param eta:			Learning rate
void Network::UpdateMiniBatch(vector<vector<vector<float>>> mini_batch, float eta)
{
	// Initialize nabla_b to size of baises
	vector<vector<float>> nabla_b = vector<vector<float>>(biases.size());

	// Initialize nabla_w to size of weights
	vector<vector<vector<float>>> nabla_w = vector<vector<vector<float>>>(weights.size());

	// Cycle through each layer
	for (int i = 0; i < numLayers - 1; i++)
	{
		// Initialize each neuron in layer to zero
		nabla_b[i] = vector<float>(biases[i].size(), 0.0f);
		
		// Initialize each weight to size of next layer
		nabla_w[i] = vector<vector<float>>(weights[i].size());

		// Cycle through each neuron
		for (int j = 0; j < biases[i].size(); j++)
		{
			// Initialize to size of previous layer
			nabla_w[i][j] = vector<float>(sizes[i], 0.0F);
		}
	}

	// Initialize ins to size of first layer
	vector<vector<float>> ins = vector<vector<float>>(sizes[0]);

	// Initialize outs to size of first layer
	vector<vector<float>> outs = vector<vector<float>>(sizes.back());

	// Cycle through each item is first layer
	for (int i = 0; i < sizes[0]; i++)
	{
		// Initialize ins term to size of mini batch
		ins[i] = vector<float>(mini_batch.size(), 0.0f);
		// Cycle through mini batch
		for (int j = 0; j < mini_batch.size(); j++)
		{
			// Assign ins
			ins[i][j] = mini_batch[j][0][i];
		}
	}

	// Cycle through each item in last layer
	for (int i = 0; i < sizes.back(); i++)
	{
		// Initialize term to mini batch size
		outs[i] = vector<float>(mini_batch.size(), 0.0f);
		
		// Cycle through mini batch
		for (int j = 0; j < mini_batch.size(); j++)
		{
			outs[i][j] = mini_batch[j][1][i];
		}
	}

	// Perform back propagation.
	// p_delta_nabla_b and p_delta_nabla_w hold results
	Backprop(ins, outs, nabla_b, nabla_w);

	// Completed all mini_batches
	// Adjust biases and weights

	// Cycle through each layer
	for (int i = 0; i < numLayers-1; i++)
	{
		// Cycle through each neuron
		for (int j = 0; j < weights[i].size(); j++)
		{
			// Calculate new bias
			biases[i][j] -= (eta / mini_batch.size()) * nabla_b[i][j];

			// Cycle through each weight
			for (int k = 0; k < weights[i][j].size(); k++)
			{
				// Calculate new weight
				weights[i][j][k] -= (eta / mini_batch.size()) * nabla_w[i][j][k];
			}
		}
	}

}

/*Back propagation of input and desire output for gradients in biases and weights
Param ins:				The inputs to the network
Param outs:				The corresponding results of the network
Param nabla_b:			The gradient result for biases
Param nabla_w:			The gradietn result for weights
*/
void Network::Backprop(vector<vector<float>> ins, vector<vector<float>> outs,
	vector<vector<float>>& nabla_b, vector<vector<vector<float>>>& nabla_w)
{
	// Stores the activation of the layer
	vector<vector<float>> activation = ins;
	// Stores the activations for each layer
	vector<vector<vector<float>>> activations = vector<vector<vector<float>>>(numLayers);

	// Assign first layer
	activations[0] = activation;
	// Stores value before logic function
	vector<vector<vector<float>>> zs = vector<vector<vector<float>>>(numLayers-1);

	// Initialize values
	// Cycle thorugh each layer
	for (int i = 0; i < numLayers-1; i++)
	{
		// Initialize activations for layer
		activations[i+1] = vector<vector<float>>(weights[i].size());
		// Initialize zs for layer
		zs[i] = vector<vector<float>>(weights[i].size());

		// Cycle through each element in mini batch
		for (int j = 0; j < weights[i].size(); j++)
		{
			// Initialize activation for mini batch size
			activations[i + 1][j] = vector<float>(ins[0].size(), 0.0f);
			// Initialize zs for mini batch size
			zs[i][j] = vector<float>(ins[0].size(), 0.0f);
		}

		// Cycle through each neuron
		for (int j = 0; j < weights[i].size(); j++)
		{
			// Set bias to zero
			nabla_b[i][j] = 0;

			// Cycle through each weight
			for (int k = 0; k < weights[i][j].size(); k++)
			{
				nabla_w[i][j][k] = 0;
			}
		}
	}

	// Cycle through each layer
	for (int i = 0; i < numLayers-1; i++)
	{
		// Cycle through each neuron
		for (int j = 0; j < weights[i].size(); j++)
		{
			// Cycle through each element in mini batch
			for (int k = 0; k < ins[0].size(); k++)
			{
				// Declare sum
				float sum = 0;

				// Cycle through each weight
				for (int l = 0; l < weights[i][j].size(); l++)
				{
					// Increment sum by weight
					sum += weights[i][j][l] * activation[l][k];
				}

				// Add bias
				sum += biases[i][j];

				// Assign to zs
				zs[i][j][k] = sum;
			}
		}

		// Calculate new activation
		activation = vector<vector<float>>(zs[i].size());
		// Cycle through each neuron
		for (int j = 0; j < sizes[i+1]; j++)
		{
			// Initialize activation term
			activation[j] = vector<float>(ins[0].size(), 0.0f);

			// For each mini batch
			for (int k = 0; k < ins[0].size(); k++)
			{
				// Update activation
				activation[j][k] = LogicF(zs[i][j][k]);
			}
		}

		// Store activation of layer
		activations[i+1] = activation;
	}

	// Back propagation
	// Calculate delta
	vector<vector<float>>delta = Cost(activations.back(), outs);
	// Initialize prime to derivative of logic function
	vector<vector<float>>prime = LogicFPrime(zs.back());
	// Iterate through output
	for (int i = 0; i < activations.back().size(); i++)
	{
		// Iterate through mini batch
		for (int j = 0; j < ins[0].size(); j++)
		{
			// Convert delta to gradient
			delta[i][j] *= prime[i][j];
		}
	}

	// Cycle through neurons in last layer
	for (int i = 0; i < sizes.back(); i++)
	{
		// Cycle through mini batches
		for (int j = 0; j < ins[0].size(); j++)
		{
			// Assign nabal_b last layer to delta
			nabla_b[numLayers - 2][i] += delta[i][j];

			// Cycle through weights in each neuron
			for (int k = 0; k < weights[numLayers - 2][i].size(); k++)
			{
				// Calculate delta_nabla_w
				nabla_w[numLayers - 2][i][k] += delta[i][j] * activations[numLayers - 2][k][j];
			}
		}
	}

	// Cycle though every layer except last
	for (int i = numLayers-3; i >= 0; i--)
	{
		// Get last z
		vector<vector<float>> z = zs[i];
		// Calculate derivative
		vector<vector<float>> sp = LogicFPrime(z);

		// Reset delta to size of second to last layer and initialize to zero
		vector<vector<float>> delta_temp = vector<vector<float>>(weights[i].size());

		// Cycle through each neuron
		for (int j = 0; j < weights[i].size(); j++)
		{
			// Cycle through each mini batch
			for (int k = 0; k < ins[0].size(); k++)
			{
				// Initialzie to zero
				delta_temp[j] = vector<float>(ins[0].size(), 0.0f);
			}
		}

		// Cycle through neurons in previous layer
		for (int j = 0; j < sizes[i+1]; j++)
		{
			// Cycle through next layer
			for (int k = 0; k < sizes[i + 2]; k++)
			{
				// Cycle through mini batch
				for (int l = 0; l < ins[0].size(); l++)
				{
					delta_temp[j][l] += weights[i + 1][k][j] * delta[k][l] * sp[j][l];
				}
			}
		}

		// Assign to delta
		delta = delta_temp;

		// Cycle through each neuron
		for (int j = 0; j < sizes[i+1]; j++)
		{
			// Cycle through each mini batch
			for (int k = 0; k < ins[0].size(); k++)
			{
				// Assign to end of delta_nabla_b
				nabla_b[i][j] += delta[j][k];

				// Cycle through each weight
				for (int l = 0; l < weights[i][j].size(); l++)
				{
					// Calculate delta_nabla_w
					nabla_w[i][j][l] += delta[j][k] * activations[i][l][k];
				}
			}
		}
	}

}

/* Evaluate test_data
3 dimensional array
first argument is for number of test data
[n][0] is input
[n][1] is output
*/
int Network::Evaluate(vector<vector<vector<float>>> test_data)
{
	// Number of correct results
	int result = 0;

	// Cycle through test_data
	for (int i = 0; i < test_data.size(); i++)
	{
		// Assign input
		vector<float>input = test_data[i][0];
		// Assign output
		vector<float>output = test_data[i][1];
		// Calculate ideal response
		int idealResults = distance(output.begin(), max_element(output.begin(), output.end()));

		vector<float>realOut = FeedForward(input);

		// Calculate actual response
		int results = distance(realOut.begin(), max_element(realOut.begin(), realOut.end()));
		// If real equal ideal increment results
		if (results == idealResults) result++;
	}

	// Return result
	return result;
}