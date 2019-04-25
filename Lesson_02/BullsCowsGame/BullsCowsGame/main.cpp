// BullsCows Game - Lesson_02 from Unreal C++ Course
// Coded by Robert Sibek

#include <iostream>
#include <string>
#include <Windows.h>
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText guess);
void SummarizeGame();
bool AskToPlayAgain();
void FillChar(char c, int32 count);

FBullCowGame BCGame;
enum Colors { blue = 1, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };

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
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
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

	if (BCGame.IsGameWon()) {
		SummarizeGame();
	}

	// TODO Summarize the game
}

void SummarizeGame() {
	TextColor(green);
	FText msg = "Congratulations! You have Won the game.";
	FillChar('=', msg.length());
	std::cout << msg;
	FillChar('=', msg.length());
}

void FillChar(char c, int32 count) {
	std::cout << std::endl;
	for (int32 i = 0; i < count; i++) {
		std::putchar(c);
	}
	std::cout << std::endl;

}

void PrintIntro() {
	//for (int32 c = 1; c < 15; c++) {
	//	TextColor(c);
	//	std::cout << "Line color " << c << std::endl;
	//}
	// TODO Provide more beautiful intro
	constexpr int32 WORD_LENGTH = 5;
	TextColor(hwhite);
	std::cout << "===== Welcome to Bulls and Cows =====" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetWordLength() << " letter word?" << std::endl << std::endl;
}

FText GetValidGuess() {
	EGuessStatus GuessStatus = EGuessStatus::Invalid;
	FText guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		TextColor(hblue);
		std::cout << CurrentTry << ". What is your Guess? ";
		getline(std::cin, guess);

		GuessStatus = BCGame.CheckGuessValidity(guess);
		TextColor(red);
		switch (GuessStatus) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << " letter word.";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Plese enter a valid Isogram.";
			break;
		case EGuessStatus::Empty_String:
			std::cout << "Please enter non empty string.";
			break;
		default:
			break;
		}

		std::cout << "\n";
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
