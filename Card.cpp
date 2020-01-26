// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Card.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "Card.h"
using namespace std;

/* splitC() - Helper function:
* Algorithm: Take an inputted string and delimiter character, placing each substring separated by the delimiters into an array, and returning the number of substrings
* 1. Take an inputted string and delimiting character, and define str_length integer as the length of the string, arr_length as the length of the array
* 2. Use a for loop from i = 0 up to the string length - 1 (strings start from 0), incrementing by 1.
* 3. In the loop, check if the current input character is equal to the delimiter
* 4. If this is the case, make sure it is not right after the previous delimiter, place the substring up to that point into the array, and increment the substring counter by 1,
* and set the value for the variable defining the position of the previous delimiter as the current index.
* 6. Otherwise, also check if the current index is the last character in the string, and place the substring from the last delimiter to the end in the array if it is,
* and increment the substring counter by 1.
* 7. Test if the amount of substrings has reached the maximum capacity of the inputted array, set the counter to -1 and break out of the for loop if this is the case.
* 8. Return the counter value
* Input parameters: inputted string, delimiter char, string array, and array length integer
* Output (prints to screen): nothing
* Returns: integer of counted substrings
*/

int splitC(string input, char delim, string pieces[], int arr_length){ // Declare splitC()
    int str_length = input.length(); // Initialize the str_length variable as the length of the string
    int counter = 0; // Intitialize the counter variable
    int prev_delim = -1; // Initialize the prev_delim variable as -1.
    int piece_num = 0; // Initialize the piece_num variable
    for(int i = 0; i < str_length; i++){ // For loop from i = 0 to the integer below the total length of the string
        if(input[i] == delim){ // If the input character is equal to the delimiter
            if(i != prev_delim + 1){ // If the current delimiter is NOT right after the last one
                pieces[piece_num] = input.substr(prev_delim + 1, i - prev_delim - 1); // Set the position in pieces[] from one after the last delimiter to one before the current
                piece_num++; // Add one to the counter for the return value
            }
            prev_delim = i; // set the prev_delim variable to the current delimiter
        }
        else if(i == str_length - 1){ // If the current index is the last character in the string
            pieces[piece_num] = input.substr(prev_delim + 1, i - prev_delim); // output from the last delimiter to the end of the string
            piece_num++; // Add one to the counter for the return value
        }
        
        if(piece_num == arr_length && i < str_length - 1){ // If the piece_num is equal to the total length of the array AND it isn't the very last substring
            piece_num = -1; // Set the counter value to -1.
            break; // Exit the for loop
        }
    }
    return piece_num; // Return the counter value
}

Card::Card(){ // Default
    isAccessed = false;
    description = "";
    cardType = 0;
    value = 0;
}

Card::Card(bool isAcc, string desc, int type, int val){ // Parameterized
    isAccessed = isAcc;
    description = desc;
    cardType = type;
    value = val;
}

void Card::setAccessed(bool accessedInput){ //sets whether that card has been accessed since the last “shuffle”
    isAccessed = accessedInput;
}
bool Card::getAccessed(){ //gets whether that card has been accessed since the last “shuffle”
    return isAccessed;
}

void Card::setAllInitVals(int versionInput, int index, string fileName){ //Int inputs are the version number, index in array, and fileName. Sets the string description, card type, and value (from .txt)
    ifstream myFile; // Make the stream object myFile
    myFile.open(fileName); // Open the inputted file name using the stream object
    string pieces[8];
    string line = "";
    int cardNum = -1;
    
    while(getline(myFile, line)){ // While getline is still running
        splitC(line,'/',pieces,8); // Run the splitC function to populate the pieces[] array with the current line
        cardNum = stoi(pieces[0]); // Sets the cardNum to the first piece in the line of the .txt
        if(cardNum == index){
            description = pieces[versionInput + 2];
            cardType = stoi(pieces[1]);
            value = stoi(pieces[2]);
            break; // Break out of the while loop
        }
    }
    myFile.close(); // Close the file stream
}

string Card::getDescription(){ //Get the string description of the card
    return description;
}

int Card::getCardType(){ //Card type getter
    return cardType;
}

int Card::getValue(){ //Gets the value for the card
    return value;
}