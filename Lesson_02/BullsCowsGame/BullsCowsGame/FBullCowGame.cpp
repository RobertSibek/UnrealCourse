#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLength() const { return HIDDEN_WORD.length(); }

void FBullCowGame::Reset()
{
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

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (false) {
		return EGuessStatus::Not_Isogram;
	}
	else if (guess == "") {
		return EGuessStatus::Empty_String;
	}
	else if (guess.length() != GetWordLength()) {
		return EGuessStatus::Wrong_Length;
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
		

		// loop through all letters in the guess
		int32 WordLength = MyHiddenWord.length();
		int32 GuessLength = Guess.length();

		for (int32 i = 0; i < WordLength; i++) {
			// compare letters against the hidden word
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
