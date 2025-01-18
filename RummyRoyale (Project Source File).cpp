
/*         --IMPORTANT NOTE--
THIS CODE WILL NOT RUN ON THE DEFAULT SETTING OF DEV C++ 5.11:

TO MAKE IT RUN SMOTHLY WE APPLIED THESE SPECIFIC SETTINGS:
1. GO TO TOOLS
2. GO TO COMPILER OPTIONS.
3. GO TO SETTINGS TAB.
4. GO TO CODE GENERATION.
5. IN THE (Language standard (-std)). Select ISO C++ 11.
6. Select OK.

--THE COMPILATION MAY SHOW ERRORS/ MAY NOT RUN SMOTHLY ON VS CODE--
*/

#include <iostream>
#include <string>
#include <algorithm> // for swap function
#include <random>	// For random algorithm generator 
#include <cstdlib>  // For system("CLS") to clear the screen
#include <thread>   // For delay
#include <chrono>   // For delay
	
using namespace std;
#define RESET       "\033[0m"
#define BRIGHT_BLACK  "\033[90m"  // Bright Black (Gray)
#define BRIGHT_RED    "\033[91m"  // Bright Red
#define BRIGHT_GREEN  "\033[92m"  // Bright Green
#define BRIGHT_YELLOW "\033[93m"  // Bright Yellow
#define BRIGHT_BLUE   "\033[94m"  // Bright Blue
#define BRIGHT_MAGENTA "\033[95m" // Bright Magenta
#define BRIGHT_CYAN   "\033[96m"  // Bright Cyan
#define BRIGHT_WHITE  "\033[97m"  // Bright White


	
	// Represents a single card
	struct Card {
	    string suit;
	    int rank;
	    string rankName;  // To store the name of the rank for face cards
	    int value;
	
	    // Default constructor (needed for array initialization)
	    Card() : suit("None"), rank(0), rankName("None"), value(0) {}
	
	    // Parameterized constructor
	    Card(string s, int r) : suit(s), rank(r) {
	        if (r == 1) {
	            rankName = BRIGHT_RED "Ace" RESET;
	            value = 1;  // Ace value is 1
	        } else if (r == 11) {
	            rankName = BRIGHT_GREEN "Joker" RESET;
	            value = 0;  // Joker value is 0
	        } else if (r == 12) {
	            rankName =  BRIGHT_BLUE "King" RESET;
	            value = 20;  // King value is 20
	        } else if (r == 13) {
	            rankName = BRIGHT_RED "Queen" RESET;
	            value = 20;  // Queen value is 20
	        } else {
	            rankName = to_string(r);  // Cards 2-10 use their numeric value
	            value = r;  // 2-10 cards have their usual value
	        }
	    }
	};
	
	// Represents the deck of cards
	class Deck {
	private:
	    Card cards[52];
	    int currentSize = 52;
	
	public:
	    Deck() {
	        string suits[] = { BRIGHT_RED "Hearts" RESET, BRIGHT_BLUE "Diamonds" RESET, BRIGHT_YELLOW "Clubs" RESET, BRIGHT_GREEN "Spades" RESET };
	        int cardIndex = 0;
	
	        // Loop through each suit and each rank
	        for (int i = 0; i < 4; ++i) {
	            for (int rank = 1; rank <= 13; ++rank) {
	                cards[cardIndex] = Card(suits[i], rank);
	                cardIndex++;
	            }
	        }
	        shuffle();
	    }
	
	    // Shuffle the deck
	   // Shuffle the deck using a simple random number generator
void shuffle() {
    currentSize = 52; // Reset the deck size
    srand(time(0));   // Seed the random number generator with the current time

    // Fisher-Yates Shuffle Algorithm using rand()
    for (int i = currentSize - 1; i > 0; --i) {
        int j = rand() % (i + 1); // Generate a random index between 0 and i
        swap(cards[i], cards[j]); // Swap the current card with a randomly selected card
    }
}

	
	    // Draw a card
	    Card drawCard() {
	        if (currentSize > 0) {
	            currentSize--;  // Decrease the size of the deck
	            return cards[currentSize];  // Return the last card
	        }
	        cout << BRIGHT_CYAN "No cards left to draw!" RESET;
	        return Card();  // Return a default card if no cards are left
	    }
	
	    int getCurrentSize() const {
	        return currentSize;
	    }
	};
	
	// Represents a player
	class Player {
	public:
	    Card hand[4];  // Static array for player's hand (4 cards max)
	    int handSize = 0;
	    int score = 0;  // Player's current score
	
	public:
	    void drawCard(Deck& deck) {
	        if (handSize < 4) {  // Only draw if there is space in hand
	            hand[handSize] = deck.drawCard();
	            handSize++;
	        }
	    }
	
	    void replaceCard(int index, Deck& deck) {
	        if (index >= 0 && index < handSize) {
	            hand[index] = deck.drawCard();
	        }
	    }
	
	    int calculateHandValue() const {
	        int total = 0;
	        for (int i = 0; i < handSize; ++i) {
	            total += hand[i].value;  // Add the value of each card
	        }
	        return total;
	    }
	
	    void showHand() const {
	        for (int i = 0; i < handSize; ++i) {
	            cout << BRIGHT_RED<< (i + 1)<< ": "<<RESET << BRIGHT_WHITE<<hand[i].rankName << BRIGHT_YELLOW " of "  << hand[i].suit << BRIGHT_GREEN " (Value: " << hand[i].value << ")" RESET<< endl;
	        }
	    }
		
	    void addScore(int points) {
	        score += points;
	    }
	
	    int getScore() const {
	        return score;
	    }
	
	    void clearHand() {
	        handSize = 0;
	    }
	};
	// GAME MANAGER //
	class GameManager {
	private:
	    Deck deck;
	    Player player;
	    Player computer;
	    int targetScore;
	
	    void clearScreen() {
	        // Clear the console screen
	        system("CLS");  // Windows-specific command for clearing screen
	    }
	    

void taunt() {
    // Array of taunts
    string taunts[] = {
        BRIGHT_YELLOW "Ha! You'll never beat me!",
        BRIGHT_YELLOW "Is that all you've got?",
        BRIGHT_YELLOW "You're playing like a beginner!",
        BRIGHT_YELLOW "You really think you can win with that hand?",
        BRIGHT_YELLOW "I hope you have better luck next time!",
        BRIGHT_YELLOW "That was a weak move, even for you!",
        BRIGHT_YELLOW "Not bad... but still not enough!",
        BRIGHT_YELLOW "Keep trying, maybe you'll get lucky eventually!",
        BRIGHT_YELLOW "Haha! This is too easy!",
        BRIGHT_YELLOW "You sure you want to keep playing?"
    };

    // Seed the random number generator with the current time
    srand(time(nullptr));

    // Generate a random index between 0 and 9
    int index = rand() % 10;

    // Output the randomly selected taunt
    cout << taunts[index] << endl;
}

	
	void computerTurn() {
    cout << BRIGHT_RED "\nComputer's turn...\n";

    // Add thinking animation
    for (int i = 0; i < 3; ++i) {
        cout << "Thinking ...%";
        this_thread::sleep_for(chrono::milliseconds(900)); // Wait for 500 milliseconds
        cout << " ";
    }
    cout << "Decided...\n";

    int computerHandValue = computer.calculateHandValue();
    int confidenceThreshold = 35; // Arbitrary threshold for low confidence
    int decision = rand() % 100; // Random decision between 0 and 99

	    // Decide whether to call a showdown
		    if ((computerHandValue <= confidenceThreshold && decision < 50) && computerHandValue <20) { 
		        // 50% chance to call a showdown if hand value is below the threshold
		        cout << BRIGHT_YELLOW "Computer decides to call a showdown!\n" RESET;
		        this_thread::sleep_for(chrono::seconds(2)); // Wait for 500 milliseconds
		        computerShowdown();
		        return; // Skip the card replacement step
		        this_thread::sleep_for(chrono::seconds(2)); // Wait for 500 milliseconds
		    }

    // Otherwise, proceed with normal replacement logic
    cout << BRIGHT_YELLOW"Computer replaced the card with the highest value.\n" RESET;
    this_thread::sleep_for(chrono::seconds(2)); // Wait for 500 milliseconds

    // Find the card with the highest value in the computer's hand
    int highestValueIndex = 0;
    int highestValue = computer.hand[0].value;

    for (int i = 1; i < computer.handSize; ++i) {
        if (computer.hand[i].value > highestValue) {
            highestValue = computer.hand[i].value;
            highestValueIndex = i;
        }
    }

    // Replace the card with the highest value
    computer.replaceCard(highestValueIndex, deck);
    
}
		void computerShowdown() {
	        cout << BRIGHT_RED"\nShowdown!\n";
	        int playerValue = player.calculateHandValue();
	        int computerValue = computer.calculateHandValue();
	
	        cout << BRIGHT_GREEN "Your hand value: " RESET<< playerValue << endl;
	        cout << BRIGHT_RED "Computer's hand value: " RESET << computerValue << endl;
	
	        if (playerValue <= computerValue) {
	            // Wrong showdown (player wins or ties)
	            computer.addScore(30);  // Apply penalty to player score
	            cout << BRIGHT_YELLOW "Wrong showdown! Computer receives a 30-point penalty !.\n\n"RESET;
	            cout << BRIGHT_RED"OOPS! I Did not saw that coming!.. Nice Play.." RESET;
	            
	        } else {
	            // Correct showdown
	            cout << BRIGHT_GREEN"Correct showdown! Your recieved a score.\n\n"RESET;
	            player.addScore(playerValue);  // Add computer's hand value to player's score
	            taunt();
	        }
	        this_thread::sleep_for(chrono::seconds(3)); // Wait for 3 sseconds
	    }

	
	    void playerShowdown() {
	        cout << "\nShowdown!\n";
	        int playerValue = player.calculateHandValue();
	        int computerValue = computer.calculateHandValue();
	
	        cout << BRIGHT_GREEN "Your hand value: " RESET<< playerValue << endl;
	        cout << BRIGHT_RED "Computer's hand value: " RESET << computerValue << endl;
	
	        if (playerValue >= computerValue) {
	            // Wrong showdown (player wins or ties)
	            player.addScore(30);  // Apply penalty to player score
	            cout << BRIGHT_YELLOW  "Wrong showdown! You receive a 30-point penalty !.\n\n"RESET;
	            taunt();
	            
	        } else {
	            // Correct showdown
	            cout << BRIGHT_GREEN"Correct showdown! No Score Added!.\n\n"RESET;
	            computer.addScore(computerValue);  // Add computer's hand value to player's score
	            
	        }
	    }
	
	    void checkGameOver() {
	    	clearScreen();
	        if (player.getScore() >= targetScore) {
    cout << BRIGHT_RED "                     _           _     _ " << endl;
    cout << "                    | |         | |   | |" << endl;
    cout << " _   _  ___  _   _  | | ___  ___| |_  | |" << endl;
    cout << "| | | |/ _ \\| | | | | |/ _ \\/ __| __| | |" << endl;
    cout << "| |_| | (_) | |_| | | | (_) \\__ \\ |_  |_|" << endl;
    cout << " \\__, |\\___/ \\__,_| |_|\___/|___/\\__| (_)" << endl;
    cout << "  __/ |                                  " << endl;
    cout << " |___/                                    " RESET<< endl;



	            exit(0);  // End the game 
	        }
	        if (computer.getScore() >= targetScore) {
	        
    cout << BRIGHT_YELLOW"                                              _ " << endl;
    cout << "                                             | |" << endl;
    cout << " _   _  ___  _   _     __      _____  _ __   | |" << endl;
    cout << "| | | |/ _ \\| | | |    \\ \\ /\\ / / _ \\| '_ \\  | |" << endl;
    cout << "| |_| | (_) | |_| |     \\ V  V / (_) | | | | |_|" << endl;
    cout << " \\__, |\\___/ \\__,_|      \\_/\\_/ \\___/|_| |_| (_)" << endl;
    cout << "  __/ |                                          " << endl;
    cout << " |___/                                           " RESET<< endl;


	            exit(0);  // End the game 
	        }
	    }
	
	    void shuffleAndRedistribute() {
	        deck.shuffle();  // Shuffle the deck
	        player.clearHand();  // Clear both hands
	        computer.clearHand();
	        for (int i = 0; i < 4; ++i) {
	            player.drawCard(deck);  // Redraw cards for both players
	            computer.drawCard(deck);
	        }
	    }
	
	public:
	    GameManager() {
	        // Get the target score from the user
	        cout << BRIGHT_CYAN << "Enter the target score to end the game: ";
	        cin >> targetScore;
	
	        for (int i = 0; i < 4; ++i) {
	            player.drawCard(deck);
	            computer.drawCard(deck);
	        }
	    }
	
	    void playGame() {
	        while (true) {
	            clearScreen();  // Clear the screen after each round
	
	            cout << BRIGHT_GREEN << "\nYour score: " << player.getScore() << BRIGHT_RED <<" | Computer's score: " << computer.getScore() << RESET << endl;
	            cout  << BRIGHT_YELLOW"\n Your Turn (Cards in hand)\n" RESET;
	            
	            player.showHand();
	            cout << BRIGHT_BLUE "\n\n1. Replace a card\n" BRIGHT_BLUE<< "2." <<BRIGHT_BLUE" Showdown"<<BRIGHT_BLUE<<"\n   Choice: " RESET;
	            int choice;
	            cin >> choice;
	
	            if (choice == 1) {
	                cout << BRIGHT_YELLOW"Enter the number of the card to replace (1-4): ";
	                int index;
	                cin >> index;
	                player.replaceCard(index - 1, deck);
	                cout << "Card replaced.\n";
	
	                computerTurn();  // Computer takes its turn after player
	            } else if (choice == 2) {
	                playerShowdown();
	                shuffleAndRedistribute();  // Shuffle deck and redistribute cards after showdown
	                this_thread::sleep_for(chrono::seconds(3));
	             	
					} else {
	                cout << "Invalid choice. Try again.\n";
	            }
	
	            checkGameOver();  // Ensure the game ends correctly after a showdown
	        }
	    }
	};
	
	// Splash screen
	void splashScreen() {

    cout << BRIGHT_YELLOW << " _____                                                                                _____ " << endl;
   
    cout << " _____                                                                       _____ " << endl;
    cout << "( ___ )                                                                     ( ___ )" << endl;
    cout << " |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | " << endl;
    cout << " |   |               _                            _                          |   | " << endl;
    cout << " |   |              | |                          | |                         |   | " << endl;
    cout << " |   | __      _____| | ___ ___  _ __ ___   ___  | |_ ___                    |   | " << endl;
    cout << " |   | \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\           _       |   | " << endl;
    cout << " |   |  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |         | |      |   | " << endl;
    cout << " |   |  _\\_/\\_/ \\___|_|\\___\\___/|_|_|_|_|_|\\___| _\\__\\___/   _  __ _| | ___  |   | " << endl;
    cout << " |   | | '__| | | | '_ ` _ \\| '_ ` _ \\| | | | | '__/ _ \\| | | |/ _` | |/ _ \\ |   | " << endl;
    cout << " |   | | |  | |_| | | | | | | | | | | | |_| | | | | (_) | |_| | (_| | |  __/ |   | " << endl;
    cout << " |   | |_|   \\__,_|_| |_| |_|_| |_| |_|\__,  | |_|  \\___/ \\__, |\\__,_|_|\\___| |   | " << endl;
    cout << " |   |                                  __/ |             __/ |              |   | " << endl;
    cout << " |   |                                 |___/             |___/               |   | " << endl;
    cout << " |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| " << endl;
    cout << "(_____)                                                                     (_____) " << endl;


		cout << BRIGHT_CYAN"\n";
		for (int i = 0; i < 42; ++i) {
	        cout << "==" ;}
	    cout  << BRIGHT_CYAN << "\n\t\t\t\tLoading, please wait...\n";
	    for (int i = 0; i < 42; ++i) {
	        cout << "==" ;
	        if (i==45){
	        	cout << "!";
			}
			
	        this_thread::sleep_for(chrono::milliseconds(40));
	    }
	    cout << RESET;
	    cout << "\n\n";
	}
	
	// Main function
	int main() {
	    splashScreen();
	    GameManager gameManager;
	    gameManager.playGame();
	    return 0;
	}

