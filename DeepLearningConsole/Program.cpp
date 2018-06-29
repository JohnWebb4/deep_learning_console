#include "stdafx.h"

// Needed for cin and cout
#include <iostream>
// Needed for string
#include <string>
// Needed for vector
#include <vector>
// Needed for if and off streams
#include <fstream>
// Needed for transform
#include <algorithm>
// Needed for function
#include <functional>
// Needed for thread
#include <thread>
// Needed for chrono::seconds
#include <chrono>


// Declare namespace
using namespace std;

/* Load input, output, biases, and weights from current folder
Param fbiases:		File to read biases from
Param fweights:		File to read weights from
Param fsizes:		File to read sizes from
Param ftraind:		File to read training data from
Param fEta:			File to read learning rate from
Param console:		Console to assign values to
Param train_data:	Training data to write to
Param eta:			Learning rate to write to
*/
void Load(ifstream &fbiases, ifstream &fweights, ifstream &fsizes,
	ifstream &ftraind, ifstream &fEta, DLConsole &console,
	vector<vector<string>> &train_data, float &eta)

{
	// Alert user
	cout << StringTable.at(StringReading) << F_SIZES_NAME << endl;
	// Load sizes
	// Declare temporary sizes
	vector<int> viSizes;
	// Declare temporary string to hold size
	int iSize;
	// If can read from file
	while (fsizes >> iSize)
	{
		// Add to viSizes
		viSizes.emplace_back(iSize);
	}
	// Alert complete
	cout << StringTable.at(StringReading) << F_SIZES_NAME <<
		StringTable.at(StringComplete) << endl;

	// Reconstruct console
	console = DLConsole::DLConsole(viSizes);

	// Close sizes file
	fsizes.close();

	// Alert user
	cout << StringTable.at(StringReading) << F_BIASES_NAME << endl;
	cout << StringTable.at(StringReading) << F_WEIGHTS_NAME << endl;
	// Load biases and weights
	// Cycle through layers
	for (int i = 0; i < console.numLayers - 1; i++)
	{
		// Cycle through neurons
		for (int j = 0; j < console.sizes[i + 1]; j++)
		{
			// Declare temporary bias
			float bias;
			// Attempt to read bias
			if (fbiases >> bias)
			{
				// Assign bias
				console.biases[i][j] = bias;
			}
			// Else alert
			else
			{
				// EOF reached
				cout << StringTable.at(StringEOF) << F_BIASES_NAME << endl;
			}

			// Cycle through weights
			for (int k = 0; k < console.weights[i][j].size(); k++)
			{
				// Declare temporary weights
				float weight;
				// Attempt to read weight
				if (fweights >> weight)
				{
					// Assign weight
					console.weights[i][j][k] = weight;
				}
				// Else alert
				else
				{
					// EOF reached
					cout << StringTable.at(StringEOF) << F_WEIGHTS_NAME << endl;
				}
			}
		}
	}
	// Close bias and weights
	fbiases.close();
	fweights.close();
	// Alert done reading
	cout << StringTable.at(StringReading) << F_BIASES_NAME <<
		StringTable.at(StringComplete) << endl;
	cout << StringTable.at(StringReading) << F_WEIGHTS_NAME <<
		StringTable.at(StringComplete) << endl;

	// Alert user
	cout << StringTable.at(StringReading) << F_TRAIN_DATA_NAME << endl;
	// Load training data
	// Declare temporary training data to write to
	vector<vector<string>> vvsTrain;
	// Declare temporary training data to write to
	vector<string> vsTrain = vector<string>(2);
	// Declare random string to read to
	string sTrain;
	// While can read
	while (getline(ftraind, sTrain))
	{
		// Convert input to lower
		transform(sTrain.begin(), sTrain.end(), sTrain.begin(), tolower);

		// Assign to training data input
		vsTrain[0] = (sTrain);

		// read output
		if (getline(ftraind, sTrain))
		{
			// Assign output
			vsTrain[1] = (sTrain);
		}
		else
		{
			// Alert user
			cout << StringTable.at(StringEOF) << F_TRAIN_DATA_NAME << endl;
		}

		// Assign to training data
		vvsTrain.emplace_back(vsTrain);
	}

	// Assign to training data
	train_data = vvsTrain;

	// Alert user
	cout << StringTable.at(StringReading) << F_TRAIN_DATA_NAME <<
		StringTable.at(StringComplete) << endl;
	// Close training data
	ftraind.close();

	// Alert loading eta
	cout << StringTable.at(StringReading) << F_ETA_NAME << endl;
	// Load temporary learning rate
	float tempEta;
	// Load eta
	if (fEta >> tempEta)
	{
		// Assign learning rate
		eta = tempEta;
	}
	else
	{
		// Alert user EOF
		cout << StringTable.at(StringEOF) << F_ETA_NAME << endl;
	}
	// Alert user
	cout << StringTable.at(StringReading) << F_ETA_NAME <<
		StringTable.at(StringComplete) << endl;

	// Alert completly done
	cout << StringTable.at(StringReading) <<
		StringTable.at(StringComplete) << endl;
}

/* Save input, output, biases, and weights to current folder
Param console:		Console to save values from
Param train_data:	Training data to save values from
Param eta:			Current learning rate
*/
void Save(DLConsole &console, vector<vector<string>> &train_data, float &eta)
{
	ofstream fbiases(F_BIASES_NAME);
	ofstream fweights(F_WEIGHTS_NAME);
	ofstream fsizes(F_SIZES_NAME);
	ofstream ftraind(F_TRAIN_DATA_NAME);
	ofstream fEta(F_ETA_NAME);

	// Write files
	// Alert user
	cout << StringTable.at(StringSaving) << F_BIASES_NAME << endl;
	cout << StringTable.at(StringSaving) << F_WEIGHTS_NAME << endl;
	// Cycle through layers
	for (int i = 0; i < console.numLayers - 1; i++)
	{
		// Cycle through neurons
		for (int j = 0; j < console.sizes[i + 1]; j++)
		{
			// Write bias
			fbiases << console.biases[i][j] << endl;

			// Cycle through weights
			for (int k = 0; k < console.weights[i][j].size(); k++)
			{
				// Write weights
				fweights << console.weights[i][j][k] << endl;
			}
		}
	}
	// Close biases and weights
	fbiases.close();
	fweights.close();
	// Alert user
	cout << StringTable.at(StringSaving) << F_BIASES_NAME <<
		StringTable.at(StringComplete) << endl;
	cout << StringTable.at(StringSaving) << F_WEIGHTS_NAME <<
		StringTable.at(StringComplete) << endl;

	// Alert user
	cout << StringTable.at(StringSaving) << F_SIZES_NAME << endl;
	// Cycle through sizes
	for (int i = 0; i < console.sizes.size(); i++)
	{
		// Write sizes
		fsizes << console.sizes[i] << endl;
	}
	// Close sizes
	fsizes.close();
	// Alert user
	cout << StringTable.at(StringSaving) << F_SIZES_NAME <<
		StringTable.at(StringComplete) << endl;

	// Alert user
	cout << StringTable.at(StringSaving) << F_TRAIN_DATA_NAME << endl;
	// Cycle through training data
	for (int i = 0; i < train_data.size(); i++)
	{
		// Cycle through input and output
		for (int j = 0; j < train_data[i].size(); j++)
		{
			// Write training data string
			ftraind << train_data[i][j] << endl;
		}
	}
	// Close training data
	ftraind.close();
	// Alert user
	cout << StringTable.at(StringSaving) << F_TRAIN_DATA_NAME <<
		StringTable.at(StringComplete) << endl;

	// Alert saving
	cout << StringTable.at(StringSaving) << F_ETA_NAME << endl;
	// Save eta
	fEta << eta << endl;	
	// Close eta
	fEta.close();
	// Alert user
	cout << StringTable.at(StringSaving) << F_ETA_NAME <<
		StringTable.at(StringComplete) << endl;

}

/* Train Network Using SGD
Param console:				Console to change values of
Param training_data:		Training data to write to
Param trainInputs:			Number of training inputs
Param epochs:				Number of epochs (iterations around training data)
Param eta:					Learning Rate
Param mini_batch_size:		Mini Batch Size
Param breakOnPerfect:		Should Break on perfect test evaluation
*/
void ResetTrain(DLConsole &console, vector<vector<string>> &training_data, int trainInputs,
	int epochs, float eta, int mini_batch_size, bool breakOnPerfect)
{
	// Reset training data
	training_data = vector<vector<string>>();

	// Train
	Train(console, training_data, trainInputs, epochs, eta, mini_batch_size, breakOnPerfect);
}

/* Train Network Using SGD
Param console:				Console to change values of
Param training_data:		Training data to write to
Param trainInputs:			Number of training inputs
Param epochs:				Number of epochs (iterations around training data)
Param eta:					Learning Rate
Param mini_batch_size:		Mini Batch Size
Param breakOnPerfect:		Should Break on perfect test evaluation
*/
void Train(DLConsole &console, vector<vector<string>> &training_data, int trainInputs,
	int epochs, float eta, int mini_batch_size, bool breakOnPerfect)
{
	// Declare training data
	vector<vector<string>> train_data = vector<vector<string>>(trainInputs);

	// Add break
	cout << endl;

	// Cycle up to trainingInputs
	for (int i = 0; i < trainInputs; i++)
	{
		// Define test_data
		train_data[i] = vector<string>(2);

		// Ask for input
		cout << StringTable.at(StringWhatYouType) << endl;
		// Declare temporary string for response
		string sIn;
		// Get input
		getline(cin, sIn);

		// Convert to lowercase
		transform(sIn.begin(), sIn.end(), sIn.begin(), tolower);

		// Assign to inputS
		train_data[i][0] = sIn;

		// Ask for response
		cout << StringTable.at(StringShouldSay) << endl;
		// Declare temporary string for response
		string sOut;
		// Get response
		getline(cin, sOut);
		// Assign to outputs
		train_data[i][1] = sOut;
	}

	// Alert user out of size
	cout << StringTable.at(StringOutOfInputs) << endl;

	// Cycle through train_data
	for (int i = 0; i < train_data.size(); i++)
	{
		// If train_data input is not present
		// in training data then add to end
		// Otherwise override output

		// Declare boolean for input not present anywhere in
		// training data
		bool bNotInput = true;
		// Cycle through training data
		for (int j = 0; j < training_data.size(); j++)
		{
			// If equal inputs
			if (train_data[i][0] == training_data[j][0])
			{
				// Is an input, set bNotInput to false
				bNotInput = false;
				// Overwrite output with train_data output
				training_data[j][1] = train_data[i][1];
				// Break training search
				break;
			}
		}
		// If not a previous input
		if (bNotInput)
		{
			// Add to overall training data
			training_data.emplace_back(train_data[i]);
		}
	}

	// Alert training network
	cout << StringTable.at(StringTraining) << endl;
	// Start Stoichastic Gradient Descent
	// console.SGD(training_data, epochs, mini_batch_size, eta, training_data, breakOnPerfect);
}


/* Train in background
Param exitTest:			Is the testing done?
Param console:			Console to train with
Param train_data:		Data to train against
Param mini_batch_size:	The size of a mini batch
Param eta:				Learning rate
*/
void BackTrain(bool &exitTest, bool &training, DLConsole &console, vector<vector<string>> &train_data,
	int &mini_batch_size, float &eta, float &etaSpeed)
{
	// If training elsewhere
	if (training)
	{
		// return
		return;
	}
	// Else traing
	else
	{
		// Set training to true
		training = true;

		// Declare previous Passes
		int prevPasses = 0;

		// While testing
		while (!exitTest)
		{
			// Test training data
			int iPasses = console.Evaluate(train_data);

			// If perfect run
			if (iPasses == train_data.size())
			{
				// Alert user
				cout << StringTable.at(StringTraining) << iPasses <<
					StringTable.at(StringOf) << train_data.size() <<
					StringTable.at(StringComplete) << endl;

				// End training
				training = false;
				// Return
				return;
			}
			// Else if improvement over last run
			else if (iPasses != prevPasses)
			{
				// Alert user
				cout << StringTable.at(StringTraining) << iPasses <<
					StringTable.at(StringOf) << train_data.size() << endl;
			}
			else
			{
				// Background training one epoch
				console.SGD(train_data, 1, mini_batch_size, eta);
			}

			// Check if any weight or bias is NAN
			// If so, reset to zero
			// Cycle through layers
			for (int i = 0; i < console.numLayers - 1; i++)
			{
				// Cycle through neurons
				for (int j = 0; j < console.sizes[i + 1]; j++)
				{

					// If bias is NAN reset console
					if (isnan(console.biases[i][j]) || 
						isinf(console.biases[i][j]))
					{
						// Reset console
						console = DLConsole(console.sizes);

						// Alert user
						cout << StringTable.at(StringReset) <<
							StringTable.at(StringBias) << i <<
							StringTable.at(StringOf) << j << endl;

						// Slow learning rate
						eta = Slow(eta, etaSpeed);
					}

					// Cycle through weights
					for (int k = 0; k < console.weights[i][j].size(); k++)
					{
						// If weight is NAN reset console
						if (isnan(console.weights[i][j][k]) || 
							isinf(console.weights[i][j][k]))
						{
							// Reset console
							console = DLConsole(console.sizes);

							// Alert user
							cout << StringTable.at(StringReset) <<
								StringTable.at(StringWeight) << i <<
								StringTable.at(StringOf) << j <<
								StringTable.at(StringOf) << k << endl;

							// Slow learning rate
							eta = Slow(eta, etaSpeed);
						}
					}
				}
			}

			// Assign previous passes
			prevPasses = iPasses;
		}
	}
}

/* Displays Help message
*/
void Help()
{
	// Add break
	cout << endl;

	// Done loading network
	// Explain test to user
	cout << StringTable.at(StringTestPrompt) << endl;

	// Add break
	cout << endl;

	// Explain commands
	cout << StringTable.at(StringHelpMessage) << endl;
	cout << StringTable.at(StringSaveMessage) << endl;
	cout << StringTable.at(StringTrainMessage) << endl;
	cout << StringTable.at(StringResetMessage) << endl;
	cout << StringTable.at(StringNoMessage) << endl;
	cout << StringTable.at(StringExitMessage) << endl;
	cout << StringTable.at(StringFastMessage) << endl;
	cout << StringTable.at(StringSlowMessage) << endl;
	cout << StringTable.at(StringConsoleMessage) << endl;
	cout << StringTable.at(StringInputsMessage) << endl;

	// Add break
	cout << endl;
}

/* Increment learning rate by speed factor
Param eta:		The learning rate
Param etaSpeed:	The percentage increase
Returns:		The new learning rate
*/
float Fast(float eta, float etaSpeed)
{
	// Declare new learning rate
	float result = eta * etaSpeed;

	// Write new learning rate
	cout << StringTable.at(StringEta) << result << endl;

	// Scale eta and return
	return result;
}

/* Decrement learning rate by speed factor
Param eta:		The learning rate
Param etaSpeed:	The percentage decrease
Returns:		The new learning rate
*/
float Slow(float eta, float etaSpeed)
{
	// Declare new learning rate
	float result = eta / etaSpeed;

	// Write new learning rate
	cout << StringTable.at(StringEta) << eta << endl;

	// Scale eta and return
	return result;
}

/* Write bias and weights to screen
Param console:		Console to read bias and weights
Param train_data:	The current training data
*/
void ConsoleSumm(DLConsole &console, vector<vector<string>> &train_data)
{
	// Calculate anything outside of two
	// Standard deviations
	// Declare floats sum, mean, count and stand dev for biases
	float biasSum = 0.0f, biasMean = 0.0f, biasCount = 0.0f, biasSD = 0.0f;
	// Declare floats sum, mean, coutn and stand dev for weights
	float weightSum = 0.0f, weightMean = 0.0f, weightCount = 0.0f, weightSD = 0.0f;
	// Declare number of acceptable standard deviations
	const float acceptDevs = 2.0f;

	// Cycle through bias and weights
	// Cycle through layers
	for (int i = 0; i < console.numLayers - 1; i++)
	{
		// Add bias count
		biasCount += console.biases[i].size();

		// Cycle through neurons
		for (int j = 0; j < console.sizes[i + 1]; j++)
		{
			// Sum bias
			biasSum += console.biases[i][j];

			// Add weight count
			weightCount += console.weights[i][j].size();

			// Cycle through weights
			for (int k = 0; k < console.weights[i][j].size(); k++)
			{
				// Sum weights
				weightSum += console.weights[i][j][k];
			}
		}
	}

	// Calculate bias and weight means
	biasMean = biasSum / biasCount;
	weightMean = weightSum / weightCount;

	// Calculate standard deviation
	// Cycle through layers
	for (int i = 0; i < console.numLayers - 1; i++)
	{
		// Cycle through neurons
		for (int j = 0; j < console.sizes[i + 1]; j++)
		{
			// Sum standard deviation
			biasSD += pow(console.biases[i][j] - biasMean, 2);

			// Cycle through weights
			for (int k = 0; k < console.weights[i][j].size(); k++)
			{
				// Sum standard deviation
				weightSD += pow(console.weights[i][j][k] - weightMean, 2);
			}
		}
	}

	// Calculate standard deviation
	biasSD = biasSD / biasCount;
	weightSD = weightSD / weightCount;

	// Add break
	cout << endl;

	// Write biases and weights outside x standard deviations
	for (int i = 0; i < console.numLayers-1; i++)
	{
		// Cycle through each neuron
		for (int j = 0; j < console.sizes[i+1]; j++)
		{
			// If outside x standard deviations
			if (abs(console.biases[i][j] - biasMean) > (acceptDevs * biasSD))
			{
				// Write bias
				cout << StringTable.at(StringBias) <<
					i << StringTable.at(StringOf) <<
					j << StringTable.at(StringColon) <<
					console.biases[i][j] << endl;
			}

			// Cycle through weights
			for (int k = 0; k < console.weights[i][j].size(); k++)
			{
				// If outside x standard deviations
				if (abs(console.weights[i][j][k] - weightMean) > (acceptDevs * weightSD))
				{
					// Write weight
					cout << StringTable.at(StringWeight) <<
						i << StringTable.at(StringOf) <<
						j << StringTable.at(StringOf) <<
						k << StringTable.at(StringColon) <<
						console.weights[i][j][k] << endl;
				}
			}
		}
	}

	// Add break
	cout << endl;

	// Evaluate training data and write response
	cout << StringTable.at(StringTraining) << console.Evaluate(train_data) <<
		StringTable.at(StringOf) << train_data.size() << endl;
}

/* Write training data to screen
Param trainData:	The training data to write
Param eta:			The current learning rate
*/
void Inputs(vector<vector<string>> &trainData, float &eta)
{
	// Add break
	cout << endl;

	// Write training data
	cout << StringTable.at(StringTraining);

	// Cycle through training data
	for (int i = 0; i < trainData.size(); i++)
	{
		// Ask for input
		cout << StringTable.at(StringWhatYouType) << endl;
		// Write input
		cout << trainData[i][0] << endl;

		// Ask for response
		cout << StringTable.at(StringShouldSay) << endl;
		// Write outputs
		cout << trainData[i][1] << endl;
	}

	// Write learning rate
	cout << StringTable.at(StringEta) << eta << endl;

	// Add break
	cout << endl;
}

/* Console network. Queries input and returns response
*/
int main()
{
	// Declare max words per response
	int iMaxWords = 1;

	// Declare and Initialize Neural Network Console
	DLConsole console = DLConsole::DLConsole({ iMaxWords, iMaxWords, iMaxWords, iMaxWords });

	// Define epochs
	int epochs = 4000;

	// Define learning rate
	float eta = 0.00001f;

	// Define learning rate speed factor
	float etaSpeed = 1.1; // 10% change

	// Should stop SGD on perfect test data run?
	bool breakOnPerfect = true;

	// Exit testing
	bool exitTest = false;

	// Declare training data size
	vector<vector<string>> train_data = vector<vector<string>>(console.sizes.front());

	// Define test data
	vector<vector<vector<float>>> test_data;

	// Define holder for previous response
	string sPrevResponse;

	// Define holder for previous output
	string sPrevOutput;

	// Define number of string inputs for training
	int trainInputs = 5;

	// Define mini batch size
	int mini_batch_size = trainInputs;

	// Define sleep times after thread
	int iThreadSleep = 1000; // second

	// Attempt to populate network
	// Attempt to load network (if fails train network)
	// Attempt to open biases file
	ifstream fbiases(F_BIASES_NAME);

	// Attempt to open weights file
	ifstream fweights(F_WEIGHTS_NAME);

	// Attempt to open sizes file
	ifstream fsizes(F_SIZES_NAME);

	// Attempt to open train_data
	ifstream ftraind(F_TRAIN_DATA_NAME);

	// Attempt to open learning rate
	ifstream fEta(F_ETA_NAME);

	// If all files exist, read values
	if (fbiases.is_open() && fweights.is_open() &&
		fsizes.is_open() &&	ftraind.is_open() &&
		fEta.is_open())
	{
		// Load files
		Load(fbiases, fweights, fsizes, ftraind, fEta, console, train_data, eta);
	}
	else
	{
		// If one of the files exists but missing one or more
		if (fbiases.is_open() || fweights.is_open() ||
			fsizes.is_open() || ftraind.is_open() ||
			fEta.is_open())
		{
			// Cycle through files to find missing
			// If missing biases
			if (!fbiases.is_open()) cout << StringTable.at(StringMissing)  << F_BIASES_NAME << endl;
			// If missing weights
			if (!fweights.is_open()) cout << StringTable.at(StringMissing) << F_WEIGHTS_NAME << endl;
			// If missiong sizes
			if (!fsizes.is_open()) cout << StringTable.at(StringMissing) << F_SIZES_NAME << endl;
			// If missing training data
			if (!ftraind.is_open()) cout << StringTable.at(StringMissing) << F_TRAIN_DATA_NAME << endl;
			// If missing learning reate
			if (!fEta.is_open()) cout << StringTable.at(StringMissing) << F_ETA_NAME << endl;

			// Alert cannot open network
			cout << StringTable.at(StringCannotLoad) << endl;
			cout << StringTable.at(StringEnterToClose);
			// Wait user input
			cin.get();
			// Return
			return 0;
		}
		// If missing all files
		else
		{
			// Alert user
			cout << StringTable.at(StringNoPreviousData) << endl;

			// Add break
			cout << endl;

			// Train network
			ResetTrain(console, train_data, trainInputs, epochs, eta, mini_batch_size, breakOnPerfect);

			// Alert finished
			cout << StringTable.at(StringRemember) << endl;
		}
	}

	// Display Help
	Help();

	// Declare bool for training and initialize to false
	bool training = false;

	// Declare previous training data
	vector<vector<string>> prevTrainData = vector<vector<string>>(train_data.size());

	// Loop until exit
	while (!exitTest)
	{
		// If training data has changed
		if (prevTrainData != train_data)
		{
			// If not currently training
			if (!training)
			{
				// Start new training
				thread tBackTrain(BackTrain, ref<bool>(exitTest), ref<bool>(training), ref<DLConsole>(console),
					ref<vector<vector<string>>>(train_data), ref<int>(mini_batch_size), ref<float>(eta),
					ref<float>(etaSpeed));

				// Detach from main process
				tBackTrain.detach();
			}

		}

		// Write previous training data
		prevTrainData = train_data;

		// Declare string resopnse
		string response;
		// Get response
		getline(cin, response);

		// If exit
		if (response == COMMAND_EXIT)
		{
			// Set flag
			exitTest = true;
		}

		// Check commands
		// If save
		else if (response == COMMAND_SAVE)
		{
			// Save network to files
			Save(console, train_data, eta);
		}

		// If train
		else if (response == COMMAND_TRAIN)
		{
			// Alert training
			cout << StringTable.at(StringTraining) << endl;
			// Train
			Train(console, train_data, trainInputs, epochs, eta, mini_batch_size, breakOnPerfect);
			// Alert continuously training
			cout << StringTable.at(StringRemember) << endl;
		}
		// If reset
		else if (response == COMMAND_RESET)
		{
			// Prompt confimration
			cout << StringTable.at(StringHardConfirm) << endl;
			// Get response. Assign to temporary variable
			string s;
			// Get response
			getline(cin, s);
			// If Hard confirmation
			if (s == CONSOLE_HARD_CONFIRM)
			{
				// Reset network
				ResetTrain(console, train_data, trainInputs, epochs, eta, mini_batch_size, breakOnPerfect);
			}
		}
		// If NO
		else if (response == COMMAND_NO)
		{
			// Ask for desired response
			cout << StringTable.at(StringShouldSay) << endl;
			// Declare temporary output
			string output;
			// Get desired output
			getline(cin, output);

			// Create boolean for not a previous training input
			bool bNotInput = true;

			// Cycle through training inputs
			for (int i = 0; i < train_data.size(); i++)
			{
				// If previous resoponse is in training data inputs
				if (sPrevResponse == train_data[i][0])
				{
					// Since input, bNotInput is false
					bNotInput = false;
					// Overwrite
					train_data[i][1] = output;
					// Break for loop
					break;
				}
			}
			// If not an training data input, add
			if (bNotInput)
			{
				// Create temporary train data
				vector<string> train = { sPrevResponse, output };

				// Add to training data
				train_data.emplace_back(train);
			}

			// Alert user
			cout << StringTable.at(StringRemember) << endl;
		}
		else if (response == COMMAND_HELP)
		{
			// Display help
			Help();
		}
		// Else if fast
		else if (response == COMMAND_FAST)
		{
			eta = Fast(eta, etaSpeed);
		}
		// Else if slow
		else if (response == COMMAND_SLOW)
		{
			eta = Slow(eta, etaSpeed);
		}
		// Else if summary
		else if (response == COMMAND_CONSOLE)
		{
			// Call inputs with current
			// Training data.
			ConsoleSumm(console, train_data);
		}
		// Else if inputs
		else if (response == COMMAND_INPUTS)
		{
			// Call inputs with current
			// Training data
			Inputs(train_data, eta);
		}
		// Else feedforward
		else
		{
			// Convert to lowercase
			transform(response.begin(), response.end(), response.begin(), tolower);
			// Return response
			sPrevOutput = console.FeedForward(response);
			// Write response
			cout << sPrevOutput << endl;
		}

		// Write previous response
		sPrevResponse = response;
	}
}