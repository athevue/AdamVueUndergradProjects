#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

//this is for RNG
bool setTeller(int x){
        if(x > 100){
            return true;
        }
        else{
            return false;
        }
}
//structure that defines each player
struct Player {
    string name;
    string question;
    bool modality;
    string lie;
    string truth;
    bool chosen; 
};
//begining of gamestart function
void gameStart(vector<Player>& players) {
    //counter that checks total rounds, correct guesses, and total players
    int right_guess = 0;
    int counter = 0;
    int totalPlayers = players.size();
    
    //exposition!
    cout << "Welcome to the Labyrinth of Truths and Lies!" << endl;
    cout << "The only way to find your way out is to ask any of our 7 sentinels questions. Some will tell the truth, but others will lie!!!" << endl;
    cout << "You need to identify the truth or lie 3 times in order to win and make your way out of the labyrinth!" << endl;
    //for loop that counts the amnt of rounds we r on.
    for (int i = 0; i < totalPlayers; i++) {
        cout << "ROUND " << i + 1 << "!" << endl;
        
       cout << "Which sentinel would you like to choose? (1-7): "<<endl;
        //for loop displaying all sentinels
        for (int j = 0; j < totalPlayers; j++) {
            
            cout << j + 1 << "- " << players[j].name << " " << endl;
        }
        
       int playerChoice;
       
        // checking if a player has already been chosen
        do {
            
            cin >> playerChoice;
            playerChoice--;

            if (playerChoice >= 0 && playerChoice < totalPlayers) {
                if (!players[playerChoice].chosen)
                    break; 
                else
                    cout << "You've already chosen that sentinel. Please choose another one." << endl;
            }
            else {
                cout << "That's not a valid answer. Try again." << endl;
            }
        } while (true);

        players[playerChoice].chosen = true; 

        cout << "You have chosen " << players[playerChoice].name << "!" << endl;
        cout << "Here is " << players[playerChoice].name << "'s question: ";
        cout << players[playerChoice].question << endl;
        
        //determining each sentinel's role as a truther or a liar.  
        if(players[playerChoice].modality == true){
            cout << "The sentinal responds: " <<  players[playerChoice].truth << endl;
        }
        else if(players[playerChoice].modality == false) {
            cout << "The sentinal responds: " << players[playerChoice].lie << endl;
        }
        
        
        //checks if sentinal is truthing or lying, along with bad answers.
        char guess;
        cout << "Is the sentinel telling the truth? (y/n): ";
        cin >> guess;

        while (guess != 'y' && guess != 'Y' && guess != 'n' && guess != 'N') {
            cout << "That's not a valid response. try again: ";
            cin >> guess;
        }

        if ((players[playerChoice].modality && (guess == 'y' || guess == 'Y')) ||
            (!players[playerChoice].modality && (guess == 'n' || guess == 'N'))) {
            cout << "Ding Ding Ding!" << endl;
            right_guess++;
        } else {
            cout << "*Loud Incorrect Buzzer*" << endl;
        }
        counter++;

        if (right_guess >= 3) {
            cout << "Congratulations!! You escaped the labyrinth!! You guessed " << right_guess << " questions correct out of " << counter << "." << endl;
            break;
        }
    }
}

int main() {
    srand((unsigned) time(NULL));

    vector<int> mod_def;
    for (int i = 0; i < 7; i++) {
        int random = 50 + (rand() % 101);
        mod_def.push_back(random);
    }

    bool a = setTeller(mod_def[0]);
    bool b = setTeller(mod_def[1]);
    bool c = setTeller(mod_def[2]);
    bool d = setTeller(mod_def[3]);
    bool e = setTeller(mod_def[4]);
    bool f = setTeller(mod_def[5]);
    bool g = setTeller(mod_def[6]);

    vector<Player> players = {
        {"Ofona", "What is Ofona's favorite color?", a, "Red", "Purple", false},
        {"Fadak", "How tall is Fadak?", b, "6 ft 10", "5 ft 3", false},
        {"Evie", "What is Evie's middle name?", c, "Marie", "Rose", false},
        {"Haniah", "How many siblings does Haniah have?", d, "7", "4", false},
        {"Adam", "What is Adam's latest obsession?", e, "Thrifting", "Pickleball", false},
        {"Josh", "What is Josh's current retail position?", f, "Retail Management", "Restaurant Manager", false},
        {"Hayden", "I clutch Fortnite", g, "no.", "yes.", false}
    };

    gameStart(players);




    return 0;
}

