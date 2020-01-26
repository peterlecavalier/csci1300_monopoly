// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Board.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "Board.h"
#include "User.h"
#include "Property.h"
#include "Card.h"
using namespace std;

/* split() - Helper function:
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

int split(string input, char delim, string pieces[], int arr_length){ // Declare split()
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

string printSpace(string spaceInput, int fullSize, bool leftRight){
    int length = spaceInput.length();
    int spaceNum = (fullSize - length) / 2;
    string strSpace = "";

    if(((fullSize - length) % 2) != 0 && leftRight == true){
        spaceNum++;
    }

    for(int i = 0; i < spaceNum; i++){
        strSpace+= " ";
    }
    return strSpace;
}

/* turnLower() - Helper function:
* Algorithm: Take an inputted string and turn every uppercase letter into its lowercase equivalent
* 1. Take an inputted string and delimiting character, and define length integer as the length of the string
* 2. Use a for loop from i = 0 up to the string length
* 3. In the loop, use the ASCII values of each character to check if it's uppercase. If it is, turn the character into its lowercase equivalent
* 4. Return the final string.
* Input parameters: inputted string
* Output (prints to screen): nothing
* Returns: lowercase string
*/

string turnLower(string input){ // Declare turnLower()
    int length = input.length();
    for(int i = 0; i < length; i++){ // This for loop turns every letter in the input string into it's corresponding lowercase letter.
        if(input[i] >= 65 && input[i] <= 90){
            input[i] = input[i] + 32;
        }
    }
    return input;
}

Board::Board(){ // Default
    versionInt = 0; //Initialize all variables
    versionName = "";
    numUsers = 0;
    houseName = "";
    hotelName = "";
    housePName = "";
    hotelPName = "";
    moneyName = "";
    chanceName = "";
    commName = "";
    railName = "";
    moneySign = "";
    middleVal = 100;
    turnNumber = 1;
}

Board::Board(int verInt, string verName, int numUs, string houseN, string hotelN, string housePN, string hotelPN, string moneyN, string chanceN, string commN, string railN, string monSign, int middle, int turnN){ // Parameterized
    versionInt = verInt;
    versionName = verName;
    numUsers = numUs;
    houseName = houseN;
    hotelName = hotelN;
    housePName = housePN;
    hotelPName = hotelPN;
    moneyName = moneyN;
    chanceName = chanceN;
    commName = commN;
    railName = railN;
    moneySign = monSign;
    middleVal = middle;
    turnNumber = turnN;
}

void Board::setAllInitVals(int versionInput, string user0, string user1, string user2, string user3, vector <int> turnOrderInput){ //sets the version number, version name, house name, hotel name, money name, chance name, and community chest name (from .txt)
    ifstream myFile; // Make the stream object myFile
    myFile.open("versionDetails.txt"); // Open the inputted file name using the stream object
    string pieces[11];
    string line = "";
    int verNum = -1;

    users[0].setUsername(user0); //There will always be at least 1 real user and 1 cpu.
    users[0].setIsReal(true);
    users[1].setUsername(user1);
    numUsers = 2;

    if(user2 != ""){
        users[2].setUsername(user2);
        numUsers = 3;
    }
    if(user3 != ""){
        users[3].setUsername(user3);
        numUsers = 4;
    }

    turnOrder = turnOrderInput;

    while(getline(myFile, line)){ // While getline is still running
        split(line,'/',pieces,11); // Run the split function to populate the pieces[] array with the current line
        verNum = stoi(pieces[0]); // Sets the current verNum to the first character in the line of the .txt
        if(verNum == versionInput){
            versionName = pieces[1];
            houseName = pieces[2];
            hotelName = pieces[3];
            housePName = pieces[4];
            hotelPName = pieces[5];
            moneyName = pieces[6];
            chanceName = pieces[7];
            commName = pieces[8];
            railName = pieces[9];
            moneySign = pieces[10];
            break; // Break out of the while loop
        }
    }
    myFile.close(); // Close the file stream
    versionInt = versionInput;


    for(int i = 0; i < 40; i++){
        props[i].setAllInitVals(versionInt, i);
    }

    for(int i = 0; i < 16; i++){
        chance[i].setAllInitVals(versionInt, i, "chance.txt");
        community[i].setAllInitVals(versionInt, i, "comChest.txt");
    }
}

int Board::getVersion(){ //gets the version of the game played as an int
    return versionInt;
}

string Board::getVersionName(){ //gets the NAME of the version as a string
    return versionName;
}

void Board::setNumUsers(int usersInput){ //Sets the number of users in the game
    numUsers = usersInput;
}

int Board::getNumUsers(){ //gets the number of users in the game
    return numUsers;
}

string Board::getHouseName(){ //gets the name of a house for the version
    return houseName;
}

string Board::getHotelName(){ //gets the name of a hotel for the version
    return hotelName;
}

string Board::getHousePName(){ //gets the name of plural houses for the version
    return housePName;
}

string Board::getHotelPName(){ //gets the name of plural hotels for the version
    return hotelPName;
}

string Board::getMoneyName(){ //gets the name of money for the version
    return moneyName;
}

string Board::getChanceName(){ //gets the name of a chance card for the version
    return chanceName;
}

string Board::getCommName(){ //gets the name of a community chest card for the version
    return commName;
}

string Board::getRailName(){ //gets the name of a railroad for the version
    return railName;
}

void Board::setMiddle(int midVal){ //sets the amount of money in the middle
    middleVal = midVal;
}

int Board::getMiddle(){ //gets the amount of money in the middle
    return middleVal;
}

void Board::shuffleCards(bool chanceComm){ //Shuffles the cards by simply setting the access to false for all. Tests if the get out of jail free card has been accessed and keeps it that way.
    if(chanceComm == false){ // If shuffling the chance cards
        for(int i = 0; i < 16; i++){
            if(chance[i].getCardType() != 5){ // If it is NOT a get out of jail free card
                chance[i].setAccessed(false);
            }
        }
    }
    else{ // If shuffling the community chest cardss
        for(int i = 0; i < 16; i++){
            if(community[i].getCardType() != 5){ // If it is NOT a get out of jail free card
                community[i].setAccessed(false);
            }
        }
    }
}

vector <int> Board::printAllProps(int userInput, int returnType){ //Prints all the properties that inputted user owns with respective house/hotel values. returnType determines whether it is returning mortgaged properties, unmortgaged properties, or nothing.
    int numBrown = 0;
    int numLightBlue = 0;
    int numPink = 0;
    int numOrange = 0;
    int numRed = 0;
    int numYellow = 0;
    int numGreen = 0;
    int numDarkBlue = 0;
    int numUtilities = users[userInput].getNumUtil();
    int numRailroads = users[userInput].getNumRail();
    int numTotal = 0;
    string currColor = "";
    bool ownAnything = false;
    vector <int> currentUserProps;

    for(int i = 0; i < 40; i++){ // This loop counts how many of each color the user has.
        if(props[i].getOwner() == userInput){
            ownAnything = true;
            currColor = props[i].getColor();
            if(currColor == "Brown"){
                numBrown++;
            }
            else if(currColor == "Light Blue"){
                numLightBlue++;
            }
            else if(currColor == "Pink"){
                numPink++;
            }
            else if(currColor == "Orange"){
                numOrange++;
            }
            else if(currColor == "Red"){
                numRed++;
            }
            else if(currColor == "Yellow"){
                numYellow++;
            }
            else if(currColor == "Green"){
                numGreen++;
            }
            else if(currColor == "Dark Blue"){
                numDarkBlue++;
            }
        }
    }

    numTotal = numBrown + numLightBlue + numPink + numOrange + numRed + numYellow + numGreen + numDarkBlue + numUtilities + numRailroads;

    if(ownAnything == false && numUtilities == 0 && numRailroads == 0){
        cout << users[userInput].getUsername() << " does not own any property!" << endl;
        return currentUserProps;
    }
    else{
        if(numTotal == 1){
            cout << users[userInput].getUsername() << " owns 1 property:" << endl;
        }
        else{
            cout << users[userInput].getUsername() << " owns " << numTotal << " properties:" << endl;
        }
    }

    for(int i = 0; i < 40; i++){
        if(i == 0 && numBrown != 0){
            cout << endl << "Brown:" << endl;
        }
        else if(i == 5 && numLightBlue != 0){
            cout << endl << "Light Blue:" << endl;
        }
        else if(i == 10 && numPink != 0){
            cout << endl << "Pink:" << endl;
        }
        else if(i == 15 && numOrange != 0){
            cout << endl << "Orange:" << endl;
        }
        else if(i == 20 && numRed != 0){
            cout << endl << "Red:" << endl;
        }
        else if(i == 25 && numYellow != 0){
            cout << endl << "Yellow:" << endl;
        }
        else if(i == 30 && numGreen != 0){
            cout << endl << "Green:" << endl;
        }
        else if(i == 35 && numDarkBlue != 0){
            cout << endl << "Dark Blue:" << endl;
        }

        if(props[i].getOwner() == userInput && props[i].getColor() != "Railroad" && props[i].getColor() != "Utility"){
            if(props[i].getNumHotels() == 1){
                cout << i << " - " << props[i].getName() << " - 1 " << hotelName << ". - " << "Current Rent: " << props[i].getCurrentRent();
            }
            else if(props[i].getNumHouses() == 1){
                cout << i << " - " << props[i].getName() << " - 1 " << houseName << ". - " << "Current Rent: " << props[i].getCurrentRent();
            }
            else if(props[i].getNumHouses() > 1){
                cout << i << " - " << props[i].getName() << " - " << props[i].getNumHouses() << housePName << ". - " << "Current Rent: " << props[i].getCurrentRent();
            }
            else{
                cout << i << " - " << props[i].getName() << " - Current Rent: " << props[i].getCurrentRent();
            }

            if(props[i].getIfMortgaged() == true){ //If the property is mortgaged
                cout << " MORTGAGED" << endl;
                if(returnType == 0){ //If returning mortgaged properties
                    currentUserProps.push_back(i); //Add the current property to the vector
                }
            }
            else{ //If it isn't mortgaged
                cout << endl;
                if(returnType == 1){ //If returning unmortgaged
                    currentUserProps.push_back(i); //Add the current property to the vector
                }
            }
        }
    }

    if(numUtilities != 0){
        if(numUtilities == 1){
            cout << endl << "Utility:" << endl;
            if(props[12].getOwner() == userInput){
                cout << "12 - " << props[12].getName() << " - Current Rent: 4 times amount shown on dice.";
                if(props[12].getIfMortgaged() == true){ //If the property is mortgaged
                    cout << " MORTGAGED" << endl;
                    if(returnType == 0){ //If returning mortgaged properties
                        currentUserProps.push_back(12); //Add the current property to the vector
                    }
                }
                else{ //If it isn't mortgaged
                    cout << endl;
                    if(returnType == 1){ //If returning unmortgaged
                        currentUserProps.push_back(12); //Add the current property to the vector
                    }
                }
            }
            else{
                cout << "28 - " << props[28].getName() << " - Current Rent: 4 times amount shown on dice.";
                if(props[28].getIfMortgaged() == true){ //If the property is mortgaged
                    cout << " MORTGAGED" << endl;
                    if(returnType == 0){ //If returning mortgaged properties
                        currentUserProps.push_back(28); //Add the current property to the vector
                    }
                }
                else{ //If it isn't mortgaged
                    cout << endl;
                    if(returnType == 1){ //If returning unmortgaged
                        currentUserProps.push_back(28); //Add the current property to the vector
                    }
                }
            }
        }
        else{
            cout << endl << "Utilities:" << endl;
            cout << "12 - " << props[12].getName() << " - Current Rent: 10 times amount shown on dice." << endl;
            cout << "28 - " << props[28].getName() << " - Current Rent: 10 times amount shown on dice." << endl;
            if(props[12].getIfMortgaged() == true){ //If the property is mortgaged
                cout << " MORTGAGED" << endl;
                if(returnType == 0){ //If returning mortgaged properties
                    currentUserProps.push_back(12); //Add the current property to the vector
                }
            }
            else{ //If it isn't mortgaged
                cout << endl;
                if(returnType == 1){ //If returning unmortgaged
                    currentUserProps.push_back(12); //Add the current property to the vector
                }
            }
            if(props[28].getIfMortgaged() == true){ //If the property is mortgaged
                cout << " MORTGAGED" << endl;
                if(returnType == 0){ //If returning mortgaged properties
                    currentUserProps.push_back(28); //Add the current property to the vector
                }
            }
            else{ //If it isn't mortgaged
                cout << endl;
                if(returnType == 1){ //If returning unmortgaged
                    currentUserProps.push_back(28); //Add the current property to the vector
                }
            }
        }
    }

    if(numRailroads != 0){
        if(numRailroads == 1){
            cout << endl << railName << ":" << endl;
        }
        else{
            cout << endl << railName << "s:" << endl;
        }

        for(int i = 5; i < 36; i = i + 10){
            if(props[i].getOwner() == userInput){
                cout << i << " - " << props[i].getName() << " - Current Rent: " << props[i].getCurrentRent();

                if(props[i].getIfMortgaged() == true){ //If the property is mortgaged
                    cout << " MORTGAGED" << endl;
                    if(returnType == 0){ //If returning mortgaged properties
                        currentUserProps.push_back(i); //Add the current property to the vector
                    }
                }
                else{ //If it isn't mortgaged
                    cout << endl;
                    if(returnType == 1){ //If returning unmortgaged
                        currentUserProps.push_back(i); //Add the current property to the vector
                    }
                }
            }
        }
    }

    return currentUserProps; //Return the vector of currentUserProps
}

void Board::saveGame(){ //Saves the game by writing all modified data to a .txt file.
    string boardString = "";
    string propString = "";
    string userString = "";
    string cardString = "";
    string turnOrderString = "";

    ofstream saveOutput;
    saveOutput.open("saveFile.txt");

    //Save the details of the board & game
    for(int i = 0; i < turnOrder.size(); i++){ //Loop thru turn order and populate the string with its values.
        turnOrderString += to_string(turnOrder[i]);
    }

    saveOutput << "Board/" << time(0) << "/" << versionInt << "/" << versionName << "/" << turnNumber << "/" << turnOrderString << "/" << numUsers << "/" << middleVal << endl;
    for(int i = 0; i < 40; i++){ //Saves the details of each property
        saveOutput << "Prop/" << i << "/" << props[i].getCurrentRent() << "/" << props[i].getIfMortgaged() << "/" << props[i].getOwner() << "/" << props[i].getNumHouses() << "/" << props[i].getNumHotels() << "/" << props[i].getIfMonopolized() << endl;
    }

    for(int i = 0; i < 16; i++){ //Saves the details of the chance cards
        saveOutput << "Chance/" << i << "/" << chance[i].getAccessed() << endl;
    }

    for(int i = 0; i < 16; i++){ //Saves the details of the community chest cards
        saveOutput << "Comm/" << i << "/" << community[i].getAccessed() << endl;
    }

    for(int i = 0; i < numUsers; i++){ //Saves the details of the users
        saveOutput << "User/" << i << "/" << users[i].getUsername() << "/" << users[i].getMoney() << "/" << users[i].getGetOutOfJail() << "/" << users[i].getSpace() << "/" << users[i].getNumUtil() << "/" << users[i].getNumRail() << "/" << users[i].getIsReal() << "/" << users[i].getNumDoubles() << "/" << users[i].getInJail() << endl;
    }
    saveOutput.close(); //Close the .txt
}

bool Board::loadGame(){ //Loads the game by reading from the .txt file
    ifstream loadInput; // Make the stream object loadInput
    loadInput.open("saveFile.txt"); // Open the saveFile using the ifstream object
    int numStudents = 0;
    string turnOrderString = "";
    string turnOrderChar = "";
    vector <int> nullVect;
    if(loadInput.is_open()){ // If the file was successfully opened
        string firstLine = ""; // Initialize the line variable
        string pieces[11];
        getline(loadInput, firstLine);
        split(firstLine, '/', pieces, 11);

        cout << "There is a save file from ";
        int timeDif = time(0) - stoi(pieces[1]);
        int yearsCount = (timeDif / 31536000);
        timeDif = (timeDif % 31536000);
        int daysCount = (timeDif / 86400);
        int monthsCount = (daysCount / 30);
        timeDif = (timeDif % 86400);
        int hoursCount = (timeDif / 3600);
        timeDif = (timeDif % 3600);
        int minCount = (timeDif / 60);
        if(yearsCount != 0){
            cout << "about " << yearsCount << " years and " << monthsCount << " months ago ";
        }
        else if(monthsCount != 0){
            cout << "about " << monthsCount << " months ago ";
        }
        else if(daysCount != 0){
            cout << daysCount << " days and " << hoursCount << " hours ago ";
        }
        else if(hoursCount != 0){
            cout << hoursCount << " hours and " << minCount << " minutes ago ";
        }
        else{
            cout << minCount << " minutes ago ";
        }

        cout << "(" << pieces[3] << " Monopoly, Turn " << pieces[4] << ")." << endl;
        cout << "Would you like to load this file? (y/n)" << endl;
        string choiceInput = "";
        bool choiceBool = false;
        bool goodInput = false;
        while(goodInput == false){
            cin >> choiceInput;
            if(choiceInput == "y" || choiceInput == "Y" || choiceInput == "n" || choiceInput == "N"){
                goodInput = true;
                if(choiceInput == "y" || choiceInput == "Y"){
                    choiceBool = true;
                }
                else{
                    choiceBool = false;
                }
            }
            else{
                cout << "Please enter y or n." << endl;
            }
        }

        if(choiceBool == true){
            versionInt = stoi(pieces[2]);
            setAllInitVals(versionInt, "null", "null", "", "", nullVect);
            versionName = pieces[3];
            turnNumber = stoi(pieces[4]);
            turnOrderString = pieces[5];
            numUsers = stoi(pieces[6]);
            middleVal = stoi(pieces[7]);
            string line = "";
            int currInpNum = 0;
            while(getline(loadInput, line)){ // While getline is still running
                if(line != firstLine){ // If the line isn't the first line
                    split(line, '/', pieces, 11);
                    currInpNum = stoi(pieces[1]);
                    if(pieces[0] == "Prop"){
                        props[currInpNum].setCurrentRent(stoi(pieces[2]));
                        if(pieces[3] == "0"){
                            props[currInpNum].setIfMortgaged(false);
                        }
                        else{
                            props[currInpNum].setIfMortgaged(true);
                        }
                        props[currInpNum].setOwner(stoi(pieces[4]));
                        props[currInpNum].setNumHouses(stoi(pieces[5]));
                        props[currInpNum].setNumHotels(stoi(pieces[6]));
                        if(pieces[7] == "0"){
                            props[currInpNum].setIfMonopolized(false);
                        }
                        else{
                            props[currInpNum].setIfMonopolized(true);
                        }
                    }
                    else if(pieces[0] == "Chance"){
                        if(pieces[2] == "0"){
                            chance[currInpNum].setAccessed(false);
                        }
                        else{
                            chance[currInpNum].setAccessed(false);
                        }
                    }
                    else if(pieces[0] == "Comm"){
                        if(pieces[2] == "0"){
                            community[currInpNum].setAccessed(false);
                        }
                        else{
                            community[currInpNum].setAccessed(false);
                        }
                    }
                    else{
                        users[currInpNum].setUsername(pieces[2]);
                        users[currInpNum].setMoney(stoi(pieces[3]));
                        users[currInpNum].setGetOutOfJail(stoi(pieces[4]));
                        users[currInpNum].setSpace(stoi(pieces[5]));
                        users[currInpNum].setNumUtil(stoi(pieces[6]));
                        users[currInpNum].setNumRail(stoi(pieces[7]));
                        if(pieces[8] == "0"){
                            users[currInpNum].setIsReal(false);
                        }
                        else{
                            users[currInpNum].setIsReal(true);
                        }
                        users[currInpNum].setNumDoubles(stoi(pieces[9]));
                        if(pieces[10] == "0"){
                            users[currInpNum].setInJail(false);
                        }
                        else{
                            users[currInpNum].setInJail(true);
                        }
                    }

                }
            }

            for(int i = 0; i < turnOrderString.length(); i++){
                turnOrderChar = turnOrderString[i];
                turnOrder.push_back(stoi(turnOrderChar));
            }
            return true;
        }
        else{
            return false;
        }

    }
    else{ // If the file failed to open
        return false;
    }
}

bool Board::sellHouses(int userInput, int moneyNeeded){ //Asks for user input on what house(s) they want to sell, then sells them back to the bank and gives back the correct value to the user.
    bool boolBrown = false; //Initialize all variables
    int housesBrown = 0;
    int hotelsBrown = 0;
    bool boolLightBlue = false;
    int housesLightBlue = 0;
    int hotelsLightBlue = 0;
    bool boolPink = false;
    int housesPink = 0;
    int hotelsPink = 0;
    bool boolOrange = false;
    int housesOrange = 0;
    int hotelsOrange = 0;
    bool boolRed = false;
    int housesRed = 0;
    int hotelsRed = 0;
    bool boolYellow = false;
    int housesYellow = 0;
    int hotelsYellow = 0;
    bool boolGreen = false;
    int housesGreen = 0;
    int hotelsGreen = 0;
    bool boolDarkBlue = false;
    int housesDarkBlue = 0;
    int hotelsDarkBlue = 0;
    string currColor = "";
    bool housesAnything = false;
    bool validInput = false;
    int numHousesTarget = 0;
    int numHotelsTarget = 0;
    int prop1 = 0;
    int prop2 = 0;
    int prop3 = 0;
    int sellingChoiceInt = 0;
    int propsInColor = 0;
    int totalMoney = 0;
    int propNum = 0;

    for(int i = 0; i < 40; i++){ // This loop counts how many houses on each color the user has
        if(props[i].getOwner() == userInput && (props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0)){
            housesAnything = true;
            currColor = props[i].getColor();
            if(currColor == "Brown"){
                boolBrown = true;
                housesBrown = housesBrown + props[i].getNumHouses();
                hotelsBrown = hotelsBrown + props[i].getNumHotels();
            }
            else if(currColor == "Light Blue"){
                boolLightBlue = true;
                housesLightBlue = housesLightBlue + props[i].getNumHouses();
                hotelsLightBlue = hotelsLightBlue + props[i].getNumHotels();
            }
            else if(currColor == "Pink"){
                boolPink = true;
                housesPink = housesPink + props[i].getNumHouses();
                hotelsPink = hotelsPink + props[i].getNumHotels();
            }
            else if(currColor == "Orange"){
                boolOrange = true;
                housesOrange = housesOrange + props[i].getNumHouses();
                hotelsOrange = hotelsOrange + props[i].getNumHotels();
            }
            else if(currColor == "Red"){
                boolRed = true;
                housesRed = housesRed + props[i].getNumHouses();
                hotelsRed = hotelsRed + props[i].getNumHotels();
            }
            else if(currColor == "Yellow"){
                boolYellow = true;
                housesYellow = housesYellow + props[i].getNumHouses();
                hotelsYellow = hotelsYellow + props[i].getNumHotels();
            }
            else if(currColor == "Green"){
                boolGreen = true;
                housesGreen = housesGreen + props[i].getNumHouses();
                hotelsGreen = hotelsGreen + props[i].getNumHotels();
            }
            else if(currColor == "Dark Blue"){
                boolDarkBlue = true;
                housesDarkBlue = housesDarkBlue + props[i].getNumHouses();
                hotelsDarkBlue = hotelsDarkBlue + props[i].getNumHotels();
            }
        }
    }

    if(housesAnything == false){
        if(users[userInput].getIsReal() == true){
            cout << "You have no properties with installments." << endl;
        }
        return false;
    }
    else{
        if(users[userInput].getIsReal() == true){
            string sellingChoice = "";
            cout << "You can sell " << housePName << " and " << hotelPName << " to the bank for half their original cost." << endl;
            cout << "Which color would you like to sell installments on?" << endl;
            if(boolBrown == true){
                cout << "Brown - " << hotelsBrown << " " << hotelPName << ", " << housesBrown << " " << housePName << endl;
            }
            if(boolLightBlue == true){
                cout << "Light Blue - " << hotelsLightBlue << " " << hotelPName << ", " << housesLightBlue << " " << housePName << endl;
            }
            if(boolPink == true){
                cout << "Pink - " << hotelsPink << " " << hotelPName << ", " << housesPink << " " << housePName << endl;
            }
            if(boolOrange == true){
                cout << "Orange - " << hotelsOrange << " " << hotelPName << ", " << housesOrange << " " << housePName << endl;
            }
            if(boolRed == true){
                cout << "Red - " << hotelsRed << " " << hotelPName << ", " << housesRed << " " << housePName << endl;
            }
            if(boolYellow == true){
                cout << "Yellow - " << hotelsYellow << " " << hotelPName << ", " << housesYellow << " " << housePName << endl;
            }
            if(boolGreen == true){
                cout << "Green - " << hotelsGreen << " " << hotelPName << ", " << housesGreen << " " << housePName << endl;
            }
            if(boolDarkBlue == true){
                cout << "Dark Blue - " << hotelsDarkBlue << " " << hotelPName << ", " << housesDarkBlue << " " << housePName << endl;
            }
            cout << "1 - Don't sell anything" << endl;
            cin >> sellingChoice;
            string lowerInput = turnLower(sellingChoice);
            if(lowerInput == "brown"){
                if(boolBrown == true){
                    validInput = true;
                    currColor = "Brown";
                    numHousesTarget = housesBrown;
                    numHotelsTarget = hotelsBrown;
                }
            }
            else if(lowerInput == "light blue"){
                if(boolLightBlue == true){
                    validInput = true;
                    currColor = "Light Blue";
                    numHousesTarget = housesLightBlue;
                    numHotelsTarget = hotelsLightBlue;
                }
            }
            else if(lowerInput == "pink"){
                if(boolPink == true){
                    validInput = true;
                    currColor = "Pink";
                    numHousesTarget = housesPink;
                    numHotelsTarget = hotelsPink;
                }
            }
            else if(lowerInput == "orange"){
                if(boolOrange == true){
                    validInput = true;
                    currColor = "Orange";
                    numHousesTarget = housesOrange;
                    numHotelsTarget = hotelsOrange;
                }
            }
            else if(lowerInput == "red"){
                if(boolRed == true){
                    validInput = true;
                    currColor = "Red";
                    numHousesTarget = housesRed;
                    numHotelsTarget = hotelsRed;
                }
            }
            else if(lowerInput == "yellow"){
                if(boolYellow == true){
                    validInput = true;
                    currColor = "Yellow";
                    numHousesTarget = housesYellow;
                    numHotelsTarget = hotelsYellow;
                }
            }
            else if(lowerInput == "green"){
                if(boolGreen == true){
                    validInput = true;
                    currColor = "Green";
                    numHousesTarget = housesGreen;
                    numHotelsTarget = hotelsGreen;
                }
            }
            else if(lowerInput == "dark blue"){
                if(boolDarkBlue == true){
                    validInput = true;
                    currColor = "Dark Blue";
                    numHousesTarget = housesDarkBlue;
                    numHotelsTarget = hotelsDarkBlue;
                }
            }
            else if(lowerInput == "1"){
                return true;
            }

            while(validInput == false){
                cout << "Please enter a valid color (or 1 to exit):" << endl;
                cin >> sellingChoice;
                lowerInput = turnLower(sellingChoice);
                if(lowerInput == "brown"){
                    if(boolBrown == true){
                        validInput = true;
                        currColor = "Brown";
                        numHousesTarget = housesBrown;
                        numHotelsTarget = hotelsBrown;
                    }
                }
                else if(lowerInput == "light blue"){
                    if(boolLightBlue == true){
                        validInput = true;
                        currColor = "Light Blue";
                        numHousesTarget = housesLightBlue;
                        numHotelsTarget = hotelsLightBlue;
                    }
                }
                else if(lowerInput == "pink"){
                    if(boolPink == true){
                        validInput = true;
                        currColor = "Pink";
                        numHousesTarget = housesPink;
                        numHotelsTarget = hotelsPink;
                    }
                }
                else if(lowerInput == "orange"){
                    if(boolOrange == true){
                        validInput = true;
                        currColor = "Orange";
                        numHousesTarget = housesOrange;
                        numHotelsTarget = hotelsOrange;
                    }
                }
                else if(lowerInput == "red"){
                    if(boolRed == true){
                        validInput = true;
                        currColor = "Red";
                        numHousesTarget = housesRed;
                        numHotelsTarget = hotelsRed;
                    }
                }
                else if(lowerInput == "yellow"){
                    if(boolYellow == true){
                        validInput = true;
                        currColor = "Yellow";
                        numHousesTarget = housesYellow;
                        numHotelsTarget = hotelsYellow;
                    }
                }
                else if(lowerInput == "green"){
                    if(boolGreen == true){
                        validInput = true;
                        currColor = "Green";
                        numHousesTarget = housesGreen;
                        numHotelsTarget = hotelsGreen;
                    }
                }
                else if(lowerInput == "dark blue"){
                    if(boolDarkBlue == true){
                        validInput = true;
                        currColor = "Dark Blue";
                        numHousesTarget = housesDarkBlue;
                        numHotelsTarget = hotelsDarkBlue;
                    }
                }
                else if(lowerInput == "1"){
                    return true;
                }
            }

            cout << "On " << currColor << " properties, you have: " << hotelPName << " - " << numHotelsTarget << ", " << housePName << " - " << numHousesTarget << "." << endl;
            cout << "How many " << hotelPName << " do you want to sell? (Selling a " << hotelName << " reduces that property to 4 " << housePName << ")" << endl;
            cout << "NOTE: You cannot sell any " << housePName << " until all " << hotelPName << " have been sold." << endl;
            while(validInput == false){
                cout << "Please enter a number between 0 and " << numHotelsTarget << ":" << endl;
                cin >> sellingChoice;
                for(int i = 0; i < sellingChoice.length(); i++){ //Loop through to make sure it's a numerical input
                    if(sellingChoice[i] < 48 || sellingChoice[i] > 57){
                        validInput = false;
                        break;
                    }
                }
                if(validInput = true){
                    if(stoi(sellingChoice) < 0 || stoi(sellingChoice) > numHotelsTarget){ //Make sure the number entered is in the range of the hotels available
                        validInput = false;
                    }
                }
            }

            sellingChoiceInt = stoi(sellingChoice);

            if(sellingChoiceInt != 0){
                for(int i = 0; i < 40; i++){ //Loop through each property
                    if(sellingChoiceInt == 0){ //If there are no more hotels that want to be sold
                        break;
                    }
                    if(props[i].getColor() == currColor && props[i].getNumHotels() != 0){ //If the property is in the correct color
                        if(props[i].getNumHotels() != 0){ //If the number of hotels on the property is not already 0
                            props[i].setNumHotels(0);
                            props[i].setNumHouses(4);
                            numHotelsTarget--;
                            numHousesTarget = numHousesTarget + 4;
                            totalMoney = totalMoney + (props[i].getHouseCost() / 2);
                            sellingChoiceInt--;
                            cout << "You sold 1 " << hotelName << " on " << props[i].getName() << endl;
                        }
                    }
                }
            }
            users[userInput].setMoney(users[userInput].getMoney() + totalMoney); //Give the money to the user
            cout << "You have received " << moneySign << totalMoney << ". You now have " << moneySign << users[userInput].getMoney() << endl;
            validInput = false;

            if(numHotelsTarget == 0){
                cout << "On " << currColor << " properties, you now have: " << hotelPName << " - " << numHotelsTarget << ", " << housePName << " - " << numHousesTarget << "." << endl;
                cout << "How many " << housePName << " do you want to sell?" << endl;
                while(validInput == false){
                    cout << "Please enter a number between 0 and " << numHousesTarget << ":" << endl;
                    cin >> sellingChoice;
                    for(int i = 0; i < sellingChoice.length(); i++){ //Loop through to make sure it's a numerical input
                        if(sellingChoice[i] < 48 || sellingChoice[i] > 57){
                            validInput = false;
                            break;
                        }
                    }
                    if(validInput = true){
                        if(stoi(sellingChoice) < 0 || stoi(sellingChoice) > numHousesTarget){ //Make sure the number entered is in the range of the houses available
                            validInput = false;
                        }
                    }
                }

                sellingChoiceInt = stoi(sellingChoice);
                totalMoney = 0;
                if(currColor == "Brown" || currColor == "Dark Blue"){
                    propsInColor = 2;
                }
                else{
                    propsInColor = 3;
                }

                while(sellingChoiceInt != 0){ //Loop through until all houses WANTED to be sold are sold
                    propNum = 0; //Reset the propNum to 0
                    for(int i = 0; i < 40; i++){ //Loop through each property
                        if(sellingChoiceInt == 0){ //If there are no more houses that want to be sold
                            break;
                        }
                        if(props[i].getColor() == currColor){ //If the property is in the correct color
                            propNum++;
                            if((! (propNum <= (propsInColor - (numHousesTarget % propsInColor)))) && props[i].getNumHouses() != 0){ //If the current property is NOT less developed than ones after it AND there is at least one house on the property
                                props[i].setNumHouses(props[i].getNumHouses() - 1);
                                numHousesTarget--;
                                totalMoney = totalMoney + (props[i].getHouseCost() / 2);
                                sellingChoiceInt--;
                                if(propNum == 1){
                                    prop1++;
                                }
                                else if(propNum == 2){
                                    prop2++;
                                }
                                else{
                                    prop3++;
                                }
                            }
                        }
                    }
                }

                propNum = 0;

                for(int i = 0; i < 40; i++){ //Loop through each property to output the name of the properties in which houses were sold on.
                    if(props[i].getColor() == currColor){
                        propNum++;
                        if(propNum == 1 && prop1 != 0){
                            if(prop1 == 1){
                                cout << "You sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                            }
                            else{
                                cout << "You sold " << prop1 << " " << housePName << " on " << props[i].getName() << endl;;
                            }
                        }
                        else if(propNum == 2 && prop2 != 0){
                            if(prop2 == 1){
                                cout << "You sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                            }
                            else{
                                cout << "You sold " << prop2 << " " << housePName << " on " << props[i].getName() << endl;
                            }
                        }
                        else if(propNum == 3 && prop3 != 0){
                            if(prop3 == 1){
                                cout << "You sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                            }
                            else{
                                cout << "You sold " << prop3 << " " << housePName << " on " << props[i].getName() << endl;
                            }
                        }
                    }
                }

                users[userInput].setMoney(users[userInput].getMoney() + totalMoney); //Give the money to the user
                cout << "You have received " << moneySign << totalMoney << ". You now have " << moneySign << users[userInput].getMoney() << endl;
            }

        }
        else{ //If the user isn't real
            int targetCost = 0;
            while(moneyNeeded > 0){
                for(int i = 0; i < 40; i++){ // This loop counts how many houses on each color the user has AGAIN for each while loop
                    if(props[i].getOwner() == userInput && (props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0)){
                        housesAnything = true;
                        currColor = props[i].getColor();
                        if(currColor == "Brown"){
                            boolBrown = true;
                            housesBrown = housesBrown + props[i].getNumHouses();
                            hotelsBrown = hotelsBrown + props[i].getNumHotels();
                        }
                        else if(currColor == "Light Blue"){
                            boolLightBlue = true;
                            housesLightBlue = housesLightBlue + props[i].getNumHouses();
                            hotelsLightBlue = hotelsLightBlue + props[i].getNumHotels();
                        }
                        else if(currColor == "Pink"){
                            boolPink = true;
                            housesPink = housesPink + props[i].getNumHouses();
                            hotelsPink = hotelsPink + props[i].getNumHotels();
                        }
                        else if(currColor == "Orange"){
                            boolOrange = true;
                            housesOrange = housesOrange + props[i].getNumHouses();
                            hotelsOrange = hotelsOrange + props[i].getNumHotels();
                        }
                        else if(currColor == "Red"){
                            boolRed = true;
                            housesRed = housesRed + props[i].getNumHouses();
                            hotelsRed = hotelsRed + props[i].getNumHotels();
                        }
                        else if(currColor == "Yellow"){
                            boolYellow = true;
                            housesYellow = housesYellow + props[i].getNumHouses();
                            hotelsYellow = hotelsYellow + props[i].getNumHotels();
                        }
                        else if(currColor == "Green"){
                            boolGreen = true;
                            housesGreen = housesGreen + props[i].getNumHouses();
                            hotelsGreen = hotelsGreen + props[i].getNumHotels();
                        }
                        else if(currColor == "Dark Blue"){
                            boolDarkBlue = true;
                            housesDarkBlue = housesDarkBlue + props[i].getNumHouses();
                            hotelsDarkBlue = hotelsDarkBlue + props[i].getNumHotels();
                        }
                    }
                }

                if(housesBrown > 0 || hotelsBrown > 0){ //Check in succession if each color has any installments. The CPU will sell all they need to in one color before moving onto the next one.
                    currColor = "Brown";
                    numHousesTarget = housesBrown;
                    numHotelsTarget = hotelsBrown;
                }
                else if(housesLightBlue > 0 || hotelsLightBlue > 0){
                    currColor = "Light Blue";
                    numHousesTarget = housesLightBlue;
                    numHotelsTarget = hotelsLightBlue;
                }
                else if(housesPink > 0 || hotelsPink > 0){
                    currColor = "Pink";
                    numHousesTarget = housesPink;
                    numHotelsTarget = hotelsPink;
                }
                else if(housesOrange > 0 || hotelsOrange > 0){
                    currColor = "Orange";
                    numHousesTarget = housesOrange;
                    numHotelsTarget = hotelsOrange;
                }
                else if(housesRed > 0 || hotelsRed > 0){
                    currColor = "Red";
                    numHousesTarget = housesRed;
                    numHotelsTarget = hotelsRed;
                }
                else if(housesYellow > 0 || hotelsYellow > 0){
                    currColor = "Yellow";
                    numHousesTarget = housesYellow;
                    numHotelsTarget = hotelsYellow;
                }
                else if(housesGreen > 0 || hotelsGreen > 0){
                    currColor = "Green";
                    numHousesTarget = housesGreen;
                    numHotelsTarget = hotelsGreen;
                }
                else if(housesDarkBlue > 0 || hotelsDarkBlue > 0){
                    currColor = "Dark Blue";
                    numHousesTarget = housesDarkBlue;
                    numHotelsTarget = hotelsDarkBlue;
                }
                else{ //If there are no properties to sell
                    return false;
                }

                for(int i = 0; i < 40; i++){ //Loop through each property until it finds one of the right color. Set the variable targetCost to the house cost for that property.
                    if(props[i].getColor() == currColor){
                        targetCost = (props[i].getHouseCost() / 2);
                        break;
                    }
                }

                int housesNeeded = 0;
                if((moneyNeeded % targetCost) != 0){ //This if statement sets the housesNeeded to the right amount, rounding up.
                    housesNeeded = (moneyNeeded / targetCost) + 1;
                }
                else{
                    housesNeeded = (moneyNeeded / targetCost);
                }
                totalMoney = 0;
                if(housesNeeded > (numHousesTarget + (numHotelsTarget * 5))){ //If there are more houses needed than possible for that color
                    housesNeeded = numHousesTarget + (numHotelsTarget * 5);
                }

                if(housesNeeded != 0){
                    for(int i = 0; i < 40; i++){ //Loop through each property
                        if(housesNeeded == 0){ //If there are no more hotels that want to be sold
                            break;
                        }
                        if(props[i].getColor() == currColor && props[i].getNumHotels() != 0){ //If the property is in the correct color
                            if(props[i].getNumHotels() != 0){ //If the number of hotels on the property is not already 0
                                props[i].setNumHotels(0);
                                props[i].setNumHouses(4);
                                numHotelsTarget--;
                                numHousesTarget = numHousesTarget + 4;
                                totalMoney = totalMoney + (props[i].getHouseCost() / 2);
                                housesNeeded--;
                                cout << users[userInput].getUsername() << " sold 1 " << hotelName << " on " << props[i].getName() << endl;
                            }
                        }
                    }
                }

                if(numHotelsTarget == 0){
                    if(currColor == "Brown" || currColor == "Dark Blue"){
                        propsInColor = 2;
                    }
                    else{
                        propsInColor = 3;
                    }

                    while(housesNeeded != 0){ //Loop through until all houses WANTED to be sold are sold
                        propNum = 0; //Reset the propNum to 0
                        for(int i = 0; i < 40; i++){ //Loop through each property
                            if(housesNeeded == 0){ //If there are no more houses that want to be sold
                                break;
                            }
                            if(props[i].getColor() == currColor){ //If the property is in the correct color
                                propNum++;
                                if((! (propNum <= (propsInColor - (numHousesTarget % propsInColor)))) && props[i].getNumHouses() != 0){ //If the current property is NOT less developed than ones after it AND there is at least one house on the property
                                    props[i].setNumHouses(props[i].getNumHouses() - 1);
                                    numHousesTarget--;
                                    totalMoney = totalMoney + (props[i].getHouseCost() / 2);
                                    housesNeeded--;
                                    if(propNum == 1){
                                        prop1++;
                                    }
                                    else if(propNum == 2){
                                        prop2++;
                                    }
                                    else{
                                        prop3++;
                                    }
                                }
                            }
                        }
                    }

                    propNum = 0;

                    for(int i = 0; i < 40; i++){ //Loop through each property to output the name of the properties in which houses were sold on.
                        if(props[i].getColor() == currColor){
                            propNum++;
                            if(propNum == 1 && prop1 != 0){
                                if(prop1 == 1){
                                    cout << users[userInput].getUsername() << " sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                                }
                                else{
                                    cout << users[userInput].getUsername() << " sold " << prop1 << " " << housePName << " on " << props[i].getName() << endl;
                                }
                            }
                            else if(propNum == 2 && prop2 != 0){
                                if(prop2 == 1){
                                    cout << users[userInput].getUsername() << " sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                                }
                                else{
                                    cout << users[userInput].getUsername() << " sold " << prop2 << " " << housePName << " on " << props[i].getName() << endl;
                                }
                            }
                            else if(propNum == 3 && prop3 != 0){
                                if(prop3 == 1){
                                    cout << users[userInput].getUsername() << " sold 1 " << houseName << " on " << props[i].getName() << "." << endl;
                                }
                                else{
                                    cout << users[userInput].getUsername() << " sold " << prop3 << " " << housePName << " on " << props[i].getName() << endl;
                                }
                            }
                        }
                    }
                }
                moneyNeeded = moneyNeeded - totalMoney;
            }
            users[userInput].setMoney(users[userInput].getMoney() + totalMoney); //Give the money to the user
            cout << users[userInput].getUsername() << " has received " << moneySign << totalMoney << ". They now have " << moneySign << users[userInput].getMoney() << endl;
        }
    }

    return true; //If it has made it this far, return true.
}

void Board::buyHouses(int userInput){ //Asks for user input on what house(s) they want to buy, then buys them from the bank and sets the correct number on the properties
    bool boolBrown = false; //Initialize all variables
    int housesBrown = 0;
    int hotelsBrown = 0;
    bool boolLightBlue = false;
    int housesLightBlue = 0;
    int hotelsLightBlue = 0;
    bool boolPink = false;
    int housesPink = 0;
    int hotelsPink = 0;
    bool boolOrange = false;
    int housesOrange = 0;
    int hotelsOrange = 0;
    bool boolRed = false;
    int housesRed = 0;
    int hotelsRed = 0;
    bool boolYellow = false;
    int housesYellow = 0;
    int hotelsYellow = 0;
    bool boolGreen = false;
    int housesGreen = 0;
    int hotelsGreen = 0;
    bool boolDarkBlue = false;
    int housesDarkBlue = 0;
    int hotelsDarkBlue = 0;
    string currColor = "";
    bool monopolyAnything = false;
    bool validInput = false;
    int numHousesTarget = 0;
    int numHotelsTarget = 0;
    int prop1 = 0;
    int prop2 = 0;
    int prop3 = 0;
    int buyingChoiceInt = 0;
    int propsInColor = 0;
    int totalMoney = 0;
    int capMoney = 0;
    int totalBought = 0;
    bool housesAnything = false;
    int colorHouseCost = 0;
    bool enoughMoney = true;
    int propNum = 0;
    int targetCost = 0;

    if(checkMonopoly("Brown") == true && props[1].getOwner() == userInput && props[1].getNumHotels() != 1 && props[3].getNumHotels() != 1){ //If the color is monopolized AND the current user is the owner of it AND it isn't fully installed
        boolBrown = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Light Blue") == true && props[6].getOwner() == userInput && props[6].getNumHotels() != 1 && props[8].getNumHotels() != 1 && props[9].getNumHotels() != 1){
        boolLightBlue = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Pink") == true && props[11].getOwner() == userInput && props[11].getNumHotels() != 1 && props[13].getNumHotels() != 1 && props[14].getNumHotels() != 1){
        boolPink = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Orange") == true && props[16].getOwner() == userInput && props[16].getNumHotels() != 1 && props[18].getNumHotels() != 1 && props[19].getNumHotels() != 1){
        boolOrange = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Red") == true && props[21].getOwner() == userInput && props[21].getNumHotels() != 1 && props[23].getNumHotels() != 1 && props[24].getNumHotels() != 1){
        boolRed = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Yellow") == true && props[26].getOwner() == userInput && props[26].getNumHotels() != 1 && props[27].getNumHotels() != 1 && props[9].getNumHotels() != 1){
        boolYellow = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Green") == true && props[31].getOwner() == userInput && props[31].getNumHotels() != 1 && props[32].getNumHotels() != 1 && props[34].getNumHotels() != 1){
        boolGreen = true;
        monopolyAnything = true;
    }
    if(checkMonopoly("Dark Blue") == true && props[37].getOwner() == userInput && props[37].getNumHotels() != 1 && props[39].getNumHotels() != 1){
        boolDarkBlue = true;
        monopolyAnything = true;
    }

    if(monopolyAnything == false){
        if(users[userInput].getIsReal() == true){
            cout << "You do not have any properties to build additional installments on." << endl;
        }
        return;
    }

    for(int i = 0; i < 40; i++){ // This loop counts how many houses on each color the user already has
        if(props[i].getOwner() == userInput && (props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0)){
            housesAnything = true;
            currColor = props[i].getColor();
            if(currColor == "Brown"){
                housesBrown = housesBrown + props[i].getNumHouses();
                hotelsBrown = hotelsBrown + props[i].getNumHotels();
            }
            else if(currColor == "Light Blue"){
                housesLightBlue = housesLightBlue + props[i].getNumHouses();
                hotelsLightBlue = hotelsLightBlue + props[i].getNumHotels();
            }
            else if(currColor == "Pink"){
                housesPink = housesPink + props[i].getNumHouses();
                hotelsPink = hotelsPink + props[i].getNumHotels();
            }
            else if(currColor == "Orange"){
                housesOrange = housesOrange + props[i].getNumHouses();
                hotelsOrange = hotelsOrange + props[i].getNumHotels();
            }
            else if(currColor == "Red"){
                housesRed = housesRed + props[i].getNumHouses();
                hotelsRed = hotelsRed + props[i].getNumHotels();
            }
            else if(currColor == "Yellow"){
                housesYellow = housesYellow + props[i].getNumHouses();
                hotelsYellow = hotelsYellow + props[i].getNumHotels();
            }
            else if(currColor == "Green"){
                housesGreen = housesGreen + props[i].getNumHouses();
                hotelsGreen = hotelsGreen + props[i].getNumHotels();
            }
            else if(currColor == "Dark Blue"){
                housesDarkBlue = housesDarkBlue + props[i].getNumHouses();
                hotelsDarkBlue = hotelsDarkBlue + props[i].getNumHotels();
            }
        }
    }

    if(users[userInput].getIsReal() == true){
        string buyingChoice = "";
        cout << "You can buy " << housePName << " and " << hotelPName << " from the bank to increase rent on your properties." << endl;
        cout << "Which color would you like to buy installments on?" << endl << endl;
        if(boolBrown == true){
            cout << "'Brown' - Currently has " << hotelsBrown << " " << hotelPName << ", " << housesBrown << " " << housePName << endl;
        }
        if(boolLightBlue == true){
            cout << "'Light Blue' - Currently has " << hotelsLightBlue << " " << hotelPName << ", " << housesLightBlue << " " << housePName << endl;
        }
        if(boolPink == true){
            cout << "'Pink' - Currently has " << hotelsPink << " " << hotelPName << ", " << housesPink << " " << housePName << endl;
        }
        if(boolOrange == true){
            cout << "'Orange' - Currently has " << hotelsOrange << " " << hotelPName << ", " << housesOrange << " " << housePName << endl;
        }
        if(boolRed == true){
            cout << "'Red' - Currently has " << hotelsRed << " " << hotelPName << ", " << housesRed << " " << housePName << endl;
        }
        if(boolYellow == true){
            cout << "Yellow - Currently has " << hotelsYellow << " " << hotelPName << ", " << housesYellow << " " << housePName << endl;
        }
        if(boolGreen == true){
            cout << "'Green' - Currently has " << hotelsGreen << " " << hotelPName << ", " << housesGreen << " " << housePName << endl;
        }
        if(boolDarkBlue == true){
            cout << "'Dark Blue' - Currently has " << hotelsDarkBlue << " " << hotelPName << ", " << housesDarkBlue << " " << housePName << endl;
        }
        cout << "1 - Don't buy anything" << endl << endl;
        getline(cin, buyingChoice);
        string lowerInput = turnLower(buyingChoice);
        if(lowerInput == "brown"){
            if(boolBrown == true){
                validInput = true;
                currColor = "Brown";
                numHousesTarget = housesBrown;
                numHotelsTarget = hotelsBrown;
            }
        }
        else if(lowerInput == "light blue"){
            if(boolLightBlue == true){
                validInput = true;
                currColor = "Light Blue";
                numHousesTarget = housesLightBlue;
                numHotelsTarget = hotelsLightBlue;
            }
        }
        else if(lowerInput == "pink"){
            if(boolPink == true){
                validInput = true;
                currColor = "Pink";
                numHousesTarget = housesPink;
                numHotelsTarget = hotelsPink;
            }
        }
        else if(lowerInput == "orange"){
            if(boolOrange == true){
                validInput = true;
                currColor = "Orange";
                numHousesTarget = housesOrange;
                numHotelsTarget = hotelsOrange;
            }
        }
        else if(lowerInput == "red"){
            if(boolRed == true){
                validInput = true;
                currColor = "Red";
                numHousesTarget = housesRed;
                numHotelsTarget = hotelsRed;
            }
        }
        else if(lowerInput == "yellow"){
            if(boolYellow == true){
                validInput = true;
                currColor = "Yellow";
                numHousesTarget = housesYellow;
                numHotelsTarget = hotelsYellow;
            }
        }
        else if(lowerInput == "green"){
            if(boolGreen == true){
                validInput = true;
                currColor = "Green";
                numHousesTarget = housesGreen;
                numHotelsTarget = hotelsGreen;
            }
        }
        else if(lowerInput == "dark blue"){
            if(boolDarkBlue == true){
                validInput = true;
                currColor = "Dark Blue";
                numHousesTarget = housesDarkBlue;
                numHotelsTarget = hotelsDarkBlue;
            }
        }
        else if(lowerInput == "1"){
            return;
        }

        while(validInput == false){
            cout << "Please enter a valid color (or 1 to exit):" << endl;
            getline(cin, buyingChoice);
            lowerInput = turnLower(buyingChoice);
            if(lowerInput == "brown"){
                if(boolBrown == true){
                    validInput = true;
                    currColor = "Brown";
                    numHousesTarget = housesBrown;
                    numHotelsTarget = hotelsBrown;
                }
            }
            else if(lowerInput == "light blue"){
                if(boolLightBlue == true){
                    validInput = true;
                    currColor = "Light Blue";
                    numHousesTarget = housesLightBlue;
                    numHotelsTarget = hotelsLightBlue;
                }
            }
            else if(lowerInput == "pink"){
                if(boolPink == true){
                    validInput = true;
                    currColor = "Pink";
                    numHousesTarget = housesPink;
                    numHotelsTarget = hotelsPink;
                }
            }
            else if(lowerInput == "orange"){
                if(boolOrange == true){
                    validInput = true;
                    currColor = "Orange";
                    numHousesTarget = housesOrange;
                    numHotelsTarget = hotelsOrange;
                }
            }
            else if(lowerInput == "red"){
                if(boolRed == true){
                    validInput = true;
                    currColor = "Red";
                    numHousesTarget = housesRed;
                    numHotelsTarget = hotelsRed;
                }
            }
            else if(lowerInput == "yellow"){
                if(boolYellow == true){
                    validInput = true;
                    currColor = "Yellow";
                    numHousesTarget = housesYellow;
                    numHotelsTarget = hotelsYellow;
                }
            }
            else if(lowerInput == "green"){
                if(boolGreen == true){
                    validInput = true;
                    currColor = "Green";
                    numHousesTarget = housesGreen;
                    numHotelsTarget = hotelsGreen;
                }
            }
            else if(lowerInput == "dark blue"){
                if(boolDarkBlue == true){
                    validInput = true;
                    currColor = "Dark Blue";
                    numHousesTarget = housesDarkBlue;
                    numHotelsTarget = hotelsDarkBlue;
                }
            }
            else if(lowerInput == "1"){
                return;
            }
        }

        if(currColor == "Brown" || currColor == "Dark Blue"){
            propsInColor = 2;
        }
        else{
            propsInColor = 3;
        }

        for(int i = 0; i < 40; i++){ //Loop through each property and find the house cost of the color selected
            if(props[i].getColor() == currColor){
                colorHouseCost = props[i].getHouseCost();
                break;
            }
        }

        int maxHouses = 0;

        if((((propsInColor * 5) - (numHousesTarget + (numHotelsTarget * 5))) * colorHouseCost) > users[userInput].getMoney()){ //If the user doesn't have enough moeny to purchase all the houses possible
            for(int i = 0; i < ((propsInColor * 5) - (numHousesTarget + (numHotelsTarget * 5))); i++){
                if(users[userInput].getMoney() >= ((maxHouses + 1) * colorHouseCost)){
                    maxHouses++;
                }
            }
        }

        if(maxHouses == 0){
            cout << "You can't buy any houses on that color." << endl;
            return;
        }

        cout << "On " << currColor << " properties, you have: " << hotelPName << " - " << numHotelsTarget << ", " << housePName << " - " << numHousesTarget << ", Total installments - " << numHousesTarget + (numHotelsTarget * 5) << "." << endl;
        cout << "How many " << housePName << " do you want to buy in total?" << endl;
        cout << "NOTE: installments will automatically fill up each property individually, starting from the most expensive property and moving toward the least expensive." << endl;
        cout << "You can only buy " << (propsInColor * 5) - (numHousesTarget + (numHotelsTarget * 5)) << " more " << housePName << " on " << currColor << " properties." << endl;
        cout << "You have " << moneySign << users[userInput].getMoney() << ", " << housePName << " cost " << moneySign << colorHouseCost << " each (You have enough to purchase " << maxHouses << ")." << endl;
        validInput = false;
        while(validInput == false){
            validInput = true;
            if(enoughMoney == false){
                cout << "You do not have enough money for that purchase. You can purchase up to " << maxHouses << "." << endl;
            }
            cout << "Please enter a number between 0 and " << maxHouses << ":" << endl;
            cin >> buyingChoice;
            for(int i = 0; i < buyingChoice.length(); i++){ //Loop through to make sure it's a numerical input
                if(buyingChoice[i] < 48 || buyingChoice[i] > 57){
                    validInput = false;
                    break;
                }
            }
            if(validInput == true){
                if(stoi(buyingChoice) < 0){ //Make sure the number entered is in the range of the houses available to buy
                    validInput = false;
                }
                else if(stoi(buyingChoice) > maxHouses){ //Make sure the house is not bigger than
                    validInput = false;
                    enoughMoney = false;
                }
            }
        }

        buyingChoiceInt = stoi(buyingChoice);
        int propNum = 0;


        while(buyingChoiceInt != 0){
            for(int i = 39; i >= 0; i--){ //Loop through each property
                if(buyingChoiceInt == 0){ //If there are no more hotels that want to be purchased
                    break;
                }
                if(props[i].getColor() == currColor){ //If the property is in the correct color
                    if(props[i].getNumHouses() != 4){ //If the number of houses on the property is not already 4
                        props[i].setNumHouses(props[i].getNumHouses() + 1);
                        numHousesTarget++;
                        totalMoney = totalMoney + props[i].getHouseCost();
                        buyingChoiceInt--;
                    }
                    else{
                        props[i].setNumHotels(1);
                        props[i].setNumHouses(0);
                        numHousesTarget = numHousesTarget - 4;
                        numHotelsTarget++;
                        totalMoney = totalMoney + props[i].getHouseCost();
                    }
                }
            }
        }
        users[userInput].setMoney(users[userInput].getMoney() - totalMoney); //Take the money from the user
        cout << "You have been charged " << moneySign << totalMoney << ". You now have " << moneySign << users[userInput].getMoney() << endl;
        cout << "On " << currColor << " properties, you now have: " << hotelPName << " - " << numHotelsTarget << ", " << housePName << " - " << numHousesTarget << endl;
    }
    else{ //If the user isn't real
        while(users[userInput].getMoney() >= 1050){ //TEST THIS AMOUNT
            for(int i = 0; i < 40; i++){ // This loop counts how many houses on each color the user already has AGAIN within the while loop
                if(props[i].getOwner() == userInput && (props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0)){
                    housesAnything = true;
                    currColor = props[i].getColor();
                    if(currColor == "Brown"){
                        housesBrown = housesBrown + props[i].getNumHouses();
                        hotelsBrown = hotelsBrown + props[i].getNumHotels();
                    }
                    else if(currColor == "Light Blue"){
                        housesLightBlue = housesLightBlue + props[i].getNumHouses();
                        hotelsLightBlue = hotelsLightBlue + props[i].getNumHotels();
                    }
                    else if(currColor == "Pink"){
                        housesPink = housesPink + props[i].getNumHouses();
                        hotelsPink = hotelsPink + props[i].getNumHotels();
                    }
                    else if(currColor == "Orange"){
                        housesOrange = housesOrange + props[i].getNumHouses();
                        hotelsOrange = hotelsOrange + props[i].getNumHotels();
                    }
                    else if(currColor == "Red"){
                        housesRed = housesRed + props[i].getNumHouses();
                        hotelsRed = hotelsRed + props[i].getNumHotels();
                    }
                    else if(currColor == "Yellow"){
                        housesYellow = housesYellow + props[i].getNumHouses();
                        hotelsYellow = hotelsYellow + props[i].getNumHotels();
                    }
                    else if(currColor == "Green"){
                        housesGreen = housesGreen + props[i].getNumHouses();
                        hotelsGreen = hotelsGreen + props[i].getNumHotels();
                    }
                    else if(currColor == "Dark Blue"){
                        housesDarkBlue = housesDarkBlue + props[i].getNumHouses();
                        hotelsDarkBlue = hotelsDarkBlue + props[i].getNumHotels();
                    }
                }
            }

            if(((housesOrange + (hotelsOrange * 5)) < 15) && users[userInput].getMoney() >= 1100 && boolOrange == true){ //Check in succession if each color is available for buying houses. The CPU will buy all they can on each color until they have $1000 or less.
                currColor = "Orange";
                numHousesTarget = housesOrange;
                numHotelsTarget = hotelsOrange;
                capMoney = 1100;
            }
            else if(((housesRed + (hotelsRed * 5)) < 15) && users[userInput].getMoney() >= 1150 && boolRed == true){
                currColor = "Red";
                numHousesTarget = housesRed;
                numHotelsTarget = hotelsRed;
                capMoney = 1150;
            }
            else if(((housesYellow + (hotelsYellow * 5)) < 15) && users[userInput].getMoney() >= 1150 && boolYellow == true){
                currColor = "Yellow";
                numHousesTarget = housesYellow;
                numHotelsTarget = hotelsYellow;
                capMoney = 1150;
            }
            else if(((housesPink + (hotelsPink * 5)) < 15) && users[userInput].getMoney() >= 1100 && boolPink == true){
                currColor = "Pink";
                numHousesTarget = housesPink;
                numHotelsTarget = hotelsPink;
                capMoney = 1100;
            }
            else if(((housesGreen + (hotelsGreen * 5)) < 15) && users[userInput].getMoney() >= 1200 && boolGreen == true){
                currColor = "Green";
                numHousesTarget = housesGreen;
                numHotelsTarget = hotelsGreen;
                capMoney = 1200;
            }
            else if(((housesDarkBlue + (hotelsDarkBlue * 5)) < 15) && users[userInput].getMoney() >= 1200 && boolDarkBlue == true){
                currColor = "Dark Blue";
                numHousesTarget = housesDarkBlue;
                numHotelsTarget = hotelsDarkBlue;
                capMoney = 1200;
            }
            else if(((housesLightBlue + (hotelsLightBlue * 5)) < 15) && users[userInput].getMoney() >= 1050 && boolLightBlue == true){
                currColor = "Light Blue";
                numHousesTarget = housesLightBlue;
                numHotelsTarget = hotelsLightBlue;
                capMoney = 1050;
            }
            else if(((housesBrown + (hotelsBrown * 5)) < 15) && users[userInput].getMoney() >= 1050 && boolBrown == true){
                currColor = "Brown";
                numHousesTarget = housesBrown;
                numHotelsTarget = hotelsBrown;
                capMoney = 1050;
            }
            else{ //If there are no properties to buy
                return;
            }

            for(int i = 0; i < 40; i++){ //Loop through each property until it finds one of the right color. Set the variable targetCost to the house cost for that property.
                if(props[i].getColor() == currColor){
                    targetCost = props[i].getHouseCost();
                    break;
                }
            }

            if(currColor == "Brown" || currColor == "Dark Blue"){
                propsInColor = 2;
            }
            else{
                propsInColor = 3;
            }

            while((numHousesTarget + (numHotelsTarget * 5)) < (5 * propsInColor) && users[userInput].getMoney() >= capMoney){ //Loop through until all houses possible to buy on that color are bought.
                propNum = 0; //Reset the propNum to 0
                for(int i = 0; i < 40; i++){ //Loop through each property
                    // if(housesNeeded == 0){ //If there are no more houses that want to be sold
                    //     break;
                    // }
                    if(users[userInput].getMoney() < capMoney){
                        break;
                    }
                    if(props[i].getColor() == currColor){ //If the property is in the correct color
                        propNum++;
                        if((! (propNum <= ((numHousesTarget + (numHotelsTarget * 5)) % propsInColor))) && props[i].getNumHotels() != 1){ //If the current property is NOT more developed than ones before it AND there isn't a hotel on the property
                            if(props[i].getNumHouses() == 4){
                                props[i].setNumHouses(0);
                                props[i].setNumHotels(1);
                                numHousesTarget = numHousesTarget - 4;
                                numHotelsTarget = numHotelsTarget + 1;
                            }
                            else{
                                props[i].setNumHouses(props[i].getNumHouses() + 1);
                                numHousesTarget++;
                            }
                            totalMoney = totalMoney + targetCost;
                            users[userInput].setMoney(users[userInput].getMoney() - targetCost);
                            totalBought++;
                        }
                    }
                }
            }

            if(currColor == "Brown"){
                boolBrown = false;
            }
            else if(currColor == "Light Blue"){
                boolLightBlue = false;
            }
            else if(currColor == "Pink"){
                boolPink = false;
            }
            else if(currColor == "Orange"){
                boolOrange = false;
            }
            else if(currColor == "Red"){
                boolRed = false;
            }
            else if(currColor == "Yellow"){
                boolYellow = false;
            }
            else if(currColor == "Green"){
                boolGreen = false;
            }
            else if(currColor == "Dark Blue"){
                boolDarkBlue = false;
            }

            propNum = 0;

            if(totalBought == 1){
                cout << users[userInput].getUsername() << " bought 1 " << houseName << " on " << currColor << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " bought " << totalBought << " " << housePName << " on " << currColor << "." << endl;
            }
        }
        if(totalMoney > 0){
            cout << users[userInput].getUsername() << " has been charged " << moneySign << totalMoney << ". They now have " << moneySign << users[userInput].getMoney() << endl;
        }
    }
}

void Board::allPropNames(){
    for(int i = 0; i < 40; i++){
        cout << i << " - " << props[i].getName();
        if(props[i].getIsOwnable() == false){
            cout << endl;
        }
        else if(props[i].getOwner() == -1){
            cout << " - UNOWNED" << endl;
        }
        else{
            cout << " - Owned by " << users[props[i].getOwner()].getUsername() << endl;
        }
    }
}

void Board::viewSpace(int number){
    string currentRentString = "";
    string color = props[number].getColor();

    cout << props[number].getName() << ":" << endl << endl;

    if(color == "Go"){
        cout << "The first space on the board. Anyone who passes collects " << moneySign << "200." << endl;
    }
    else if(color == "Comm"){
        cout << "Draw a card from the " << commName << " cards and follow card's instructions." << endl;
    }
    else if(color == "IT"){
        cout << "Pay 10% of your total money to the middle, or " << moneySign << "200, whichever is cheapest." << endl;
    }
    else if(color == "Railroad"){
        cout << " __________________________________ " << endl;
        cout << "| ________________________________ |" << endl;
        cout << "|" << printSpace(props[number].getName(), 34, false) << props[number].getName() << printSpace(props[number].getName(), 34, true) << "|" << endl;
        currentRentString = "(" + railName + ")";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "| ________________________________ |" << endl;
        currentRentString = "Rent" + moneySign + to_string(props[number].getRentInit()) + ".";
        cout << "|Rent" << printSpace(currentRentString, 34, false) << printSpace(currentRentString, 34, true) << moneySign << to_string(props[number].getRentInit()) << ".|" << endl;
        currentRentString = "If 2 " + railName + "s are owned" + moneySign + to_string(props[number].getRent1()) + ".";
        cout << "|If 2 " << railName << "s are owned" << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << moneySign << props[number].getRent1() << ".|" << endl;
        currentRentString = "If 3" + to_string(props[number].getRent2()) + ".";
        cout << "|If 3" << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << props[number].getRent2() << ".|" << endl;
        currentRentString = "If 4" + to_string(props[number].getRent3()) + ".";
        cout << "|If 4" << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << props[number].getRent3() << ".|" << endl;
        cout << "|                                  |" << endl;
        currentRentString = "Mortgage Value" + moneySign + to_string(props[number].getMortgageValue()) + ".";
        cout << "|Mortgage Value" << printSpace(currentRentString, 34, false) << printSpace(currentRentString, 34, true) << moneySign << props[number].getMortgageValue() << ".|" << endl;
        cout << "|                                  |" << endl;
        currentRentString = "Current Rent: " + moneySign + to_string(props[number].getCurrentRent());
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        if(props[number].getOwner() == -1){
            currentRentString = "Currently Unowned!";
        }
        else{
            currentRentString = "Current Owner: " + users[props[number].getOwner()].getUsername();
        }
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "|__________________________________|" << endl;
    }
    else if(color == "Chance"){
        cout << "Draw a card from the " << chanceName << " cards and follow card's instructions." << endl;
    }
    else if(color == "Jail"){
        cout << "When passing by, you are 'Just Visiting' Jail." << endl;
        cout << "Don't roll 3 doubles in a row or land on the 'Go to Jail' space, or else you're in trouble!" << endl;
    }
    else if(color == "Utility"){
        cout << " __________________________________ " << endl;
        cout << "| ________________________________ |" << endl;
        cout << "|" << printSpace(props[number].getName(), 34, false) << props[number].getName() << printSpace(props[number].getName(), 34, true) << "|" << endl;
        currentRentString = "(" + props[number].getColor() + ")";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "| ________________________________ |" << endl;
        cout << "|    If one 'Utility' is owned     |" << endl;
        cout << "|   rent is 4 times amount shown   |" << endl;
        cout << "|   on dice.                       |" << endl;
        cout << "|    If both 'Utilities' are owned |" << endl;
        cout << "|   rent is 4 times amount shown   |" << endl;
        cout << "|   on dice.                       |" << endl;
        cout << "|                                  |" << endl;
        currentRentString = "Mortgage Value" + moneySign + to_string(props[number].getMortgageValue()) + ".";
        cout << "|Mortgage Value" << printSpace(currentRentString, 34, false) << printSpace(currentRentString, 34, true) << moneySign << props[number].getMortgageValue() << ".|" << endl;
        if(props[number].getOwner() == -1){
            currentRentString = "Currently Unowned!";
        }
        else{
            currentRentString = "Current Owner: " + users[props[number].getOwner()].getUsername();
        }
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "|__________________________________|" << endl;
    }
    else if(color == "Free Parking"){
        cout << "Landing on this space gives you all the money in the middle of the board." << endl;
    }
    else if(color == "Go To Jail"){
        cout << "Landing on this space sends you directly to jail. Be careful!" << endl;
    }
    else if(color == "LT"){
        cout << "Pay " << moneySign << "75 to the middle of the board." << endl;
    }
    else{
        cout << " __________________________________ " << endl;
        cout << "| ________________________________ |" << endl;
        cout << "||           TITLE DEED           ||" << endl;
        cout << "||" << printSpace(props[number].getName(), 32, false) << props[number].getName() << printSpace(props[number].getName(), 32, true) << "||" << endl;
        currentRentString = "(" + props[number].getColor() + ")";
        cout << "||" << printSpace(currentRentString, 32, false) << currentRentString << printSpace(currentRentString, 32, true) << "||" << endl;
        cout << "||________________________________||" << endl;
        currentRentString = "Rent " + moneySign + to_string(props[number].getRentInit()) + ".";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        currentRentString = "With 1 " + houseName + moneySign + " " + to_string(props[number].getRent1()) + ".";
        cout << "|With 1 " << houseName << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << moneySign << " " << props[number].getRent1() << ".|" << endl;
        currentRentString = "With 2 " + housePName + to_string(props[number].getRent2()) + ".";
        cout << "|With 2 " << housePName << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << props[number].getRent2() << ".|" << endl;
        currentRentString = "With 3 " + housePName + to_string(props[number].getRent3()) + ".";
        cout << "|With 3 " << housePName << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << props[number].getRent3() << ".|" << endl;
        currentRentString = "With 4 " + housePName + to_string(props[number].getRent4()) + ".";
        cout << "|With 4 " << housePName << printSpace(currentRentString,34,false) << printSpace(currentRentString,34,true) << props[number].getRent4() << ".|" << endl;
        currentRentString = "With " + hotelName + " " + moneySign + to_string(props[number].getRentHotel()) + ".";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        currentRentString = "Mortgage Value " + moneySign + to_string(props[number].getMortgageValue()) + ".";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        currentRentString = housePName + " cost " + moneySign + to_string(props[number].getHouseCost()) + ". each";
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "|                                  |" << endl;
        currentRentString = "Current Rent: " + moneySign + to_string(props[number].getCurrentRent());
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        if(props[number].getOwner() == -1){
            currentRentString = "Currently Unowned!";
        }
        else{
            currentRentString = "Current Owner: " + users[props[number].getOwner()].getUsername();
        }
        cout << "|" << printSpace(currentRentString, 34, false) << currentRentString << printSpace(currentRentString, 34, true) << "|" << endl;
        cout << "|__________________________________|" << endl;
    }
}

bool Board::drawCard(bool chanceOrComm, int userInput, int diceRoll){ //Drawing a card from the deck, uses a random number generator to pick a random card, makes sure it hasn't been drawn yet.
    int cardDraw = rand() % 16;
    int cardValue = 0;
    bool allAccessed = true;
    bool canPay = true;

    if(chanceOrComm == false){ //If it's a chance card
        while(chance[cardDraw].getAccessed() == true){
            cardDraw = rand() % 16;
        }
        chance[cardDraw].setAccessed(true);
        cardValue = chance[cardDraw].getValue();
        for(int i = 0; i < 16; i++){
            if(chance[i].getAccessed() == false){
                allAccessed = false;
                break;
            }
        }
        if(allAccessed == true){ //If all have been accessed
            shuffleCards(false); //Shuffle all chance cards
        }

        if(users[userInput].getIsReal() == true){
            cout << "You drew: " << chance[cardDraw].getDescription() << endl;
        }
        else{
            cout << users[userInput].getUsername() << " drew: " << chance[cardDraw].getDescription() << endl;
        }
        ////////////////////////////////////////////////////////
        if(chance[cardDraw].getCardType() == 1){ //Go to a space
            passedGoCheck(cardValue, userInput);
            users[userInput].setSpace(cardValue);
            if(cardValue == 24 || cardValue == 11 || cardValue == 39){ //If it's just moving to a regular space
                canPay = landProperty(cardValue, userInput);
            }
            else if(cardValue == 5){ //If it's moving to Reading Railroad
                canPay = landRailroad(5, userInput, false);
            }
        }
        ///////////////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 2){ //Receive money from bank
            users[userInput].setMoney(users[userInput].getMoney() + cardValue);
            if(users[userInput].getIsReal() == true){
                cout << "You receieved " << moneySign << cardValue << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " received " << moneySign << cardValue << "." << endl;
            }
        }
        ///////////////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 3){ //Pay money to the middle
            if(cardValue > users[userInput].getMoney()){ //If they can't afford to pay
                canPay = saveBankruptcy(userInput, cardValue);
            }
            if(canPay == false){
                if(users[userInput].getIsReal() == false){
                    bankruptcy(userInput, -1);
                    return false;
                }
                else{
                    return false;
                }
            }
            else{
                users[userInput].setMoney(users[userInput].getMoney() - cardValue);
                middleVal = middleVal + cardValue;
                if(users[userInput].getIsReal() == true){
                    cout << "You have been charged " << moneySign << cardValue << ", you now have " << moneySign << users[userInput].getMoney() << "." << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " has been charged " << moneySign << cardValue << ", they now have " << moneySign << users[userInput].getMoney() << "." << endl;
                }
            }
            cout << "The middle now has " << moneySign << middleVal << "." << endl;
        }
        ////////////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 4){ //Get out of jail card
            users[userInput].setGetOutOfJail(users[userInput].getGetOutOfJail() + 1);
            if(users[userInput].getIsReal() == true){
                cout << "You now have " << users[userInput].getGetOutOfJail() << " Get Out of Jail Free cards!" << endl;
            }
            else{
                cout << users[userInput].getUsername() << " now has " << users[userInput].getGetOutOfJail() << " Get Out of Jail Free cards." << endl;
            }
        }
        //////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 5){ //Go to jail
            goToJail(userInput);
        }
        //////////////////////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 6){ //Money exchange between players
            int moneyOwed = (numUsers - 1) * 50;
            if(moneyOwed > users[userInput].getMoney()){ //If they can't afford to pay
                canPay = saveBankruptcy(userInput, moneyOwed);
            }
            if(canPay == false){
                if(users[userInput].getIsReal() == false){
                    bankruptcy(userInput, 0);
                    return false;
                }
                else{
                    return false;
                }
            }
            users[userInput].setMoney(users[userInput].getMoney() - moneyOwed); //Charge the user
            if(users[userInput].getIsReal() == true){
                cout << "You have been charged " << moneySign << moneyOwed << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " has been charged " << moneySign << moneyOwed << "." << endl;
            }

            for(int i = 0; i < numUsers; i++){ //Loop through all users and give them their money.
                if(i != userInput){
                    users[i].setMoney(users[i].getMoney() + 50);
                    if(users[i].getIsReal() == true){
                        cout << "You have receieved " << moneySign << "50." << endl;
                    }
                    else{
                        cout << users[i].getUsername() << " has receieved " << moneySign << "50." << endl;
                    }
                }
            }
        }
        ///////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 7){ //Repairs
            int totalHouses = 0;
            int totalHotels = 0;
            int owedForRepairs = 0;

            for(int i = 0; i < 40; i++){ //Loop through each property to count how many houses/hotels the user has
                if(props[i].getOwner() == userInput){
                    totalHouses = totalHouses + props[i].getNumHouses();
                    totalHotels = totalHotels + props[i].getNumHotels();
                }
            }
            owedForRepairs = (25 * totalHouses) + (100 * totalHotels);
            if(users[userInput].getIsReal() == true){
                cout << "You own " << totalHouses << " " << housePName << " and " << totalHotels << " " << hotelPName << ". You owe " << moneySign << owedForRepairs << " to the middle." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " owns " << totalHouses << " " << housePName << " and " << totalHotels << " " << hotelPName << ". They owe " << moneySign << owedForRepairs << " to the middle." << endl;
            }

            if(owedForRepairs > users[userInput].getMoney()){ //If they can't pay
                canPay = saveBankruptcy(userInput, owedForRepairs);
            }

            if(canPay == false){
                if(users[userInput].getIsReal() == false){
                    bankruptcy(userInput, -1);
                    return false;
                }
                else{
                    return false;
                }
            }

            users[userInput].setMoney(users[userInput].getMoney() - owedForRepairs);
            middleVal = middleVal + owedForRepairs;
            if(users[userInput].getIsReal() == true){
                cout << "You have been charged " << moneySign << owedForRepairs << ", you now have " << moneySign << users[userInput].getMoney() << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " has been charged " << moneySign << owedForRepairs << ", they now have " << moneySign << users[userInput].getMoney() << "." << endl;
            }
            cout << "The middle now has " << moneySign << middleVal << "." << endl;
        }
        ////////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 8){ //Go back 3 spaces
            users[userInput].setSpace(users[userInput].getSpace() - 3);
            int spaceLanded = users[userInput].getSpace();
            cout << "3 spaces back is " << props[spaceLanded].getName() << endl;

            if(spaceLanded == 4){ //If income tax
                canPay = landTax(userInput, 4);
            }
            else if(spaceLanded == 19){ //If New York Avenue
                canPay = landProperty(19, userInput);
            }
            else{ //If community chest
                canPay = drawCard(true, userInput, diceRoll);
            }
        }
        /////////////////////////////////////////////////////////////
        else if(chance[cardDraw].getCardType() == 9){ //Utility (x10)
            if(users[userInput].getSpace() == 7){
                users[userInput].setSpace(12);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[12].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[12].getName() << endl;
                }
                canPay = landUtility(12, userInput, true, diceRoll);
            }
            else if(users[userInput].getSpace() == 22){
                users[userInput].setSpace(28);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[28].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[28].getName() << endl;
                }
                canPay = landUtility(28, userInput, true, diceRoll);
            }
            else{ //space 36
                users[userInput].setSpace(12);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[12].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[12].getName() << endl;
                }

                users[userInput].setMoney(users[userInput].getMoney() + 200);
                if(users[userInput].getIsReal() == true){
                    cout << "You have passed go and received " << moneySign << "200." << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " has passed go and received " << moneySign << "200." << endl;
                }

                canPay = landUtility(12, userInput, true, diceRoll);
            }
        }
        /////////////////////
        else{ //Railroad (x2)
            if(users[userInput].getSpace() == 7){
                users[userInput].setSpace(15);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[15].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[15].getName() << endl;
                }
                canPay = landRailroad(15, userInput, true);
            }
            else if(users[userInput].getSpace() == 22){
                users[userInput].setSpace(25);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[25].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[25].getName() << endl;
                }
                canPay = landRailroad(25, userInput, true);
            }
            else{ //space 36
                users[userInput].setSpace(5);
                if(users[userInput].getIsReal() == true){
                    cout << "You landed on " << props[5].getName() << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " landed on " << props[5].getName() << endl;
                }

                users[userInput].setMoney(users[userInput].getMoney() + 200);
                if(users[userInput].getIsReal() == true){
                    cout << "You have passed go and received " << moneySign << "200." << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " has passed go and received " << moneySign << "200." << endl;
                }
                canPay = landRailroad(5, userInput, true);
            }
        }
    }
    else{ //NO TYPE 8 FOR COMMUNITY
        while(community[cardDraw].getAccessed() == true){
            cardDraw = rand() % 16;
        }
        community[cardDraw].setAccessed(true);
        cardValue = community[cardDraw].getValue();
        for(int i = 0; i < 16; i++){
            if(community[i].getAccessed() == false){
                allAccessed = false;
                break;
            }
        }
        if(allAccessed == true){ //If all have been accessed
            shuffleCards(false); //Shuffle all chance cards
        }

        if(users[userInput].getIsReal() == true){
            cout << "You drew: " << community[cardDraw].getDescription() << endl;
        }
        else{
            cout << users[userInput].getUsername() << " drew: " << community[cardDraw].getDescription() << endl;
        }
        ////////////////////////////////////////////////////////
        if(community[cardDraw].getCardType() == 1){ //Go to go
            users[userInput].setMoney(users[userInput].getMoney() + 200);
            if(users[userInput].getIsReal() == true){
                cout << "You have passed go and received " << moneySign << "200." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " has passed go and received " << moneySign << "200." << endl;
            }
            users[userInput].setSpace(0);
        }
        ///////////////////////////////////////////////////////////////////////
        else if(community[cardDraw].getCardType() == 2){ //Receive money from bank
            users[userInput].setMoney(users[userInput].getMoney() + cardValue);
            if(users[userInput].getIsReal() == true){
                cout << "You receieved " << moneySign << cardValue << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " received " << moneySign << cardValue << "." << endl;
            }
        }
        ///////////////////////////////////////////////////////////////////////
        else if(community[cardDraw].getCardType() == 3){ //Pay money to the middle
            if(cardValue > users[userInput].getMoney()){ //If they can't afford to pay
                canPay = saveBankruptcy(userInput, cardValue);
            }
            if(canPay == false){
                if(users[userInput].getIsReal() == false){
                    bankruptcy(userInput, -1);
                }
                else{
                    return false;
                }
            }
            else{
                users[userInput].setMoney(users[userInput].getMoney() - cardValue);
                middleVal = middleVal + cardValue;
                if(users[userInput].getIsReal() == true){
                    cout << "You have been charged " << moneySign << cardValue << ", you now have " << moneySign << users[userInput].getMoney() << "." << endl;
                }
                else{
                    cout << users[userInput].getUsername() << " has been charged " << moneySign << cardValue << ", they now have " << moneySign << users[userInput].getMoney() << "." << endl;
                }
            }
            cout << "The middle now has " << moneySign << middleVal << "." << endl;
        }
        ////////////////////////////////////////////////////////////////////
        else if(community[cardDraw].getCardType() == 4){ //Get out of jail card
            users[userInput].setGetOutOfJail(users[userInput].getGetOutOfJail() + 1);
            if(users[userInput].getIsReal() == true){
                cout << "You now have " << users[userInput].getGetOutOfJail() << " Get Out of Jail Free cards!" << endl;
            }
            else{
                cout << users[userInput].getUsername() << " now has " << users[userInput].getGetOutOfJail() << " Get Out of Jail Free cards." << endl;
            }
        }
        //////////////////////////////////////////////////////////
        else if(community[cardDraw].getCardType() == 5){ //Go to jail
            goToJail(userInput);
        }
        //////////////////////////////////////////////////////////////////////////////
        else if(community[cardDraw].getCardType() == 6){ //Money exchange between players
            int moneyToCollect = (numUsers - 1) * 50;
            bool currentBankrupt = false;

            for(int i = 0; i < numUsers; i++){ //Loop through each user and test if they can pay. If they can't, run bankruptcy().
                if(i != userInput){
                    if(users[i].getMoney() < 50){
                        currentBankrupt = saveBankruptcy(i, 50);
                    }
                    if(currentBankrupt = false){
                        bankruptcy(i, userInput);
                    }
                    else{
                        users[i].setMoney(users[i].getMoney() - 50);
                        users[userInput].setMoney(users[userInput].getMoney() + 50);
                        cout << users[i].getUsername() << " paid " << users[userInput].getUsername() << " " << moneySign << "50." << endl;
                    }
                }
            }

            cout << users[userInput].getUsername() << " now has " << moneySign << users[userInput].getMoney() << "." << endl;
        }
        ///////////////////////////////////////////////////////
        else{ //Repairs
            int totalHouses = 0;
            int totalHotels = 0;
            int owedForRepairs = 0;

            for(int i = 0; i < 40; i++){ //Loop through each property to count how many houses/hotels the user has
                if(props[i].getOwner() == userInput){
                    totalHouses = totalHouses + props[i].getNumHouses();
                    totalHotels = totalHotels + props[i].getNumHotels();
                }
            }
            owedForRepairs = (40 * totalHouses) + (115 * totalHotels);
            if(users[userInput].getIsReal() == true){
                cout << "You own " << totalHouses << " " << housePName << " and " << totalHotels << " " << hotelPName << ". You owe " << moneySign << owedForRepairs << " to the middle." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " owns " << totalHouses << " " << housePName << " and " << totalHotels << " " << hotelPName << ". They owe " << moneySign << owedForRepairs << " to the middle." << endl;
            }

            if(owedForRepairs > users[userInput].getMoney()){ //If they can't pay
                canPay = saveBankruptcy(userInput, owedForRepairs);
            }

            if(canPay == false){
                if(users[userInput].getIsReal() == false){
                    bankruptcy(userInput, -1);
                }
                else{
                    return false;
                }
            }

            users[userInput].setMoney(users[userInput].getMoney() - owedForRepairs);
            middleVal = middleVal + owedForRepairs;
            if(users[userInput].getIsReal() == true){
                cout << "You have been charged " << moneySign << owedForRepairs << ", you now have " << moneySign << users[userInput].getMoney() << "." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " has been charged " << moneySign << owedForRepairs << ", they now have " << moneySign << users[userInput].getMoney() << "." << endl;
            }
            cout << "The middle now has " << moneySign << middleVal << "." << endl;
        }
    }
    return canPay;
}

void Board::viewBoard(){ //Displays the board with lines and numbers, and displays what spaces each user is on.
    string spaceText = "";

    cout << " ________________________________" << endl;
    cout << "|  |  |  |  |  |  |  |  |  |  |  |" << endl;
    cout << "|10|11|12|13|14|15|16|17|18|19|20|" << endl;
    cout << "|--|--------------------------|--|" << endl;
    cout << "|9 |                          |21|" << endl;
    cout << "|--|   ->->->->->->->->->->-  |--|" << endl;
    cout << "|8 |   ^                   V  |22|" << endl;
    cout << "|--|   |                   |  |--|" << endl;
    cout << "|7 |   ^                   V  |23|" << endl;
    cout << "|--|   |                   |  |--|" << endl;
    cout << "|6 |   ^                   V  |24|" << endl;
    cout << "|--|   |" << printSpace(versionName, 19, false) << versionName << printSpace(versionName, 19, true) << "|  |--|" << endl;
    cout << "|5 |   ^      ------       V  |25|" << endl;
    cout << "|--|   |     MONOPOLY      |  |--|" << endl;
    cout << "|4 |   ^                   V  |26|" << endl;
    cout << "|--|   |                   |  |--|" << endl;
    cout << "|3 |   ^                   V  |27|" << endl;
    cout << "|--|   |                   |  |--|" << endl;
    cout << "|2 |   ^                   V  |28|" << endl;
    cout << "|--|   -<-<-<-<-<-<-<-<-<-<-  |--|" << endl;
    cout << "|1 |                          |29|" << endl;
    cout << "|--|--------------------------|--|" << endl;
    cout << "|0 |39|38|37|36|35|34|33|32|31|30|" << endl;
    cout << "|__|__|__|__|__|__|__|__|__|__|__|" << endl << endl;
    for(int i = 0; i < numUsers; i++){
        if(users[i].getInJail() == true){
            spaceText = "Jail";
        }
        else{
            spaceText = props[users[i].getSpace()].getName();
        }

        cout << users[i].getUsername() << " is currently on space " << users[i].getSpace() << " (" << spaceText << ")" << endl;
        cout << "    -Has " << moneySign << users[i].getMoney() << endl;
    }
}

bool Board::mortgageProperty(int userInput){ //Mortgages property from the inputted user. Returns false if they CAN'T mortgage property, returns true if they can and choose not to/did mortgage.
    if(users[userInput].getIsReal() == true){ //If the user is real
        string choice;
        vector <int> mortgageCheckProps;
        mortgageCheckProps = printAllProps(userInput, 1);
        bool checkValidity = true;
        if(mortgageCheckProps.size() == 0){ //If the vector from printAllProps is empty
            cout << "No properties are available to mortgage" << endl;
            return false;
        }
        cout << endl << "40 - Don't mortgage anything." << endl << endl;
        cout << "Which property would you like to mortgage? (Enter a property number below)" << endl;
        cin >> choice;
        for(int i = 0; i < choice.length(); i++){ //Loop through to make sure it's a numerical input
            if(choice[i] < 48 || choice[i] > 57){
                checkValidity = false;
                break;
            }
        }

        if(checkValidity == true){
            for(int i = 0; i < mortgageCheckProps.size(); i++){
                if(stoi(choice) == mortgageCheckProps[i] || choice == "40"){
                    checkValidity = true;
                    break;
                }
            }
        }


        while(checkValidity == false){
            cout << "Please enter a number of a property that you own and is mortgeagable." << endl;
            cout << "Which property would you like to mortgage? (Enter a property number below)" << endl;
            cin >> choice;
            for(int i = 0; i < choice.length(); i++){ //Loop through to make sure it's a numerical input
                if(choice[i] < 48 || choice[i] > 57){
                    checkValidity = false;
                    break;
                }
            }

            if(checkValidity == true){
                for(int i = 0; i < mortgageCheckProps.size(); i++){
                    if(stoi(choice) == mortgageCheckProps[i] || choice == "40"){
                        checkValidity = true;
                        break;
                    }
                }
            }
        }

        if(choice == "40"){ //If they don't want to mortgage anything
            return true;
        }
        else{
            string mortgageColor = props[stoi(choice)].getColor();
            bool checkHasHouses = false;
            for(int i = 0; i < 40; i++){ //Loop through every property, checking if any property on that color has houses/hotels
                if(props[i].getColor() == mortgageColor){
                    if(props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0){
                        checkHasHouses = true;
                        break;
                    }
                }
            }
            while(checkHasHouses == true){ //While the properties' color still has houses on it
                checkHasHouses = false; //Reset the boolean to false
                string sellHousesInput = "";
                cout << "One or more properties of the same color of the property you want to mortgage have " << housePName << "/" << hotelPName << ". You cannot mortgage unless all installments are sold." << endl;
                cout << "Would you like to sell installments?" << endl;
                cout << "1. Yes, sell " << housePName << "/" << hotelPName << endl;
                cout << "2. No, don't mortgage the property" << endl;
                cin >> sellHousesInput;
                while(sellHousesInput != "1" && sellHousesInput != "2"){ //Input validation
                    cout << "Please enter 1 or 2." << endl;
                    cin >> sellHousesInput;
                }
                if(sellHousesInput == "1"){ //If they want to sell houses
                    sellHouses(userInput, 0);
                }
                else{ //If they don't want to mortgage the property
                    return true;
                }
                for(int i = 0; i < 40; i++){ //Loop through every property, checking if any property on that color has houses/hotels
                    if(props[i].getColor() == mortgageColor){
                        if(props[i].getNumHouses() > 0 || props[i].getNumHotels() > 0){
                            checkHasHouses = true;
                            break;
                        }
                    }
                }
            }
            props[stoi(choice)].setIfMortgaged(true); //ONLY RUNS IF THEY SOLD ALL THE HOUSES AND/OR WANT TO MORTGAGE STILL
            for(int i = 0; i < 40; i++){ //Loops through each property and sets any with the same color to unmonopolized
                if(props[i].getColor() == mortgageColor){
                    props[i].setIfMonopolized(false);
                }
            }
            users[userInput].setMoney(users[userInput].getMoney() + props[stoi(choice)].getMortgageValue());
            cout << "You have mortgaged " << props[stoi(choice)].getName() << ". You have received " << moneySign << props[stoi(choice)].getMortgageValue() << "." << endl;
        }
    }
    else{ //If the user isn't real
        for(int i = 0; i < 40; i++){ //Loop through each property, and find the first one that is unmonopolized. Mortgage that property.
            if(props[i].getIfMonopolized() == false && props[i].getOwner() == userInput){
                props[i].setIfMortgaged(true);
                users[userInput].setMoney(users[userInput].getMoney() + props[i].getMortgageValue());
                cout << users[userInput].getUsername() << " has mortgaged " << props[i].getName() << ". They have received " << moneySign << props[i].getMortgageValue() << "." << endl;
                return true;
            }
        }
        return false; //Return false if they couldn't find a property to mortgage
    }
}

void Board::unMortgageProperty(int userInput){
    if(users[userInput].getIsReal() == true){ //If the user is real
        string choice;
        string propChoice;
        vector <int> mortgageCheckProps;
        mortgageCheckProps = printAllProps(userInput, 0);
        bool checkValidity = true;
        if(mortgageCheckProps.size() == 0){ //If the vector from printAllProps is empty
            cout << endl << "No properties are available to unmortgage" << endl;
            return;
        }
        cout << endl << "40 - Don't unmortgage anything." << endl << endl;
        cout << "Which property would you like to unmortgage? (Enter a property number below)" << endl;
        cin >> choice;

        for(int i = 0; i < choice.length(); i++){ //Loop through to make sure it's a numerical input
            if(choice[i] < 48 || choice[i] > 57){
                checkValidity = false;
                break;
            }
        }
        if(checkValidity == true){
            for(int i = 0; i < mortgageCheckProps.size(); i++){
                if(stoi(choice) == mortgageCheckProps[i] || choice == "40"){
                    checkValidity = true;
                    break;
                }
            }
        }

        while(checkValidity == false){
            cout << "Please enter a number of a property that you own and is unmortgeagable." << endl;
            cout << "Which property would you like to unmortgage? (Enter a property number below)" << endl;
            cin >> choice;

            for(int i = 0; i < choice.length(); i++){ //Loop through to make sure it's a numerical input
                if(choice[i] < 48 || choice[i] > 57){
                    checkValidity = false;
                    break;
                }
            }
            if(checkValidity == true){
                for(int i = 0; i < mortgageCheckProps.size(); i++){
                    if(stoi(choice) == mortgageCheckProps[i] || choice == "40"){
                        checkValidity = true;
                        break;
                    }
                }
            }
        }

        if(choice == "40"){ //If they don't want to unmortgage anything
            return;
        }

        while(users[userInput].getMoney() < (props[stoi(choice)].getMortgageValue() + (props[stoi(choice)].getMortgageValue() / 10))){ //While they don't have enough money to unmortgage
            cout << "You do not have enough money to unmortgage this property and not be bankrupt! Would you like to mortgage other property/sell installments?" << endl;
            cout << "1. Mortgage property" << endl;
            cout << "2. Sell " << housePName << "/" << hotelPName << endl;
            cout << "3. Don't unmortgage the property" << endl;
            cin >> propChoice;
            while(propChoice.length() != 1 || propChoice[0] < 49 || propChoice[0] > 51){ //Input validation
                cout << "Please enter a number between 1 and 3." << endl;
                cin >> propChoice;
            }
            if(propChoice == "1"){ //If they want to mortgage property
                mortgageProperty(userInput);
            }
            else if(propChoice == "2"){ //If they want to sell houses/hotels
                sellHouses(userInput, 0);
            }
            else{ //If they don't want to buy the property
                return;
            }
        }
        users[userInput].setMoney(users[userInput].getMoney() - (props[stoi(choice)].getMortgageValue() + (props[stoi(choice)].getMortgageValue() / 10)));
        props[stoi(choice)].setIfMortgaged(false);
        cout << "You have unmortgaged " << props[stoi(choice)].getName() << ". You have been charged " << moneySign << (props[stoi(choice)].getMortgageValue() + (props[stoi(choice)].getMortgageValue() / 10)) << "." << endl;
    }
    else{ //If the user isn't real
        for(int i = 0; i < 40; i++){ //Loop through each property, and find the first one.
            if(props[i].getOwner() == userInput && props[i].getIfMortgaged() == true){
                if(users[userInput].getMoney() >= (props[i].getMortgageValue() + (props[i].getMortgageValue() / 10))){ //If they can unmortgage and still not be bankrupt
                    props[i].setIfMortgaged(false);
                    users[userInput].setMoney(users[userInput].getMoney() - (props[i].getMortgageValue() + (props[i].getMortgageValue() / 10)));
                    cout << users[userInput].getUsername() << " has unmortgaged " << props[i].getName() << ". They have been charged " << moneySign << (props[i].getMortgageValue() + (props[i].getMortgageValue() / 10)) << "." << endl;
                }
                else{ //If they can't unmortgage past this point
                    break;
                }
            }
        }
    }
}

void Board::setTurnNum(int turnInput){ //Sets the turn number
    turnNumber = turnInput;
}

int Board::getTurnNum(){ //Gets the turn number
    return turnNumber;
}

void Board::setTurnOrder(vector <int> turnOrderInput){ //Sets the turn order
    turnOrder = turnOrderInput;
}

vector <int> Board::getTurnOrder(){ //Gets the turn order string
    return turnOrder;
}

bool Board::passedGoCheck(int newSpace, int userInput){ //Checks whether the user passed go with the current action or not.
    if(users[userInput].getSpace() > newSpace){
        users[userInput].setMoney(users[userInput].getMoney() + 200);
        if(users[userInput].getIsReal() == true){
            cout << "You have passed go and received " << moneySign << "200." << endl;
        }
        else{
            cout << users[userInput].getUsername() << " has passed go and received " << moneySign << "200." << endl;
        }
    }
}

bool Board::landProperty(int spaceInput, int userInput){
    bool bankruptcyCheck = false;

    if(props[spaceInput].getOwner() == userInput){
        if(users[userInput].getIsReal() == true){
            cout << "You already own this property." << endl;
        }
        else{
            cout << users[userInput].getUsername() << " already owns this property." << endl;
        }
        return true;
    }

    if(users[userInput].getIsReal() == true){ //If the user is real
        if(props[spaceInput].getOwner() == -1){ //If unowned
            string propChoice = "";
            cout << "This space is unowned. Would you like to buy it? (Cost = " << moneySign << props[spaceInput].getPropCost() << ")" << endl;
            cout << "You currently have " << moneySign << users[userInput].getMoney() << "." << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "3. View all property details" << endl;
            cin >> propChoice;
            while(propChoice.length() != 1 || propChoice[0] < 49 || propChoice[0] > 51){ //Input validation
                cout << "Please enter a number between 1 and 3." << endl;
                cin >> propChoice;
            }

            if(propChoice == "3"){ //View the property details
                viewSpace(spaceInput);
            }

            while(propChoice == "3"){ //Loop for user to view the details as many times as they want
                cout << "This space is unowned. Would you like to buy it? (Cost = " << moneySign << props[spaceInput].getPropCost() << ")" << endl;
                cout << "You currently have " << moneySign << users[userInput].getMoney() << "." << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "3. View all property details" << endl;
                cin >> propChoice;
                while(propChoice.length() != 1 || propChoice[0] < 49 || propChoice[0] > 51){ //Input validation
                    cout << "Please enter a number between 1 and 3." << endl;
                    cin >> propChoice;
                }

                if(propChoice == "3"){ //View the property details
                    viewSpace(spaceInput);
                }
            }

            if(propChoice == "2"){ //If they don't want the property
                return true;
            }
            else if(propChoice == "1"){ //If they want to buy the property
                while(users[userInput].getMoney() <= props[spaceInput].getPropCost()){ //While they don't have enough money to buy
                    cout << "You do not have enough money to buy this property and not be bankrupt! Would you like to mortgage property/sell installments?" << endl;
                    cout << "1. Mortgage property" << endl;
                    cout << "2. Sell " << housePName << "/" << hotelPName << endl;
                    cout << "3. Don't buy the property" << endl;
                    cin >> propChoice;
                    while(propChoice.length() != 1 || propChoice[0] < 49 || propChoice[0] > 51){ //Input validation
                        cout << "Please enter a number between 1 and 3." << endl;
                        cin >> propChoice;
                    }
                    if(propChoice == "1"){ //If they want to mortgage property
                        mortgageProperty(userInput);
                    }
                    else if(propChoice == "2"){ //If they want to sell houses/hotels
                        sellHouses(userInput, 0);
                    }
                    else{ //If they don't want to buy the property
                        return true;
                    }
                }
                users[userInput].setMoney((users[userInput].getMoney()) - (props[spaceInput].getPropCost()));
                cout << "You have been charged " << moneySign << props[spaceInput].getPropCost() << ". You now have " << moneySign << users[userInput].getMoney() << "." << endl;
                props[spaceInput].setOwner(userInput);
                cout << "You now own " << props[spaceInput].getName() << "!" << endl;
                if(checkMonopoly(props[spaceInput].getColor()) == true){ //If there is a new monopoly
                    cout << "You now own a monopoly on " << props[spaceInput].getColor() << " properties!" << endl;
                }
                return true;
            }
        }
        else{ //If owned
            cout << "You owe " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << props[spaceInput].getCurrentRent() << " for the rent on this property." << endl;
            if(props[spaceInput].getCurrentRent() > users[userInput].getMoney()){
                bankruptcyCheck = saveBankruptcy(userInput, props[spaceInput].getCurrentRent());
                if(bankruptcyCheck == false){
                    return false;
                }
            }

            users[userInput].setMoney(users[userInput].getMoney() - props[spaceInput].getCurrentRent());
            users[props[spaceInput].getOwner()].setMoney(users[props[spaceInput].getOwner()].getMoney() + props[spaceInput].getCurrentRent());
            cout << "You paid " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << props[spaceInput].getCurrentRent() << " for " << props[spaceInput].getName() << endl;
            return true;
        }
    }
    else{ //If the user is a CPU
        if(props[spaceInput].getOwner() == -1){ //If unowned
            if(props[spaceInput].getPropCost() <= users[userInput].getMoney()){ //AND they can afford it, they will buy it.
                users[userInput].setMoney((users[userInput].getMoney()) - (props[spaceInput].getPropCost()));
                props[spaceInput].setOwner(userInput);
                cout << users[userInput].getUsername() << " has purchased " << props[spaceInput].getName() << " for " << moneySign << props[spaceInput].getPropCost() << "." << endl;
                cout << "They now have " << moneySign << users[userInput].getMoney() << endl;
                if(checkMonopoly(props[spaceInput].getColor()) == true){ //If there is a new monopoly
                    cout << "They now own a monopoly on " << props[spaceInput].getColor() << " properties." << endl;
                }
                return true;
            }
        }
        else{ //If owned
            cout << users[userInput].getUsername() << " owes " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << props[spaceInput].getCurrentRent() << " for the rent on this property." << endl;
            if(props[spaceInput].getCurrentRent() > users[userInput].getMoney()){
                bankruptcyCheck = saveBankruptcy(userInput, props[spaceInput].getCurrentRent());
                if(bankruptcyCheck == false){
                    bankruptcy(userInput, props[spaceInput].getOwner());
                    return false;
                }
            }

            users[userInput].setMoney(users[userInput].getMoney() - props[spaceInput].getCurrentRent());
            users[props[spaceInput].getOwner()].setMoney(users[props[spaceInput].getOwner()].getMoney() + props[spaceInput].getCurrentRent());
            cout << users[userInput].getUsername() << " paid " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << props[spaceInput].getCurrentRent() << " for " << props[spaceInput].getName() << endl;
            return true;
        }
    }
}

bool Board::landRailroad(int spaceInput, int userInput, bool multiplier){ //Does action for railroad space, multiplier is if from a card.
    int numOwnedByUser = 0; //Initialize all variables
    int rentForNumOwned = 0;
    bool landPropertyReturn = false;
    int savedRailSpace = 0;

    if(props[spaceInput].getOwner() == userInput){
        if(users[userInput].getIsReal() == true){
            cout << "You already own this " << railName << "." << endl;
        }
        else{
            cout << users[userInput].getUsername() << " already owns this " << railName << "." << endl;
        }
        return true;
    }

    if(props[spaceInput].getOwner() == -1){ //If it's unowned
        landProperty(spaceInput, userInput); //Run the landProperty() function for the railroad
        for(int i = 5; i < 36; i = i + 10){ //Loop through each railroad
            if(props[i].getOwner() == userInput){ //If the railroad is owned by the user
                numOwnedByUser++;
            }
        }

        if(numOwnedByUser == 1){
            rentForNumOwned = 25;
        }
        else if(numOwnedByUser == 2){
            rentForNumOwned = 50;
        }
        else if(numOwnedByUser == 3){
            rentForNumOwned = 100;
        }
        else if(numOwnedByUser == 4){
            rentForNumOwned = 150;
        }

        for(int i = 5; i < 36; i = i + 10){ //Loop through each railroad AGAIN
            if(props[i].getOwner() == userInput){ //If the railroad is owned by the user
                props[i].setCurrentRent(rentForNumOwned);
                savedRailSpace = i;
            }
        }

        if(users[userInput].getIsReal() == true && numOwnedByUser != users[userInput].getNumRail()){ //If the user is real AND they just purchased a railroad
            users[userInput].setNumRail(numOwnedByUser); //Set the number of railroads for that user
            cout << "You now own " << users[userInput].getNumRail() << " " << railName << "(s). Current rent is " << moneySign << props[savedRailSpace].getCurrentRent() << " for each of your " << railName << "s." << endl;
        }
        else if(users[userInput].getIsReal() == false && numOwnedByUser != users[userInput].getNumRail()){ //If the user is not real AND they just purchased a railroad
            users[userInput].setNumRail(numOwnedByUser); //Set the number of railroads for that user
            cout << users[userInput].getUsername() << " now owns " << users[userInput].getNumRail() << " " << railName << "(s). Current rent is " << moneySign << props[savedRailSpace].getCurrentRent() << " for each of their " << railName << "s." << endl;
        }

        users[userInput].setNumRail(numOwnedByUser); //Set the number of railroads for that user

        return true;
    }
    else{ //If the railroad is owned
        if(multiplier == true){ //If it's from a card that multiplies the rent by 2, set the current rent to its actual rent times 2.
            props[spaceInput].setCurrentRent(props[spaceInput].getCurrentRent() * 2);
            landPropertyReturn = landProperty(spaceInput, userInput); //Run the landProperty() function for the railroad
            props[spaceInput].setCurrentRent(props[spaceInput].getCurrentRent() / 2); //Reset the rent to normal
        }
        else{ //If it isn't from a multiplier card
            landPropertyReturn = landProperty(spaceInput, userInput); //Run the landProperty() function for the railroad
        }

        return landPropertyReturn;
    }
}

bool Board::landUtility(int spaceInput, int userInput, bool fromCard, int diceRoll){ //Does action for utility space, does x10 no matter what if the boolean is true.
    int userNumUtil = 0;
    int amountOwed = 0;
    bool canPay = false;
    int multiplier = 0;

    if(props[spaceInput].getOwner() == userInput){
        if(users[userInput].getIsReal() == true){
            cout << "You already own this Utility." << endl;
        }
        else{
            cout << users[userInput].getUsername() << " already owns this Utility." << endl;
        }
        return true;
    }

    if(props[spaceInput].getOwner() == -1){ //If it's unowned
        landProperty(spaceInput, userInput); //Run the landProperty() function for the utility

        if(props[12].getOwner() == userInput){
            userNumUtil++;
        }
        if(props[28].getOwner() == userInput){
            userNumUtil++;
        }

        if(users[userInput].getIsReal() == true && userNumUtil != users[userInput].getNumUtil()){ //If the user is real AND they just purchased a utility
            users[userInput].setNumUtil(userNumUtil); //Set the number of utilities for that user
            if(userNumUtil == 2){ //If they own 2 utilities
                cout << "You now own 2 utilities. Current rent is 10 times the amount shown on the dice for each of your utilities." << endl;
            }
            else{ //If they own 1
                cout << "You now own 1 utility. Current rent is 4 times the amount shown on the dice." << endl;
            }
        }
        else if(users[userInput].getIsReal() == false && userNumUtil != users[userInput].getNumUtil()){ //If the user is not real AND they just purchased a utility
            users[userInput].setNumUtil(userNumUtil); //Set the number of utilities for that user
            if(userNumUtil == 2){ //If they own 2 utilities
                cout << users[userInput].getUsername() << " now owns 2 utilities. Current rent is 10 times the amount shown on the dice for each of their utilities." << endl;
            }
            else{ //If they own 1
                cout << users[userInput].getUsername() << " now owns 1 utility. Current rent is 4 times the amount shown on the dice." << endl;
            }
        }
        users[userInput].setNumUtil(userNumUtil); //Set the number of utilities for that user
    }
    else{ //If it is owned
        if(users[props[spaceInput].getOwner()].getNumUtil() == 2 || fromCard == true){ //If the multiplier is 10x or from a card that says it is
            amountOwed = diceRoll * 10;
            multiplier = 10;
        }
        else{ //If the multiplier is 4x
            amountOwed = diceRoll * 4;
            multiplier = 4;
        }

        if(users[userInput].getIsReal() == true){ //If the user is real
            cout << "You owe " << users[props[spaceInput].getOwner()].getUsername() << " " << multiplier << "x the amount on your roll (" << moneySign << amountOwed << ")." << endl;
            if(amountOwed > users[userInput].getMoney()){
                canPay = saveBankruptcy(userInput, amountOwed);
                if(canPay == false){
                    return false;
                }
            }
            users[userInput].setMoney(users[userInput].getMoney() - amountOwed);
            users[props[spaceInput].getOwner()].setMoney(users[props[spaceInput].getOwner()].getMoney() + amountOwed);
            cout << "You paid " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << amountOwed << "." << endl;
            return true;
        }
        else{
            cout << users[userInput].getUsername() << " owes " << users[props[spaceInput].getOwner()].getUsername() << " " << multiplier << "x the amount on their roll (" << moneySign << amountOwed << ")." << endl;
            if(amountOwed > users[userInput].getMoney()){
                canPay = saveBankruptcy(userInput, amountOwed);
                if(canPay == false){
                    bankruptcy(userInput, props[spaceInput].getOwner());
                    return false;
                }
            }
            users[userInput].setMoney(users[userInput].getMoney() - amountOwed);
            users[props[spaceInput].getOwner()].setMoney(users[props[spaceInput].getOwner()].getMoney() + amountOwed);
            cout << users[userInput].getUsername() << " paid " << users[props[spaceInput].getOwner()].getUsername() << " " << moneySign << amountOwed << "." << endl;
            return true;
        }
    }
}

void Board::landFreeParking(int userInput){ //Action for landing on free parking - user receives money from the middle and the middle value is reset to 100.
    if(users[userInput].getIsReal() == true){ //If the user is real
        cout << "Congratulations!" << endl;
        users[userInput].setMoney(users[userInput].getMoney() + middleVal); //Add the value from the middle to their amount
        cout << "You have received " << moneySign << middleVal << " from the middle." << endl;
        middleVal = 100; //Reset the middle value
    }
    else{ //If the user isn't real
        users[userInput].setMoney(users[userInput].getMoney() + middleVal); //Add the value from the middle to their amount
        cout << users[userInput].getUsername() << " landed on Free Parking and received " << moneySign << middleVal << " from the middle." << endl;
        middleVal = 100; //Reset the middle value
    }
    cout << "The money in the middle has been reset to " << moneySign << "100." << endl;
}

bool Board::landTax(int userInput, int spaceInput){ //Action for landing on a tax space - returns true everytime EXCEPT if they can't pay the tax.
    int moneyToMiddle = 0;
    bool enoughToPay = true;

    if(spaceInput == 4){ //If income tax
        if(200 > (users[userInput].getMoney() / 10)){ //If 10% is better
            moneyToMiddle = (users[userInput].getMoney() / 10);
            cout << "Amount owed is " << moneySign << moneyToMiddle << " (10%)." << endl;
        }
        else{ //If $200 is better
            moneyToMiddle = 200;
            cout << "Amount owed is " << moneySign << moneyToMiddle << " (Less money than 10%)." << endl;
        }

        if(users[userInput].getMoney() < moneyToMiddle){ //If they can't afford
            enoughToPay = saveBankruptcy(userInput, moneyToMiddle);
        }
        if(enoughToPay == false){
            if(users[userInput].getIsReal() == false){
                bankruptcy(userInput, -1);
            }
            return false;
        }
    }
    else{ //If luxury tax (space 38)
        moneyToMiddle = 75;
        if(moneyToMiddle > users[userInput].getMoney()){ //If they can't afford to pay
            enoughToPay = saveBankruptcy(userInput, moneyToMiddle);
        }
        if(enoughToPay == false){
            if(users[userInput].getIsReal() == false){
                bankruptcy(userInput, -1);
            }
            return false;
        }
    }

    users[userInput].setMoney(users[userInput].getMoney() - moneyToMiddle);
    middleVal = middleVal + moneyToMiddle;

    if(users[userInput].getIsReal() == true){
        cout << "You have been charged " << moneySign << moneyToMiddle << ", you now have " << moneySign << users[userInput].getMoney() << "." << endl;
    }
    else{
        cout << users[userInput].getUsername() << " has been charged " << moneySign << moneyToMiddle << ", they now have " << moneySign << users[userInput].getMoney() << "." << endl;
    }
    cout << "The middle now has " << moneySign << middleVal << "." << endl;

    return enoughToPay;
}

void Board::goToJail(int userInput){ //Sends the user to jail.
    users[userInput].setSpace(10);
    users[userInput].setInJail(true);
    cout << users[userInput].getUsername() << " has been sent directly to jail! " << users[userInput].getUsername() << " cannot leave unless one of the following occurs:" << endl;
    cout << "1) They throw doubles on any of the next 3 turns. Succeeding in doing so moves them forward the number of spaces" << endl;
    cout << "shown by their throw. Even though they threw doubles, they do NOT take another turn." << endl;
    cout << "2) Using a 'Get Out of Jail Free' card if they have one (" << users[userInput].getUsername() << " has " << users[userInput].getGetOutOfJail() << ")." << endl;
    cout << "3) Paying a fine of " << moneySign << "50 before they roll the dice on either of their next two turns." << endl;
    cout << "If they don't throw doubles by their third turn, they MUST pay the " << moneySign << "50 fine. They then get out of Jail" << endl;
    cout << "and immediately move forward the number of spaces shown by their throw." << endl;
}

bool Board::checkMonopoly(string colorInput){
    int initOwner = -2;
    for(int i = 0; i < 40; i++){ //Loop through every property
        if(props[i].getColor() == colorInput){
            if(initOwner == -2){ //Set the initOwner to the owner in first property in the color group it comes across
                initOwner = props[i].getOwner();
            }
            else{ //If it isn't the first property it's come across
                if(props[i].getOwner() != initOwner){ //Check if the properties' owner is NOT the same as the initial
                    return false;
                }
            }
        }
    }
    return true; //Return true if it passed the test
}

bool Board::saveBankruptcy(int userInput, int amtOwed){ //Tries to save bankruptcy by selling houses and mortgaging properties
    string inputChoice = ""; //Initialize input variable
    bool mortgage = true;
    bool installments = true;

    if(users[userInput].getIsReal() == true){ //If the user is real
        while(mortgage == true && installments == true){
            cout << "You do not have enough money to pay and not be bankrupt! Would you like to mortgage property or sell installments?" << endl;
            cout << "1. Mortgage property" << endl;
            cout << "2. Sell " << housePName << "/" << hotelPName << endl;
            cin >> inputChoice;

            while(inputChoice != "1" && inputChoice != "2"){ //Input validation
                cout << "Please enter a number between 1 and 2." << endl;
                cin >> inputChoice;
            }

            if(inputChoice == "1"){ //If they want to mortgage property
                mortgage = mortgageProperty(userInput);
            }
            else{ // If they want to sell houses
                installments = sellHouses(userInput, amtOwed);
            }
        }

        while(mortgage == true && installments == false){
            cout << "You do not have enough money to pay and not be bankrupt! You have to mortgage properties." << endl;
            mortgage = mortgageProperty(userInput);
        }
        if(mortgage == false && installments == false){
            return false;
        }
        else{
            return true;
        }
    }
    else{ //If the user isn't real
        while(mortgage == true && installments == true){ //Sell all the houses they need to
            installments = sellHouses(userInput, amtOwed);
        }

        while(mortgage == true && installments == false && users[userInput].getMoney() < amtOwed){ //Mortgage until they have enough money
            mortgage = mortgageProperty(userInput);
        }

        if(mortgage == false && installments == false){ //If after doing both they still don't have enough
            return false;
        }
        else{ //If it was successful
            return true;
        }
    }
}

void Board::setCorrectRents(){ //Sets the correct rents based on how many houses are on each property
    for(int i = 0; i < 40; i++){ //Loops through each property and sets the correct rent amounts
        if(props[i].getIfMonopolized() == true && props[i].getNumHouses() == 0 && props[i].getNumHotels() == 0){ //If it is monopolized but has no installments
            props[i].setCurrentRent(props[i].getRentInit() * 2);
        }
        else if(props[i].getIfMonopolized() == false){ //If it isn't monopolized
            props[i].setCurrentRent(props[i].getRentInit());
        }
        else if(props[i].getNumHouses() == 1){ //If it has 1 house
            props[i].setCurrentRent(props[i].getRent1());
        }
        else if(props[i].getNumHouses() == 2){ //If it has 2 houses
            props[i].setCurrentRent(props[i].getRent2());
        }
        else if(props[i].getNumHouses() == 3){ //If it has 3 houses
            props[i].setCurrentRent(props[i].getRent3());
        }
        else if(props[i].getNumHouses() == 4){ //If it has 4 houses
            props[i].setCurrentRent(props[i].getRent4());
        }
        else if(props[i].getNumHotels() == 1){ //If it has a hotel
            props[i].setCurrentRent(props[i].getRentHotel());
        }
    }
}

void Board::bankruptcy(int bankruptUser, int userOwed){ //If a player goes bankrupt, this function is run
    int loanOwed = 0;
    cout << "Oh no! " << users[bankruptUser].getUsername() << " has gone bankrupt! All of their money and properties go to " << users[userOwed].getUsername() << "." << endl;
    if(users[bankruptUser].getIsReal() == true){
        return;
    }

    users[userOwed].setMoney(users[userOwed].getMoney() + users[bankruptUser].getMoney());
    cout << "*" << users[userOwed].getUsername() << " has received " << moneySign << users[bankruptUser].getMoney() << "." << endl;
    for(int i = 0; i < 40; i++){
        if(props[i].getOwner() == bankruptUser){
            props[i].setOwner(userOwed);
            cout << "*" << users[userOwed].getUsername() << " has received " << props[i].getName() << "." << endl;
            loanOwed = loanOwed + (props[i].getMortgageValue() / 10);
            if(checkMonopoly(props[i].getColor()) == true){
                cout << users[userOwed].getUsername() << " now has a monopoly on " << props[i].getColor() << " properties!" << endl;
            }
        }
    }

    cout << users[userOwed].getUsername() << " owes a loan of " << moneySign << loanOwed << " on their new properties." << endl;
    users[userOwed].setMoney(users[userOwed].getMoney() - loanOwed);
    cout << users[userOwed].getUsername() << " now has " << moneySign << users[userOwed].getMoney() << "." << endl;
    cout << "NOTE: These properties are still mortgaged, they can be unmortgaged at any desired time." << endl;

    users[bankruptUser].setIsBankrupt(true);
}

bool Board::getBankruptAt(int userInput){ //Gets whether the inputted user is bankrupt
    bool output = users[userInput].getIsBankrupt();
    return output;
}

int Board::getNumDoublesAt(int userInput){ //Gets the number of doubles for a current user (for jail)
    int numDubs = users[userInput].getNumDoubles();
    return numDubs;
}

void Board::setNumDoublesAt(int userInput, int numDubs){ //Sets the number of doubles for a current user (for jail)
    users[userInput].setNumDoubles(numDubs);
}

bool Board::getInJailAt(int userInput){ //Gets whether a user is in jail
    bool userInJail = users[userInput].getInJail();
    return userInJail;
}

void Board::setInJailAt(int userInput, bool isInJail){ //Sets whether a user is in jail
    users[userInput].setInJail(isInJail);
}

string Board::getUsernameAt(int userInput){ //Gets the username at a specified index
    return users[userInput].getUsername();
}

void Board::setSpaceAt(int userInput, int spaceInput){ //Sets the user's space
    users[userInput].setSpace(spaceInput);
}

int Board::getSpaceAt(int userInput){ //Gets the user's space
    return users[userInput].getSpace();
}

string Board::getPropNameAt(int spaceInput){ //Gets space name at inputted space
    return props[spaceInput].getName();
}

bool Board::inJailNotDoubles(int userInput, bool byChoice){ //Action for if a user tried doubles roll for the third time and failed
    string choice = "";
    bool canAfford = true;

    if(users[userInput].getGetOutOfJail() > 0){ //If they have any get out of jail cards
        useGetOut(userInput);
        return true;
    }
    else{
        if(byChoice == true){ //If it was by choice
            if(users[userInput].getMoney() < 50 && users[userInput].getIsReal() == true){
                cout << "ERROR: You do not have any Get Out of Jail Free Cards OR enough money to do this." << endl;
            }
            else if(users[userInput].getIsReal() == true){
                cout << "You will be charged " << moneySign << "50 to get out of jail. Are you sure you want to do this (y/n)?" << endl;
                cin >> choice;
                while(choice != "Y" && choice != "y" && choice != "n" && choice != "N"){
                    cout << "Please enter y or n." << endl;
                    cin >> choice;
                }

                if(choice == "y" || choice == "Y"){
                    middleVal = middleVal + 50;
                    users[userInput].setMoney(users[userInput].getMoney() - 50);
                    users[userInput].setNumDoubles(0);
                    users[userInput].setInJail(false);
                    cout << "You have been charged " << moneySign << "50." << endl;
                    return true;
                }
                else{
                    return false;
                }
            }
            return false;
        }
        else{
            if(users[userInput].getIsReal() == true){
                cout << "You do not have any Get Out of Jail Free Cards. You currently have " << moneySign << users[userInput].getMoney() << ". You will be charged " << moneySign << "50." << endl;
            }
            else{
                cout << users[userInput].getUsername() << " does not have any Get Out of Jail Free Cards. They currently have " << moneySign << users[userInput].getMoney() << ". They will be charged " << moneySign << "50." << endl;
            }

            if(users[userInput].getMoney() < 50){
                canAfford = saveBankruptcy(userInput, 50);
            }

            if(canAfford == false){
                return false;
            }
            else{
                middleVal = middleVal + 50;
                users[userInput].setMoney(users[userInput].getMoney() - 50);
                users[userInput].setNumDoubles(0);
                users[userInput].setInJail(false);
                return true;
            }
        }
    }
}

void Board::useGetOut(int userInput){ //Uses a get out of jail card
    users[userInput].setGetOutOfJail(users[userInput].getGetOutOfJail() - 1);
    if(chance[6].getAccessed() == true){
        chance[6].setAccessed(false);
    }
    else{
        community[6].setAccessed(false);
    }
    if(users[userInput].getIsReal() == true){
        cout << "One of your Get Out of Jail Free cards has been used. You will now move forward the amount on your dice." << endl;
    }
    else{
        cout << users[userInput].getUsername() << " has used a Get Out of Jail Free card." << endl;
    }
}

// bool makeTrade(int userInput){
//   string tradeInput;
//   bool validInput = false;
//   cout << "What would you like to offer?" << endl;
//   cout << "1. Money" << endl;
//   cout << "2. Property" << endl;
//   cout << "3. Get Out of Jail Free Cards" << endl;
//   cout << "4. Return to main menu" << endl;
//   while(tradeInput.length() != 1 || tradeInput[0] < 49 || tradeInput[0] > 52){ //Input validation
//       cout << "Please enter a number between 1 and 4." << endl;
//       cin >> propChoice;
//   }
//   else{
//     cout << "3. Return to main menu" << endl;
//     while(tradeInput.length() != 1 || tradeInput[0] < 49 || tradeInput[0] > 51){ //Input validation
//         cout << "Please enter a number between 1 and 3." << endl;
//         cin >> tradeInput;
//     }
//   }
// 
//   if(tradeInput == "3")
//
// } //Makes a trade. Asks the user what property/money amount they want to trade for what properties/money with what user. Calculates a sum value of everything being traded
//and determines whether this trade would be acceptable for the CPU. If not, return false. If so, make the trade by changing necessary variables.
