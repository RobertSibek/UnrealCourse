#pragma once
#include <string>

// to make compiler Unreal friendly
using FString = std::string;
using int32 = int;

// defining constants
constexpr int32 MAX_TRIES = 5;
constexpr int32 FIRST_TRY = 1;
const FString HIDDEN_WORD = "planet";

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid,
	Not_LowerCase,
	OK,
	Not_Isogram,
	Wrong_Length,
	Empty_String
};


/*
	The core functionality of the game
*/
class FBullCowGame {
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	bool bGameWon;
	FString MyHiddenWord;
	bool IsWordIsogram(FString) const;
	bool IsWordIsogramBen(FString) const;
	bool IsLowerCase(FString) const;
};