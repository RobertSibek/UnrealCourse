#include <iostream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "FBullCowGame.h"

// to make compiler Unreal friendly
using FText = std::string;

// Method prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText guess);
void PrintGameSummary();
bool AskToPlayAgain();
void FillChar(char c, int32 count);
void PrintColorPreview();

FBullCowGame BCGame;
enum Colors { blue = 1, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };


/*
	Main Entry for the game
*/
int main() {

	do {
		BCGame.Reset();
		std::cout << std::endl;
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void TextColor(int32 color)
{
#ifdef _WIN32
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
#endif
}

void PrintColorPreview() {
	for (int i = 1; i <= Colors::hwhite; i++) {
		TextColor(i);
		std::cout << "This is text in Colors[" << i << "]" << std::endl;
	}
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		if (!BCGame.IsGameWon()) {
			TextColor(hred);
			std::cout << "Bulls = " << BullCowCount.Bulls << ", ";
			std::cout << "Cows = " << BullCowCount.Cows;
			std::cout << std::endl;
		}
	}
	PrintGameSummary();
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		TextColor(green);
		FText msg = "Congratulations! You have Won the game.";
		FillChar('=', msg.length());
		std::cout << msg;
		FillChar('=', msg.length());
	}
	else {
		TextColor(grey);
		FText msg = "Bad luck. Maybe next time.";
		FillChar('=', msg.length());
		std::cout << msg;
		FillChar('=', msg.length());
	}

}

void FillChar(char c, int32 count) {
	std::cout << std::endl;
	for (int32 i = 0; i < count; i++) {
		std::putchar(c);
	}
	std::cout << std::endl;
}

void PrintIntro() {
	constexpr int32 WORD_LENGTH = 5;
	TextColor(hwhite);
	FString WelcomeMsg = "===== Welcome to Bulls and Cows =====";
	FillChar('=', WelcomeMsg.length());
	std::cout << WelcomeMsg;
	FillChar('=', WelcomeMsg.length());
	std::cout << "Can you guess the " << BCGame.GetWordLength() << " letter word?" << std::endl << std::endl;
}

FText GetValidGuess() {
	EGuessStatus GuessStatus = EGuessStatus::Invalid;
	FText guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		TextColor(hblue);
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". What is your Guess? ";
		getline(std::cin, guess);

		GuessStatus = BCGame.CheckGuessValidity(guess);
		TextColor(red);
		switch (GuessStatus) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << " letter word.";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Plese enter non repeating letters.";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all letters in lowercase";
			break;
		case EGuessStatus::Empty_String:
			std::cout << "Please enter non empty string.";
			break;
		default:
			break;
		}
	} while (GuessStatus != EGuessStatus::OK);
	return guess;
}

void PrintBack(FText guess) {
	TextColor(hred);
	std::cout << "Your guess is " << guess << std::endl;
}

bool AskToPlayAgain() 
{
	FText answer = "";
	char c;
	TextColor(hpurple);
	do {
		std::cout << std::endl << "Do you want to play again? (y/n)";
		getline(std::cin, answer);
		c = toupper(answer[0]);

		if (c == 'Y') {
			return true;
		}
		else if (c == 'N') {
			return false;
		}
		else {
			std::cout << "Incorrect answer. Select either (Y)es or (N)o." << std::endl;
		}
	} while (true);
}
