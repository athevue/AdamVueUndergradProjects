#include <iostream>
#include <string>

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
                    int index = (ch - 'a' + ShiftValue+26) % 26; // finding new placement
                    Encoded_Mssg += lowercase_alphabet[index]; // Add the new shifted charecter in
                } else if (isupper(ch)) {
                    int index = (ch - 'A' + ShiftValue+26) % 26; // same for uppercase
                    Encoded_Mssg += uppercase_alphabet[index]; 
                }
            } else {
                Encoded_Mssg += ch; // keep non alphabet
            }
        }
        return Encoded_Mssg;
    }

    string Decode(string Encoded_Mssg, int Value) {
        string Decoded_Mssg = Encode(Encoded_Mssg, -Value);
        return Decoded_Mssg;
    }

public:
    void SetShiftValue(int Value) {
        ShiftValue = Value;
    }

    string Encoded(string Mssg, int Value) {
        return Encode(Mssg, Value);
    }

    string Decoded(string Mssg, int Value) {
        return Decode(Mssg, Value);
    }
};

class Rot13Cipher : public CaesarCipher {
public:
    
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
    cout << "There are 5 messages available to decode \n";
    cout << "Here are the instructions, there are 5 preset words in this game that you are to guess based on a randomly generated shift value." << endl;
    cout << "Your job is to continue guessing the shift value until you think you got it right" << endl;
    cout << "If the message you decode is not a coherent word, enter N. If it is enter Y" << endl;

    int choice;
    string correctOrNo;
    int points;

    string words[5] = {"hello", "names", "Bond", "James", "Canada"}; // putting in the predetermined words
    string messages[5] = {cipher.Encoded(words[0], 3), cipher.Encoded(words[1], 3), cipher.Encoded(words[2], 3), cipher.Encoded(words[3], 3),cipher.Encoded(words[4], 3)};
    //string of messages with the set cipher value
    
    string eORd;
    cout << "Would you like to be encryptor or decryptor? ";
    cin >> eORd;
    if(eORd == "E"){
        //displayMENUE();
        int mc;
        string m;
        int v;
        cout << "Which message do you wanna encrpt? (1, 2, 3, 4, 5)? ";
        cin >> mc;
        cout << "What message are you encrypting? " << endl;
        cin >> m;
        cout << "What value would you like to encrypt it with? ";
        cin >> v;
        words[mc] = m;
        cout << cipher.Encoded(words[mc], v) << endl;;
        
    }
    else if(eORd == "D"){
        displayMENU();
        cin >> choice;
    }

    

    while (choice != 6) {    //while not exiting
        string decoded_message;
        int index = choice - 1; // Adjust choice to index
        encoded_mssg = messages[index];  // picks out the message the user chose
        cout << "Encoded message: " << encoded_mssg << endl;  //prints out message
        cout << "Enter your guess for the shift value (1-13) to decode the message: "; //enter shift value
        cin >> value;                                                             //takes value
        decoded_message = cipher.Decoded(encoded_mssg, value);     //decodes
        cout << "This is the decoded message: " <<  decoded_message << endl;  //displays decoding
        cout << "Is this correct? (Y/N): ";                    //user determines if it is correct (an actual word means they guessed the right value)
        
        while (true) {
            cin >> correctOrNo;  //takes in yes or no
            if (correctOrNo == "Y") {             //if yes
                cout << "Congratulations you won!" << endl;
                points = points + 1;
                cout << "Points: " << points << endl;
                break; // Break the inner loop
            } else if (correctOrNo == "N") {            //if no repeats guessing
                cout << "Sorry, try again" << endl;
                cout << "Enter your guess for the shift value (1-13) to decode the message: ";
                cin >> value;
                decoded_message = cipher.Decoded(encoded_mssg, value);
                cout << "This is the decoded message: " <<  decoded_message << endl;
                cout << "Is this correct? (Y/N): ";
            } else {
                cout << "Invalid input. Please enter 'Y' or 'N': ";
            }
        }

        displayMENU();       //starts over once you get a point
        cin >> choice;
    }

    return 0;
}
