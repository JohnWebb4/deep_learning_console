#pragma once

#include<map>
#include<string>

// Define String Indecies
const enum StringIndex {
	StringMissing = 0,
	StringCannotLoad,
	StringEnterToClose,
	StringNoPreviousData,
	StringRemember,
	StringSaving,
	StringTraining,
	StringHardConfirm,
	StringShouldSay,
	StringReading,
	StringDoneReading,
	StringEOF,
	StringWhatYouType,
	StringOutOfInputs,
	StringOf,
	StringComplete,
	StringTestPrompt,
	StringHelpMessage,
	StringSaveMessage,
	StringTrainMessage,
	StringResetMessage,
	StringNoMessage,
	StringExitMessage,
	StringEpoch,
	StringColon,
	StringMiniBatchLessTotal,
	StringEta,
	StringFastMessage,
	StringSlowMessage,
	StringBias,
	StringWeight,
	StringReset,
	StringConsoleMessage,
	StringInputsMessage
};

// Holds string table
extern const map<int, string> StringTable;