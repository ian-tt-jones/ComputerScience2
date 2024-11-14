/*****************************************
** File:    Proj1.cpp
** Project: CMSC 202 Project 1, Spring 2022
** Author:  Ian Jones
** Date:    2/22/22
** Section: 10/12
** E-mail:  ijones3@umbc.edu 
**
** This file contains the main driver program for Project 1.
**
** This program gets a random word from a list for the user to guess
** and gives hints as to what the word is until the user gets the word right.
**
***********************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function Declarations

	// load words
	void LoadWords(string wordArray[]);

	// guess word
	string GuessWord(string wordArray[]);

	// check letter
	void CheckLetter(string, string, string guessHistory[2][6], int);

	// check win
	bool CheckWin(string, string);

	// display current
	void DisplayCurrent(string guessHistory[2][6]);


// Global Constants
const int WORD_COUNT = 2315;
const string FILE_NAME = "proj1_data.txt";
const int WORD_LENGTH = 5;
const int NUM_GUESSES = 6;

// here is the main function
int main(){
	// welcome message
	cout << "Welcome to UMBC Wordle!" << endl;

	// declaring the array where the words will be stored
	string wordArray[WORD_COUNT];

	// loading the words
	LoadWords(wordArray);

	// initializing random seed
	srand (time(NULL));

	// boolean for the game to keep going
	bool continuePlaying = true;

	// while loop goes as long as the user answers yes to play again
	while(continuePlaying){

		// message to user
		cout << "Ok. I am thinking of a word with five letters." << endl;

		// generating random num 0 - 2315
		int randIndex = rand() % WORD_COUNT;

		// stores all past guesses
		string guessHistory[2][6] = {{" ", " ", " ", " ", " ", " " },
		{"_____", "_____", "_____", "_____", "_____", "_____", }};

		// random index in the list of words
		string randWord = wordArray[randIndex];

		// main loop for the game, loops 6 times unless the ord is guessed
		for (int i = 0; i < NUM_GUESSES; i++){

			// repeats guess word -> check word -> display until
			// either the word is guessed or all guesses are used

			string guess = GuessWord(wordArray);
			CheckLetter(guess, randWord, guessHistory, i);
			guessHistory[0][i] = guess;
			DisplayCurrent(guessHistory);
			if (CheckWin(guess, randWord)){
				cout << "Congrats you won!";
				cout << "The correct word was: " << randWord << endl;
				i = 6;
			}else if(i == 5){
				cout << "You lose, out of guesses!" << endl;
				cout << "The correct word was: " << randWord << endl;
			}
		}

		// asking user if they want to play again
		char response = ' ';
		do{
			cout << "Another game? y/n" << endl;
			cin >> response;
		}while((response != 'y') and (response != 'n'));
		if (response == 'n'){
			continuePlaying = false;		
			cout << "Thank you!" << endl;
		}
	}

	return 0;	
}

//-------------------------------------------------------
// Name: LoadWords
// PreCondition:  An array has been created and passed into the function.
// PostCondition: Nothing, but inserts the list of words into the array.
//---------------------------------------------------------

void LoadWords(string wordArray[]){

	//loading the words into an array
	fstream wordsFile;
	wordsFile.open( FILE_NAME );

	// loops through the list of words in the file and adds them to an array
	if(wordsFile.is_open()){
		for (int i = 0; i < WORD_COUNT; i++){
			wordsFile >> wordArray[i];
		}
	}else{
		cout << "file is not open" << endl;
	}
	wordsFile.close();

		cout << "2315 words imported." << endl;
	}


//-------------------------------------------------------
// Name: GuessWord
// PreCondition:  An array has been created and passed into the function
//				  which stores all the words that can be guessed. 
// PostCondition: Tells user whether or not their word was valid.
//---------------------------------------------------------

string GuessWord(string wordArray[]){

	string wordGuessed;
	bool wordInList = false;

	
	// loops until the user guesses a word that is in the list of words
	do{
		cout << "What word would you like to guess?" << endl;
		cin >> wordGuessed;

		for (int i = 0; i < WORD_COUNT; i++){
			if(wordGuessed == wordArray[i]){
				wordInList = true;
				i = WORD_COUNT;
			}
		}

		if(! wordInList){
			cout << "That word is not in the list, try again." << endl;
		}

	}while(! wordInList);

	return wordGuessed;
}


//-------------------------------------------------------
// Name: CheckLetter
// PreCondition:  A word has been guessed 
// PostCondition: Displays whether or not a letter is in the right poision
//  			  or in the word at all.
//---------------------------------------------------------

void CheckLetter(string wordGuessed, string wordToGuess, string guessHistory[2][6], int guess){
	for (int i = 0; i < WORD_LENGTH; i++){
		if (wordGuessed[i] == wordToGuess[i]){
			guessHistory[1][guess][i] = '!';
		}
		else{
			for (int j = 0; j < WORD_LENGTH; j++){
				if(wordGuessed[i] == wordToGuess[j]){
					guessHistory[1][guess][i] = '&';
				}
			}
		}
	}
}


//-------------------------------------------------------
// Name: CheckWin
// PreCondition:  A word has been guessed 
// PostCondition: Displays whether or not a letter is in the right poision
//  			  or in the word at all.
//---------------------------------------------------------

bool CheckWin(string wordGuessed, string wordToGuess){
	if(wordGuessed == wordToGuess){
		return true;
	}else{
		return false;
	}
}


//-------------------------------------------------------
// Name: DisplayCurrent
// PreCondition:  Words have been guessed and inserted in the
//				  guess history array.
// PostCondition: Displays the past guesses and how correct they were.
//---------------------------------------------------------

void DisplayCurrent(string guessHistory[2][6]){
	for (int i = 0; i < NUM_GUESSES; i++){
		cout << guessHistory[0][i] << endl;
		cout << guessHistory[1][i] << endl;
	}
}
