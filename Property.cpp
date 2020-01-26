// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Property.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "Property.h"
using namespace std;

/* splitP() - Helper function:
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

int splitP(string input, char delim, string pieces[], int arr_length){ // Declare splitP()
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

Property::Property(){ // Default
 //Initialize all variables
    propName = "";
    isOwnable = false;
    rent_init = 0;
    rent1 = 0;
    rent2 = 0;
    rent3 = 0;
    rent4 = 0;
    rent_hotel = 0;
    mortValue = 0;
    houseCost = 0;
    propCost = 0;
    color = "";
    currentRent = 0;
    ifMort = false;
    currentOwner = -1;
    numHouses = 0;
    numHotels = 0;
    ifMonopolized = false;
}

Property::Property(string pName, bool isOwn, int ri, int r1, int r2, int r3, int r4, int rh, int mVal, int hCost, int pCost, string col, int cRent, bool ifM, int currOwn, int nHouse, int nHotel, bool ifMon){ // Parameterized
    propName = pName;
    isOwnable = isOwn;
    rent_init = ri;
    rent1 = r1;
    rent2 = r2;
    rent3 = r3;
    rent4 = r4;
    rent_hotel = rh;
    mortValue = mVal;
    houseCost = hCost;
    propCost = pCost;
    color = col;
    currentRent = cRent;
    ifMort = ifM;
    currentOwner = currOwn;
    numHouses = nHouse;
    numHotels = nHotel;
    ifMonopolized = ifMon;
}

void Property::setAllInitVals(int versionInput, int index){ //Sets the value of the property number, property name, isOwnable, all rent values, mortgage value, house cost, and property costs given the version number (from .txt)
    ifstream propTitle; // Make the stream object propTitle
    ifstream propDetail; // Make the stream object propDetail
    propTitle.open("propNames.txt"); // Open the "propNames.txt" file using the stream object
    propDetail.open("propDetails.txt"); // Open the "propDetails.txt" file using the stream object
    string pieces[12];
    string line = "";
    int currentPropNum = -1;
    
    while(getline(propTitle, line)){ // While getline is still running (for propTitle)
        splitP(line,'/',pieces,12); // Run the splitP function to populate the pieces[] array with the current line
        currentPropNum = stoi(pieces[0]); // Sets the currentPropNum to the first character in the line of the .txt
        if(currentPropNum == index){
            propName = pieces[versionInput];
            break; // Break out of the while loop
        }
    }
    propTitle.close(); //Close the file stream
    
    while(getline(propDetail, line)){ // While getline is still running (for propDetail)
        splitP(line,'/',pieces,12); // Run the splitP function to populate the pieces[] array with the current line
        currentPropNum = stoi(pieces[0]); // Sets the currentPropNum to the first character in the line of the .txt
        if(currentPropNum == index){
            if(pieces[1] == "0"){ // Set isOwnable to false or true
                isOwnable = false;
            }
            else{
                isOwnable = true;
            }
            
            rent_init = stoi(pieces[2]);
            rent1 = stoi(pieces[3]);
            rent2 = stoi(pieces[4]);
            rent3 = stoi(pieces[5]);
            rent4 = stoi(pieces[6]);
            rent_hotel = stoi(pieces[7]);
            mortValue = stoi(pieces[8]);
            houseCost = stoi(pieces[9]);
            propCost = stoi(pieces[10]);
            color = pieces[11];
            break; // Break out of the while loop
        }
    }
    propDetail.close(); //Close the file stream
    
}

string Property::getName(){ //Gets the name of the property
    return propName;
}

bool Property::getIsOwnable(){ //Gets whether the property is ownable or not
    return isOwnable;
}

int Property::getRentInit(){ //gets the initial rent
    return rent_init;
}

int Property::getRent1(){ //gets the rent with one house
    return rent1;
}

int Property::getRent2(){ //gets the rent with two houses
    return rent2;
}

int Property::getRent3(){ //gets the rent with three houses
    return rent3;
}

int Property::getRent4(){ //gets the rent with four houses
    return rent4;
}

int Property::getRentHotel(){ //gets the rent with a hotel
    return rent_hotel;
}

void Property::setCurrentRent(int rentInput){ //Sets the current rent of the property
    currentRent = rentInput;
}

int Property::getCurrentRent(){ //Gets the current rent of the property
    return currentRent;
}

int Property::getHouseCost(){ //Gets the cost of one house for the user
    return houseCost;
}

int Property::getMortgageValue(){ //Gets the mortgage value of the property
    return mortValue;
}

int Property::getPropCost(){ //Gets the property cost
    return propCost;
}

string Property::getColor(){ //Gets the color
    return color;
}

void Property::setIfMortgaged(bool isMortgagedInput){ //Sets whether the property is mortgaged
    ifMort = isMortgagedInput;
}

bool Property::getIfMortgaged(){ //Gets whether the property is mortgaged
    return ifMort;
}

void Property::setOwner(int ownerInput){ //Sets the current owner of the property
    currentOwner = ownerInput;
}

int Property::getOwner(){ //Gets the name of the current owner of the property
    return currentOwner;
}

void Property::setNumHouses(int housesInput){ //number of houses setter
    numHouses = housesInput;
}

int Property::getNumHouses(){ //number of houses getter
    return numHouses;
}

void Property::setNumHotels(int hotelsInput){ //number of hotels setter
    numHotels = hotelsInput;
}

int Property::getNumHotels(){ //number of hotels getter
    return numHotels;
}

void Property::setIfMonopolized(int monopInput){ // Sets if the property is part of a monopoly
    ifMonopolized = monopInput;
}
bool Property::getIfMonopolized(){ // Gets if the property is part of a monopoly
    return ifMonopolized;
}