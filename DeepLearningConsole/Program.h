#pragma once

// Standard library
#include "stdafx.h"
#include <string>

// Declare namespace
using namespace std;

// Declare filenames
#define F_DICTIONARY_NAME		"dictionary.txt"
#define F_BIASES_NAME			"biases.txt"
#define F_WEIGHTS_NAME			"weights.txt"
#define F_SIZES_NAME			"sizes.txt"
#define F_TRAIN_DATA_NAME		"train_data.txt"
#define F_ETA_NAME				"eta.txt"

// Declare commands
#define COMMAND_SAVE			"SAVE"
#define COMMAND_EXIT			"EXIT"
#define COMMAND_TRAIN			"TRAIN"
#define COMMAND_RESET			"RESET"
#define COMMAND_NO				"NO"
#define COMMAND_HELP			"HELP"
#define COMMAND_FAST			"FAST"
#define COMMAND_SLOW			"SLOW"
#define COMMAND_CONSOLE			"CONSOLE"
#define COMMAND_INPUTS			"INPUTS"

// Declare console magic words
#define CONSOLE_HARD_CONFIRM	"YES"

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
static void Load(ifstream &fbiases, ifstream &fweights, ifstream &fsizes,
	ifstream &ftraind, ifstream &fEta, DLConsole &console,
	vector<vector<string>> &train_data, float &eta);

/* Save input, output, biases, and weights to current folder
Param console:		Console to save values from
Param train_data:	Training data to save values from
Param eta:			Current learning rate
*/
static void Save(DLConsole &console, vector<vector<string>> &train_data, float &eta);

/* Train Network Using SGD
Param console:				Console to change values of
Param training_data:		Training data to write to
Param trainInputs:			Number of training inputs
Param epochs:				Number of epochs (iterations around training data)
Param eta:					Learning Rate
Param mini_batch_size:		Mini Batch Size
Param breakOnPerfect:		Should Break on perfect test evaluation
*/
static void Train(DLConsole &console, vector<vector<string>> &training_data, int trainInputs,
	int epochs, float eta, int mini_batch_size, bool breakOnPerfect);

/* Train Network Using SGD
Param console:				Console to change values of
Param training_data:		Training data to write to
Param trainInputs:			Number of training inputs
Param epochs:				Number of epochs (iterations around training data)
Param eta:					Learning Rate
Param mini_batch_size:		Mini Batch Size
Param breakOnPerfect:		Should Break on perfect test evaluation
*/
static void ResetTrain(DLConsole &console, vector<vector<string>> &training_data, int trainInputs,
	int epochs, float eta, int mini_batch_size, bool breakOnPerfect);

/* Train in background
Param exitTest:			Is the testing done?
Param training:			Currently training elsewhere
Param console:			Console to train with
Param train_data:		Data to train against
Param mini_batch_size:	The size of a mini batch
Param eta:				Learning rate
Param etaSpeed:			Speed learning rate changes (Pecentage change)
*/
static void BackTrain(bool &exitTest, bool &training, DLConsole &console, vector<vector<string>> &train_data,
	int &mini_batch_size, float &eta, float &etaSpeed);

/* Displays Help message
*/
static void Help();

/* Increment learning rate by speed factor
Param eta:		The learning rate
Param etaSpeed:	The percentage increase
Returns:		The new learning rate
*/
static float Fast(float eta, float etaSpeed);

/* Decrement learning rate by speed factor
Param eta:		The learning rate
Param etaSpeed:	The percentage decrease
Returns:		The new learning rate
*/
static float Slow(float eta, float etaSpeed);

/* Write bias and weights to screen
Param console:		Console to read bias and weights
Param train_data:	The current training data
*/
static void ConsoleSumm(DLConsole &console, vector<vector<string>> &train_data);

/* Write training data to screen
Param trainData:	The training data to write
Param eta:			The current learning rate
*/
static void Inputs(vector<vector<string>> &trainData, float &eta);

/* Console network. Queries input and returns response
*/
int main();