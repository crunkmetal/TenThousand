
/*
10000 - A Dice Game
AKA: Farkle
*/

// preprocessor directives
#include <iostream>
#include <string>
#include <ctime>
#include <istream>
#include <cstdlib>	// for screenclear
#include <algorithm>

//using namespace std;

// global directives
const int MAX_SCORE = 10000;
const int NUM_DICE = 6;
int rolloverScore = 0;
int diceRoll[6];
int numPlayers, reRollingDice;
int scoreThisRound;
bool gameStartStatus = false;
bool reRollers[6] = { false };
int player_score[2] = { 0 };
bool prevArray[NUM_DICE] = { false };
std::string player_names[10];

// function prototypes
int playerCount();
int* rollDice();
void intro();
std::string get_names();
void displayDiceRoll();
void initPlayerScores();
int scoring();
void rollNotification(int);
int firstRoll();
void gameBegins(int*);
void gamePoint(int*);
void displayScores(int*);
void playAgain();
int pointScore(int*);
int reRoll(bool*);
void reRollResponse(int*);
int resetRerollStatus(bool*);
void displayReRollers();
void makePrevReRollerArray();
void showPrevReRollArray();
void reRollAllReRollable();



int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	intro();
	playerCount();
	//player_score[numPlayers] = { 0 };
	player_names[numPlayers];
	// clear screen
	system("CLS");
	get_names();
	initPlayerScores();
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	std::cout << "   *** SCORE 1000 POINTS TO START THE GAME ***\n\n\n\n";
	displayScores(player_score);
	std::cout << "\n\n\n";
	std::cout << "\n [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	// pause for user input
	system("pause>nul|set/p =START ...");
	// clear screen
	system("CLS");
	// Start rolling until someone scores 1000 points
	while (scoreThisRound < 1000 && gameStartStatus == false)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
			std::cout << " PLAYER:\t" << player_names[i] << " " << player_names[i] << " " << player_names[i] << " " << player_names[i] << " " << player_names[i] << "\n";
			// invoke roll function (pre -1000pts)
			firstRoll();
			if (scoreThisRound == 0)
			{
				player_score[i] = 0;
				std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
			}
			else if (scoreThisRound >= 1000)
			{
				player_score[i] = scoreThisRound;
				std::cout << "Round Score:\t" << scoreThisRound << "\n\n";
				scoreThisRound = 0;

				break;
			}
			else
			{
				scoreThisRound = 0;
			}
		}
	}
	std::cout << "\n [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	std::cout << "  [] [] [] [] [] []  GAME START  [] [] [] [] [] [] \n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	// invoke function to display player turn scores
	displayScores(player_score);
	// begin game functionality
	gameBegins(player_score);
	// function to display game winning results
	gamePoint(player_score);
	std::cout << "\nThe game is over!";
	// invoke function to ask user to play again
	playAgain();
	// main() requires an integer returned
	return 0;
} // *** end of main ***

// function to re-reroll all die, when all die are re-rollable
void reRollAllReRollable()
{
	// just in case, resetting all reRoller values to true
	for (int i = 0; i < NUM_DICE; i++)
	{
		reRollers[i] = true;
	}
	reRollingDice = 6;
	std::cout << "\nRe-rolling your hot dice.\n";
	system("pause");
	// invoke function to re-roll dice
	reRoll(reRollers);
	std::cout << "\n";
	// invoke function to display new dice array
	displayDiceRoll();
	// invoke function to score new dice array
	scoring();
	displayReRollers();
	std::cout << "\n";
	//showPrevReRollArray();
	//std::cout << "\n";
}
// function to display previous re-rollable die array (for comparison)
void showPrevReRollArray()
{
	//std::cout << "\n";
	//std::cout << "\tPrevArra: ";

	for (int i = 0; i < NUM_DICE; i++)
	{
		std::cout << prevArray[i] << " ";
	}
	
}
// function to make a new array of previous arrays elements for comparison
void makePrevReRollerArray()
{
	for (int i = 0; i < NUM_DICE; i++)
	{
		prevArray[i] = reRollers[i];
	}
}
// function that resets the value of re-rollable die to 'true' 
int resetRerollStatus(bool* reRollers)
{
	for (int i = 0; i < NUM_DICE; i++)
	{
		reRollers[i] = false;
	}
	reRollingDice = 0;
	return reRollingDice;
}
// rerolls and displays all non-scoring dice (for testing purposes)
void displayReRollers()
{
	std::cout << "\n";
	std::cout << "\tRe-Rolls: ";
	for (int i = 0; i < NUM_DICE; i++)
	{
		std::cout << reRollers[i] << " ";
	}
}



// function to reroll non-scoring dice from previous roll
int reRoll(bool* reRollers)
{
	makePrevReRollerArray();

	// prints original roll
	std::cout << "\tOld Roll: ";
	for (int i = 0; i < NUM_DICE; i++)
	{
		std::cout << diceRoll[i] << " ";
	}
	// re-rolls all non-scoring die
	for (int i = 0; i < NUM_DICE; i++)
	{
		if (reRollers[i] == true)
		{
			diceRoll[i] = (rand() % 6 + 1);
		}
	}
	displayReRollers();
	// reset all reRoller values to false
	//resetRerollStatus(reRollers);
	// reset the value of dice to be re-rolled to zero
	//reRollingDice = 0;

	return diceRoll, reRollingDice;
}
// function to ask user to ask user to re-roll non-scoring dice
void reRollResponse(int *player_score)
{	
		char rollAgain = 'n';
		std::cout << "\nYou have " << reRollingDice << " non-scoring die.\n";
		std::cout << "Would you like to roll them? (Y or N)\t";
		std::cin >> rollAgain;
		std::cout << "\n\n\n";
		// user choice keeps current score
		if (rollAgain == 'N' || rollAgain == 'n')
		{
			resetRerollStatus(reRollers);
			return;
		}
		// user choice rolls non-scoring dice again
		if (rollAgain == 'Y' || rollAgain == 'y')
		{
			// invoke function to re-roll dice
			reRoll(reRollers);
			std::cout << "\n";
			// invoke function to display new dice array
			displayDiceRoll();
			resetRerollStatus(reRollers);
			// invoke function to score new dice array
			scoring();
			displayReRollers();
			displayScores(player_score);
			//std::cout << "\n";
			// if all die are scoring die, add this score to player score and continue rolling
			if ((reRollingDice == 0) && (scoreThisRound > 0))
			{
				rolloverScore += scoreThisRound;
				//displayScores(player_score);
				reRollAllReRollable();
			}
		}
		// handle incorrect user response
		else
		{
			std::cout << "\nYou have entered an invalid response.";
			// invoke this function again
			reRollResponse(player_score);
		}
	
}
// function to initiate gameplay (with scorekeeping} of players rolls after 1000 pts up to max score
void gameBegins(int* player_score)
{	// for each player
	for (int i = 0; i < numPlayers; i++)
	{
		rolloverScore = 0;
		std::cout << player_names[i];
		// game paused (with non-default comment)
		system("pause>nul|set/p ='s turn to roll...");
		// clear screen of previous output
		system("CLS");

		std::cout << "\n [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
		std::cout << "PLAYER:\t" << player_names[i] << " " << player_names[i] << " " << player_names[i] << " " << player_names[i] << " " << player_names[i] << "\n";
		std::cout << "\n\n\n";
		// invoke function to roll dice
		rollDice();
		// invoke function to display the dice array
		displayDiceRoll();
		std::cout << "\n";
		scoring();
		displayReRollers();
		std::cout << "\n\n\n\n\n";
		std::cout << player_names[i] << " scored " << scoreThisRound << " points.\n";
		std::cout << "[X X] [X X]\t\t+ " << scoreThisRound << "\t\t[X X] [X X]\n";
		std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
		// while values of prevArray are not equal to values of reRollers, execute reRollResponse
		while((reRollingDice != 0) && !(std::equal(std::begin(prevArray), std::end(prevArray), std::begin(reRollers))))
		{
			if (reRollingDice == 6 && scoreThisRound > 0)
			{
				player_score[i] += scoreThisRound;
				std::cout << "\n\n";
				displayScores(player_score);
				reRollAllReRollable();
			}
			reRollResponse(player_score);
		}
		// place value of dice array scoring into this player's score
		player_score[i] += scoreThisRound;
		std::cout << "\n\n";
		std::cout << "Score after re-roll: " << scoreThisRound;
		// invoke function to display new dice array
		displayScores(player_score);
		// if player's score is greater than game point, escape loop
		if (player_score[i] >= MAX_SCORE)
		{
			return;
		}
	}
	gameBegins(player_score);
}
// function for actions after first player scores 10000
void gamePoint(int* player_score)
{
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << "\n**************************************\n\n";
	std::cout << "\n\tTHE GAME IS OVER!\n";
	// invoke function to display final scores
	displayScores(player_score);
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
}
// function to ask player to play again
void playAgain()
{
	char playAgainResponse;
	std::cout << "\nWould you like to play again? (Y or N)\t";
	std::cin >> playAgainResponse;
	// if player does not wish to replay
	if (playAgainResponse == 'N' || playAgainResponse == 'n')
	{
		// exit the application entirely
		exit(0);
	}
	// if player wishes to play again
	if (playAgainResponse == 'Y' || playAgainResponse == 'y')
	{	// reset value of last player's score from scoring()
		scoreThisRound = 0;
		// reset switch for game status to start position
		gameStartStatus = false;
		// loop back to main to start game over
		main();
	}
	// handle invalid user input
	else
	{
		std::cout << "\nYou have entered an invalid response.";
		playAgain();
	}
}
// function to display player scores
void displayScores(int* player_scores)
{
	std::cout << "\n\n\n\n\n";
	std::cout << "PLAYER SCORES\n";
	// display player scores
	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << player_names[i] << ":\t" << player_score[i] << "\n";
	}
	//std::cout << "\n";

}
// function to handle gameplay before reaching 1000 points
int firstRoll()
{	// invoke function to roll dice array
	rollDice();
	std::cout << "\n\n\n";
	std::cout << "\t";
	// invoke function to show new dice array
	displayDiceRoll();
	// invoke function to score new dice array
	scoring();
	// if player rolls less than 1000 points show score
	if (scoreThisRound < 1000)
	{
		std::cout << "\n\n\n\n\n";
		std::cout << "\n[X X] [X X]\t  \t+ " << scoreThisRound << "\t\t[X X] [X X]\n";
		std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n\n";
		system("pause>nul|set/p =Roll dice ...");
		system("CLS");
		std::cout << "\n";
	}
	// if player rolls more than 1000 points
	else
	{
		std::cout << "\n\n\n\n";
		std::cout << "[X X] [X X]\t\t" << scoreThisRound << "\t\t[X X] [X X]\n";
		std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
		std::cout << "You scored over 1000 points!  Let the games begin!\n";
		// change game play status to scorekeeping
		gameStartStatus = true;
	}
	// return score	
	return scoreThisRound;
}
// function to display game rules/introduction
void intro()
{
	std::cout << "\t [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n";
	std::cout << "\t [] [] [] [] [] [] [] 10000 [] [] [] [] [] [] [] [] \n";
	std::cout << "\t [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";

	std::cout << "10000 is a dice game with multiple variations and scoring options.\n\n";

	std::cout << "OBJECT OF THE GAME :\n";
	std::cout << "The object of the game of 10000 is to score a minimum of 10,000 points.\n\n";

	std::cout << "EQUIPMENT :\n";
	std::cout << "To play 10000, you'll need the following items:\n";
	std::cout << "(6) 6-sided dice\n";
	std::cout << "A score sheet and pencil for keeping score.\n\n";

	std::cout << "NUMBER OF PLAYERS:\n";
	std::cout << "10000 can be played by 2 or more players, but is best with 3 - 8 players\n\n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";
	system("pause>nul|set/p =more ...");
	system("CLS");

	std::cout << "\n\nHOW TO PLAY 10000\n";
	std::cout << "The following 10000 rules are the most commonly used, but there are \n";
	std::cout << "numerous variations to choose from(see Variations below).Before the game\n";
	std::cout << "begins, players should establish which rules or variations will be used.  \n";
	std::cout << "Our scoring summary chart makes this process easy and provides for endless \n";
	std::cout << "variety in your 10000 games!\n\n";

	std::cout << "One player is chosen to begin and play moves clockwise around the table.  \n";
	std::cout << "Each player in turn rolls all six dice and checks to see if they have rolled \n";
	std::cout << "any scoring dice or combinations. (See Scoring below.) Any dice that score \n";
	std::cout << "may be set aside and then the player may choose to roll all the remaining \n";
	std::cout << "dice.  The player must set aside at least one scoring die of their choice if \n";
	std::cout << "possible but is not required to set aside all scoring dice.\n\n";

	std::cout << "For example, if a player rolled 1 - 2 - 2 - 5 - 5 - 6 on their turn, they \n";
	std::cout << "could set aside the 1 and the two 5's for scoring, or they could choose to \n";
	std::cout << "set aside only the 1. Any scoring dice that are not set aside may be \n";
	std::cout << "re-rolled along with the non-scoring dice.\n\n";
	system("pause>nul|set/p =more ...");
	system("CLS");

	std::cout << "\n\nIf all six dice have been set aside for scoring(known as having 'hot dice'),\n";
	std::cout << "the player can choose to roll all six dice again and continue adding to their\n";
	std::cout << "accumulated score or they can bank their points, end their turn, and pass the\n";
	std::cout << "dice to the next player.\n\n";

	std::cout << "A player's turn continues until either they decide to stop(at which point\n";
	std::cout << "they then score their accumulated points) or until they fail to roll any scoring\n";
	std::cout << "dice on a throw.\n\n";

	std::cout << "If a player scores no points on a roll, this is known as a Farkle.  The \n";
	std::cout << "player may continue to roll any dice that have not been previously set \n";
	std::cout << "aside for scoring, but all of their points gained so far that turn are lost.\n\n";

	std::cout << "At the end of a player's turn, any points they have scored are written \n";
	std::cout << "down and the dice are passed to the next player.\n\n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";
	system("pause>nul|set/p =more ...");
	system("CLS");

	std::cout << "\n\nSCORING:\n";
	std::cout << "\t1\t\t100 points\n";
	std::cout << "\t5\t\t50 points\n";
	std::cout << "\tThree 1's\t1,000 points\n";
	std::cout << "\tThree 2's\t200 points\n";
	std::cout << "\tThree 3's\t300 points\n";
	std::cout << "\tThree 4's\t400 points\n";
	std::cout << "\tThree 5's\t500 points\n";
	std::cout << "\tThree 6's\t600 points\n";
	std::cout << "\t1 - 2 - 3 - 4 - 5 - 6\t3000 points\n";
	std::cout << "\t1 - 1 - 1 - 1 - 1 - 1\t10000 points and game is won!\n\n";

	std::cout << "*** Note that scoring combinations only count when made with a single \n";
	std::cout << "throw. (Example: If a player rolls a 1 and sets it aside and then rolls \n";
	std::cout << "two 1's on their next throw, they only score 300 points, not 1000.)\n\n";
	system("pause>nul|set/p =more ...");
	system("CLS");

	std::cout << "\n\nSometimes a single roll will provide multiple ways to score.  For example, \n";
	std::cout << "a player rolling 1 - 2 - 4 - 5 - 5 - 5 could score one of the following :\n\n";

	std::cout << "\t100 points for the 1\n";
	std::cout << "\t150 points for the 1 and a 5\n";
	std::cout << "\t500 points for the three 5's\n";
	std::cout << "\t600 points for the 1 and the three 5's\n\n";

	std::cout << "WINNING:\n";
	std::cout << "The first player to score a total of 10,000 or more points wins, provided \n";
	std::cout << "that no other players with a remaining turn can exceed that score.\n\n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";

	std::cout << "OPENING SCORE\n";
	std::cout << "One person, at random, rolls the dice once.  The first person to score 1000\n";
	std::cout << "points or more, starts the game and keeps those points.\n\n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";


	std::cout << "THREE FARKLES\n";
	std::cout << "A player who rolls three Farkles in a row loses 1000 points.\n\n";
	std::cout << " [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] \n\n";
	system("pause>nul|set/p =Press any key to start ...");
	system("CLS");
}
// function to get a count of players in the game
int playerCount()
{
	std::cout << "\n\nHow many players for this game?\n";
	std::cout << "(Enter a number between 2 - 8)\t";
	std::cin >> numPlayers;
	// check to verify there are between 2 - 8 players
	if (numPlayers > 1 && numPlayers < 9)
	{
		return numPlayers;
	}
	// if not between 2 - 8 players, ask again
	playerCount();
	return 0;
}
// function to get user names
std::string get_names()
{
	std::string name;
	// loop through players, have user assign a name for each
	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << "\nWhat is the name of Player " << i + 1 << "?\t";
		std::cin >> player_names[i];
		// clear screen
		system("CLS");
	}
	return *player_names;
}
// function to set initial player scores
void initPlayerScores()
{
	// set each player score to 0
	for (int i = 0; i < numPlayers; i++)
	{
		player_score[i] = 0;
	}
}
// function to roll dice to random number between one and six
int* rollDice()
{
	//resetRerollStatus(reRollers);
	std::cout << "\n";
	// for each of the six die...
	for (int i = 0; i < NUM_DICE; i++)
	{	// pick a number by random
		int randomDiceRoll = 1 + (rand() % 6);
		// this die assigned value of random roll
		diceRoll[i] = randomDiceRoll;
	}
	std::cout << "\n";
	// return value of dice roll array
	return diceRoll;
}
// function to show results of dice roll
void displayDiceRoll()
{
	std::cout << "\tNew Roll: ";
	for (int i = 0; i < NUM_DICE; i++)
	{
		std::cout << diceRoll[i] << " ";
	}
}
// function for scoring combinations based on random dice roll
int scoring()
{
	// reset each variable to zero at roll start
	int oneDie = 0;
	int twoDie = 0;
	int threeDie = 0;
	int fourDie = 0;
	int fiveDie = 0;
	int sixDie = 0;
	int score = 0;
	// reset value of non-scoring dice to zero (redundant)
	reRollingDice = 0;
	// loop through all six die to determine point value of roll
	for (int i = 0; i < NUM_DICE; i++)
	{
		switch (diceRoll[i])
		{
			// if this die is equal to a one...
		case 1:
			// each 'one' is worth 100 points
			score += 100;
			// this 'one' is set to non-rerollable status
			reRollers[i] = false;
			// increment the number of 'one' die
			oneDie++;
			// then break from swich statement
			break;
			// if this die is equal to two...
		case 2:
			twoDie++;
			// add to dice to be rerolled count
			reRollingDice++;
			// this die is set to re-rollable status
			reRollers[i] = true;
			break;
		case 3:
			threeDie++;
			// add to dice to be rerolled count
			reRollingDice++;
			reRollers[i] = true;
			break;
		case 4:
			fourDie++;
			// add to dice to be rerolled count
			reRollingDice++;
			reRollers[i] = true;
			break;
		case 5:
			score += 50;
			reRollers[i] = false;
			fiveDie++;
			break;
		case 6:
			sixDie++;
			// add to dice to be rerolled count
			reRollingDice++;
			reRollers[i] = true;
			break;
		}
	}
	// rolling all ones wins the game
	if (oneDie == 6)
	{
		std::cout << "\n\t***** 10000! *****\n";
		std::cout << "\nYou rolled all ones... 1 1 1 1 1 1\n";

		// six ones is equal to 10000
		score += MAX_SCORE;
		
		// all of which become re-rollable die to surpass score of 10000
		for (int i = 0; i < NUM_DICE; ++i)
		{
			reRollers[i] = true;
			// all of which become re-rollable die to surpass score of 10000
		}
		reRollingDice = 6;
		//return score;
	}
	// scoring for straight (123456)
	if (oneDie == 1 && twoDie == 1 && threeDie == 1 && fourDie == 1 && fiveDie == 1 && sixDie == 1)
	{	// subtract individual accumulated scores (from switch)from ones from score and add the value of a one threesome
		score = (score - 150) + 3000;
		std::cout << "\nYou rolled a straight... 1 2 3 4 5 6\n";
		
		// all die status changed to rerollable
		for (int i = 0; i < NUM_DICE; ++i)
		{
			reRollers[i] = true;
		}
		reRollingDice = 6;
	}
	// if statement for farkle roll, no scoring dice
	if (reRollingDice == 6 && score == 0)
	{
		std::cout << "\n\t\t F A R K L E !\n";
		score = 0;
		for (int i = 0; i < NUM_DICE; i++)
		{
			reRollers[i] = false;
		}
		reRollingDice = 0;
		return score;
	}
	
	// scoring for ones rolled
	if (oneDie == 5)
	{
		score = (score - 500) + 1200;
	} 
	else if (oneDie == 4)
	{
		score = (score - 400) + 1100;
	}
	else if (oneDie == 3)
	{
		score = (score - 300) + 1000;
	}// end of scoring for 1s
	
	



	

	// scoring for twos (for six 2s)
	if (twoDie == 6)
	{
		score += 400;
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 2, set reRoller status to false
			if (diceRoll[i] == 2)
			{
				reRollers[i] = true;
			}
			reRollingDice = 6;
		}
	}
	else if (twoDie == 4 || twoDie == 5)
	{
		score += 200;
		int dieCountOver3Count = 0;
		// if 2 die count is four or five, change re-roll status for only three 2s
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 2, set reRoller status to false
			if (diceRoll[i] == 2 && dieCountOver3Count < 3)
			{
				++dieCountOver3Count;
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// scoring for twos (for three 2s)
	else if (twoDie == 3)
	{
		score += 200;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 2)
			{
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// end of scoring for twos

	



	// scoring for threes (for six 3s)
	if (threeDie == 6)
	{
		score += 600;
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 3, set reRoller status to false
			if (diceRoll[i] == 3)
			{
				reRollers[i] = true;
			}
			reRollingDice = 6;
		}
	}
	else if (threeDie == 4 || threeDie == 5)
	{
		score += 300;
		int dieCountOver3Count = 0;
		// if 3 die count is over three but less than 6, change reroll status for only three 3s
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 3, set reRoller status to false
			if (diceRoll[i] == 3 && dieCountOver3Count < 3)
			{
					dieCountOver3Count++;
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// scoring for threes (for three 2s)
	else if (threeDie == 3)
	{
		score += 300;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 3)
			{
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// end of scoring for threes




	// scoring for fours (for six 4s)
	if (fourDie == 6)
	{
		score += 800;
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 4, set reRoller status to false
			if (diceRoll[i] == 4)
			{
				reRollers[i] = true;
			}
			reRollingDice = 6;
		}
	}
	else if (fourDie == 4 || fourDie == 5)
	{
		score += 400;
		int dieCountOver3Count = 0;
		// if 4 die count is over three but less than 6, change reroll status for only three 4s
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 4, set reRoller status to false
			if (diceRoll[i] == 4 && dieCountOver3Count < 3)
			{
				dieCountOver3Count++;				
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// scoring for fours (for between three and five 4s)
	else if (fourDie == 3)
	{
		score += 400;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 4)
			{
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// end of scoring for fours



	
	// scoring for fives (for between three and five 4s)
	if (fiveDie == 6)
	{
		score = (score - 300) + 1000;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 5)
			{
				reRollers[i] = true;
			}
			reRollingDice = 6;
		}
	}
	else if (fiveDie == 5)
	{
		score = (score - 250) + 600;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 5)
			{
				reRollers[i] = false;
			}
		}
	}
	else if (fiveDie == 4)
	{
		score = (score - 200) + 550;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 5)
			{
				reRollers[i] = false;
			}
		}
	}
	else if (fiveDie == 3)
	{
		score = (score - 150) + 500;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 5)
			{
				reRollers[i] = false;
			}
		}
	}// end of fives scoring


	// scoring for sixes (for six 6s)
	if (sixDie == 6)
	{
		score += 1200;
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 6, set reRoller status to false
			if (diceRoll[i] == 6)
			{
				reRollers[i] = true;
			}
			reRollingDice = 6;
		}
	}
	else if (sixDie == 4 || sixDie == 5)
	{
		score += 600;
		int dieCountOver3Count = 0;
		// if 6 die count is four or five, change reroll status for only three 6s
		for (int i = 0; i < NUM_DICE; i++)
		{
			// if Die is a 6, set reRoller status to false
			if (diceRoll[i] == 6 && dieCountOver3Count < 3)
			{
					dieCountOver3Count++;				
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}	// scoring for sixes (for three 6s)
	else if (sixDie == 3)
	{
		score += 600;
		for (int i = 0; i < NUM_DICE; i++)
		{
			if (diceRoll[i] == 6)
			{
				reRollers[i] = false;
				reRollingDice--;
			}
		}
	}// end of scoring for sixes




	// reset value of global var to zero before...
	scoreThisRound = 0;
	// set value of global var to this player's score
	scoreThisRound = score + rolloverScore;

	return scoreThisRound, reRollingDice;
} // end of scoring()
