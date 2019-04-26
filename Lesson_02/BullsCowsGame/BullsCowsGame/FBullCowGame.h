#pragma once
#include <string>

using FString = std::string;
using int32 = int;

constexpr int32 MAX_TRIES = 3;
constexpr int32 FIRST_TRY = 1;
const FString HIDDEN_WORD = "planet";

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Empty_String
};

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
};