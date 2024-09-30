#include <iostream>
#include <string>
#include <limits>

using namespace std;

class CaesarCipher {
private:
    int ShiftValue;
    
    string uppercase_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowercase_alphabet = "abcdefghijklmnopqrstuvwxyz";

protected:
    string Encode(string Mssg, int ShiftValue) {
        string Encoded_Mssg = "";
        for (char ch : Mssg) {
            if (isalpha(ch)) {
                if (islower(ch)) {
                    int index = (ch - 'a' + ShiftValue + 26) % 26; // finding new placement
                    Encoded_Mssg += lowercase_alphabet[index]; // add the new shifted character in
                } else if (isupper(ch)) {
                    int index = (ch - 'A' + ShiftValue + 26) % 26; // same for uppercase
                    Encoded_Mssg += uppercase_alphabet[index]; 
                }
            } else {
                Encoded_Mssg += ch; // keep non-alphabet characters
            }
        }
        return Encoded_Mssg;
    }

    string Decode(string Encoded_Mssg, int Value) {
        return Encode(Encoded_Mssg, -Value);
    }

public:

    string Encoded(string Mssg, int Value) {
        return Encode(Mssg, Value);
    }

    string Decoded(string Mssg, int Value) {
        return Decode(Mssg, Value);
    }
};


void displayMENU() {
    cout << "MENU \n";
    cout << "1: Decode Message 1 \n";
    cout << "2: Decode Message 2 \n";
    cout << "3: Decode Message 3 \n";
    cout << "4: Decode Message 4 \n";
    cout << "5: Decode Message 5 \n";
    cout << "6: Leave the Program \n";
    cout << "Selection: ";
}

int main() {
    string encoded_mssg;
    int value;
    CaesarCipher cipher;

    cout << "Welcome to the Cipher Program! \n \n";
    cout << "Here are the instructions!" << endl;
    cout << "There are two roles: decryptor and encryptor." << endl;
    cout << "There are 5 preset words in this game that you are to guess based on a randomly generated shift value." << endl;
    cout << "\nAs a decryptor, your job is to continue guessing the shift value until you think you got it right." << endl;
    cout << "If the message you decode is not a coherent word, enter N. If it is enter Y." << endl;
    cout << "\nAs an encryptor, you get the chance to see the Caesar's Cipher method in action." << endl;
    cout << "You will write a message and enter how many shift values." << endl; // game instructions

    int choice;
    string correctOrNo;
    int points = 0;

    string words[5] = {"hello", "world", "superfragile", "dinosaur", "rawrrr"}; // putting in the predetermined words
            /* ANSWERS FOR DECRYPTION */
    string messages[5] = {cipher.Encoded(words[0], 13), cipher.Encoded(words[1], 2), cipher.Encoded(words[2], 1), cipher.Encoded(words[3], 9),cipher.Encoded(words[4], 5)};
        //string of messages with the set cipher value      
        
    bool solved[5] = {false, false, false, false, false}; // tracking solved messages
    
    string eORd;
    while (true) {
        cout << "Would you like to be encryptor or decryptor? (E/D): ";
        cin >> eORd;

        if (eORd == "E" || eORd == "D") {
            break; // valid input, exit the loop
        } else {
            cout << "Invalid selection. Please enter 'E' for encryptor or 'D' for decryptor.\n";
        }
    }

    // Encryptor Mode
    if(eORd == "E"){
        int mc, v;
        string m;

        cout << "Enter (1-5): ";
        cin >> mc;
        cin.ignore();
        
        cout << "Enter the message to encrypt: ";
        getline(cin, m); // allows spaces and special characters
        cout << "Enter the shift value to encrypt with (1-13): ";
        
        while (true) {
            cin >> v;

            // check if the input was valid
            if (cin.fail() || v < 1 || v > 13) {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid shift value. Please enter a value between 1 and 13.\n";
                cout << "Enter the shift value to encrypt with (1-13): "; // prompt again
            } else {
                break; // valid input, exit the loop
            }
        }
        
        cout << "Encrypted message: " << cipher.Encoded(m, v) << endl;
        cout << "You have encrypted the message of " << m 
             << " with " << v << " shift values and it resulted to: "
             << cipher.Encoded(m, v) << ".\nThis is an example of Caesar's Cipher method."
             << "\nEnding program. Play again to try to decrypt preset messages!"<< endl;
        return 0;
    }
    
    // Decryptor Mode
    while (true) {
        displayMENU();
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid selection. Please try again.\n";
            continue;
        }

        int index = choice - 1; // adjust choice to index

        if (solved[index]) {
            cout << "You have already solved this message! Please choose a different one.\n";
            continue;
        }

        encoded_mssg = messages[index];
        cout << "Encoded message: " << encoded_mssg << endl;

        while (true) {
            cout << "Enter your guess for the shift value (1-13): ";
            
            cin >> value;

            // check if the input was valid
            if (cin.fail() || value < 1 || value > 13) {
                cin.clear(); // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number between 1 and 13.\n";
                continue;
            }

            string decoded_message = cipher.Decoded(encoded_mssg, value);
            cout << "Decoded message: " << decoded_message << endl;

            // always ask the user if they think the message is correct
            cout << "Is this correct? (Y/N): ";
            cin >> correctOrNo;

            // if the decoded message matches the original word
            if (decoded_message == words[index] && correctOrNo == "Y") {
                cout << "Congratulations, you guessed it right!\n";
                points++;
                cout << "Points: " << points << endl;
                solved[index] = true; // mark this message as solved

                // check if all messages have been solved
                if (points == 5) { // if all 5 messages are solved
                    cout << "Congratulations! You've solved all the messages!\n";
                    return 0; // exit the program
                }
                break;
            } 
            // if they say "Y" but the decoded message doesn't match the original
            else if (correctOrNo == "Y") {
                cout << "Sorry, that's not the correct answer. The decoded message doesn't match the original.\n";
            }
            // if they say "N", let them try again
            else {
                cout << "Let's try again!\n";
            }
        }
    }

    return 0;
}
