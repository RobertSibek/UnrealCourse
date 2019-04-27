#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLength() const { return HIDDEN_WORD.length(); }
int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 6}, {5, 7}, {6, 10}, {7, 15} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plamer";
	MyCurrentTry = FIRST_TRY;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

bool FBullCowGame::IsWordIsogram(FString word) const{
	for (int32 i = 0; i < word.length(); i++) {
		for (int32 j = i + 1; j < word.length(); j++) {
			if (word[i] == word[j]) {
				return false;
			}
		}
	}
	return true;
}

bool FBullCowGame::IsWordIsogramBen(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() == 0) { return false; }

	for (auto Letter : Word) {
		if (Letter == '\0' || Letter == ' ') { return false; }
		if (isupper(Letter)) {
			return false;
		}
	}

	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (guess == "") {
		return EGuessStatus::Empty_String;
	}
	else if (!IsLowerCase(guess)) {
		return EGuessStatus::Not_LowerCase;
	}
	else if (guess.length() != GetWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsWordIsogramBen(guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else {
		return EGuessStatus::OK;
	}
	
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	FBullCowCount BullCowCount;
	if (!bGameWon) {
		MyCurrentTry++;
		int32 WordLength = MyHiddenWord.length();
		int32 GuessLength = Guess.length();
		for (int32 i = 0; i < WordLength; i++) {
			for (int32 j = 0; j < GuessLength; j++) {
				if (Guess[j] == MyHiddenWord[i]) {
					if (i == j) {
						BullCowCount.Bulls++;
					}
					else {
						BullCowCount.Cows++;
					}
				}
			}
		}
	}

	if (Guess == MyHiddenWord) {
		bGameWon = true;
	}

	return BullCowCount;
}
