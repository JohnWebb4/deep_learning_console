#include "stdafx.h"
// Call string table header
#include "StringTable.h"


// String table
const map<int, string> StringTable = {
	{StringMissing,				"Missing: "},
	{StringCannotLoad,			"Cannot load netowork."},
	{StringEnterToClose,		"Press enter to close."},
	{StringNoPreviousData,		"It seems I don't have any previous information to work with.\nI am going to need to do some training first."},
	{StringRemember,			"I will remember that."},
	{StringSaving,				"Saving "},
	{StringTraining,			"Training . . . "},
	{StringHardConfirm,			"Are you sure? Type (case sensitive): YES"},
	{StringShouldSay,			"What should I say?" },
	{StringReading,				"Reading "},
	{StringEOF,					"End of file before complete "},
	{StringWhatYouType,			"What will you type?"},
	{StringOutOfInputs,			"Out of inputs."},
	{StringOf,					" / "},
	{StringComplete,			" complete."},
	{StringTestPrompt,			"This network will now test what information you give it.\nEnter an input and I will give a response."},
	{StringHelpMessage,			"Type 'HELP' To display this message again."},
	{StringSaveMessage,			"Type 'SAVE' To save your progress."},
	{StringTrainMessage,		"Type 'TRAIN' To train with additional inputs."},
	{StringResetMessage,		"Type 'RESET' To reset the training data."},
	{StringNoMessage,			"Type 'NO' If this is the wrong response."},
	{StringExitMessage,			"Type 'EXIT' to close."},
	{StringFastMessage,			"Type 'FAST' To speed up the learning rate." },
	{StringSlowMessage,			"Type 'SLOW' to slow down the learning rate." },
	{StringConsoleMessage,		"Type 'CONSOLE' To write the current console bias and weights abnormalities" },
	{StringEpoch,				"Epoch "},
	{StringColon,				" : "},
	{StringMiniBatchLessTotal,	"Mini batch size must be less than number of training data."},
	{StringEta,					"Eta: "},
	{StringBias,				"Bias: "},
	{StringWeight,				"Weight: "},
	{StringReset,				"Reset "},
	{StringInputsMessage,		"Type 'INPUTS' To write the training data"}
};