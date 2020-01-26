// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - monopolyDriver.cpp

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include "Board.h"
#include "User.h"
#include "Property.h"
#include "Card.h"
using namespace std;

int rollDie(){ //Rolls a die
	return rand() % 6 + 1;
}

int menu(bool inJail){ //Menu for each turns' selection
    string menuChoice = "";
    int finalChoice = 0;
    bool goodChoice = true;
    if(inJail == false){ //If they aren't in jail
        cout << "What would you like to do?" << endl;
        cout << "1. View board/User information" << endl;
        cout << "2. View space information" << endl;
        cout << "3. View all of a user's properties" << endl;
        cout << "4. Buy houses/hotels" << endl;
        cout << "5. Sell houses/hotels" << endl;
        cout << "6. Mortgage/Unmortgage a property" << endl;
        cout << "7. Roll the dice" << endl;
        cout << "8. Save the game" << endl;
        cout << "9. Quit" << endl;
        cout << "--Enter your number option below--" << endl;
        while(menuChoice == ""){ //Input verification
            cin >> menuChoice;
            if(menuChoice.length() != 1 || menuChoice[0] < 49 || menuChoice[0] > 57){ //
                cout << "Please enter a number between 1 and 9." << endl;
                menuChoice = "";
            }
        }
    }
    else{ //If they are in jail
        cout << "What would you like to do?" << endl;
        cout << "1. View board/user information" << endl;
        cout << "2. View space information" << endl;
        cout << "3. View all of a user's properties" << endl;
        cout << "4. Buy houses/hotels" << endl;
        cout << "5. Sell houses/hotels" << endl;
        cout << "6. Mortgage/Unmortgage a property" << endl;
        cout << "7. Roll the dice" << endl;
        cout << "8. Pay/Use card to get out of jail" << endl;
        cout << "9. Save the game" << endl;
        cout << "10. Quit" << endl;
        cout << "--Enter your number option below--" << endl;
        cin >> menuChoice;
        for(int i = 0; i < menuChoice.length(); i++){ //Loop through to make sure it's a numerical input
            if(menuChoice[i] < 48 || menuChoice[i] > 57){
                goodChoice = false;
                break;
            }
        }
        if(goodChoice == true){
            if(stoi(menuChoice) < 1 || stoi(menuChoice) > 10){
                goodChoice = false;
            }
        }
        while(goodChoice == false){
            goodChoice = true;
            cout << "Please enter a number between 1 and 10" << endl;
            cin >> menuChoice;
            for(int i = 0; i < menuChoice.length(); i++){ //Loop through to make sure it's a numerical input
                if(menuChoice[i] < 48 || menuChoice[i] > 57){
                    goodChoice = false;
                    break;
                }
            }
            if(goodChoice == true){
                if(stoi(menuChoice) < 1 || stoi(menuChoice) > 10){
                    goodChoice = false;
                }
            }
        }
    }

    finalChoice = stoi(menuChoice); //Convert the string input to an integer
    return finalChoice; //Return the integer
}


int main(){
    int time_int = time(NULL); //Set the random number seed for the game based on the current time
    srand(time_int);

    int choice = 0; //Variables for user's turn
    string inChoice = "";
    bool goodInChoice = true;
    bool loadedGame = false;
    bool welcomeInputBool = false;
    string welcomeInput;
    int numVersion = 0;
    int numOfUsers = 0;
    string user0Name = "";
    string user1Name = "";
    string user2Name = "";
    string user3Name = "";
    bool user0select = false;
    bool user1select = false;
    bool user2select = false;
    bool user3select = false;
    int currentSelectedUser = 0;
    bool selectUserBool = true;
    string continueInput = "";
    bool gameIsOver = false;
    int roll1 = 0;
    int roll2 = 0;
    int totalRoll = 0;
    int currentNumDoubles = 0;
    int currentUserSpace = 0;
    bool canCurrentlyAfford = true;
    bool repeatTurn = true;
    string stoiChar = "";
    int turnInt = 0;
    bool jailReturn = false;

    Board gameBoard; //Initialize the entire board object

    vector <int> turnOrder; //Turn order. For example, if the order is user 1, user 3, user 4, user 2, string will be "1342".
    int whoseTurnIndex = 0;//Whose turn it is as an index of the user's turn in the string turnOrder (ex. user 4 would be 2 in above example).
    int whoseTurn = 0; //Whose turn it is (actual user number)

    cout << "                                                           WELCOME TO" << endl << endl;
    cout << " /$$      /$$        /$$$$$$        /$$   /$$        /$$$$$$        /$$$$$$$         /$$$$$$        /$$             /$$     /$$" << endl;
    cout << "| $$$    /$$$       /$$__  $$      | $$$ | $$       /$$__  $$      | $$__  $$       /$$__  $$      | $$            |  $$   /$$/" << endl;
    cout << "| $$$$  /$$$$      | $$  \\ $$      | $$$$| $$      | $$  \\ $$      | $$  \\ $$      | $$  \\ $$      | $$             \\  $$ /$$/" << endl;
    cout << "| $$ $$/$$ $$      | $$  | $$      | $$ $$ $$      | $$  | $$      | $$$$$$$/      | $$  | $$      | $$              \\  $$$$/" << endl;
    cout << "| $$  $$$| $$      | $$  | $$      | $$  $$$$      | $$  | $$      | $$____/       | $$  | $$      | $$               \\  $$/" << endl;
    cout << "| $$\\  $ | $$      | $$  | $$      | $$\\  $$$      | $$  | $$      | $$            | $$  | $$      | $$                | $$" << endl;
    cout << "| $$ \\/  | $$      |  $$$$$$/      | $$ \\  $$      |  $$$$$$/      | $$            |  $$$$$$/      | $$$$$$$$          | $$" << endl;
    cout << "|__/     |__/       \\______/       |__/  \\__/       \\______/       |__/             \\______/       |________/          |__/" << endl << endl;
    cout << "Enter anything to continue." << endl;
    cin >> continueInput;
    cout << endl;

    loadedGame = gameBoard.loadGame(); //Checks if a game has been loaded

    if(loadedGame == false){ //If not, run this
        cout << endl << "Which version of the game do you want to play?" << endl;
        cout << "1 - Original Monopoly" << endl;
        cout << "2 - Pokemon Monopoly" << endl;
        cout << "3 - Disney Pixar Monopoly" << endl;
        cout << "4 - Rick and Morty Monopoly" << endl;
        cout << "5 - The Office Monopoly" << endl;
        while(welcomeInputBool == false){
            cout << "Please enter a number between 1 and 5:" << endl;
            cin >> welcomeInput;
            if(welcomeInput == "1" || welcomeInput == "2" || welcomeInput == "3" || welcomeInput == "4" || welcomeInput == "5"){
                welcomeInputBool = true;
            }
        }
        numVersion = stoi(welcomeInput);
        welcomeInputBool = false;

        cout << endl << "How many CPU's do you want to play against?" << endl;
        while(welcomeInputBool == false){
            cout << "Please enter a number between 1 and 3:" << endl;
            cin >> welcomeInput;
            if(welcomeInput == "1" || welcomeInput == "2" || welcomeInput == "3"){
                welcomeInputBool = true;
            }
        }
        numOfUsers = stoi(welcomeInput) + 1;

        cout << endl << "What is your name?" << endl;
        getline(cin, user0Name); //GETLINE IS USED INSTEAD OF CIN TO ALLOW WHITESPACE
        for(int i = 0; i < user0Name.length(); i++){
            if(user0Name[i] == '/'){
                user0Name = "";
                break;
            }
        }
        while(user0Name == ""){
            cout << "Please enter a name (you can't have an empty name OR contain a '/'!)" << endl;
            getline(cin, user0Name);
            for(int i = 0; i < user0Name.length(); i++){
                if(user0Name[i] == '/'){
                    user0Name = "";
                    break;
                }
            }
        }

        cout << endl << "Let's name the CPUs!" << endl;
        for(int i = 1; i < numOfUsers; i++){ //Name the CPUs
            cout << "What is the name of CPU " << i << "?" << endl;
            if(i == 1){
                getline(cin, user1Name);
                for(int i = 0; i < user1Name.length(); i++){
                    if(user1Name[i] == '/'){
                        user1Name = "";
                        break;
                    }
                }
                while(user1Name == ""){
                    cout << "Please re-enter the name (CPU 1 can't have an empty name OR contain a '/'!)" << endl;
                    getline(cin, user1Name);
                    for(int i = 0; i < user1Name.length(); i++){
                        if(user1Name[i] == '/'){
                            user1Name = "";
                            break;
                        }
                    }
                }
            }
            else if(i == 2){
                getline(cin, user2Name);
                for(int i = 0; i < user2Name.length(); i++){
                    if(user2Name[i] == '/'){
                        user2Name = "";
                        break;
                    }
                }
                while(user2Name == ""){
                    cout << "Please enter a name (CPU 2 can't have an empty name!)" << endl;
                    getline(cin, user2Name);
                    for(int i = 0; i < user2Name.length(); i++){
                        if(user2Name[i] == '/'){
                            user2Name = "";
                            break;
                        }
                    }
                }
            }
            else{
                getline(cin, user3Name);
                for(int i = 0; i < user3Name.length(); i++){
                    if(user3Name[i] == '/'){
                        user3Name = "";
                        break;
                    }
                }
                while(user3Name == ""){
                    cout << "Please enter a name (CPU 3 can't have an empty name!)" << endl;
                    getline(cin, user3Name);
                    for(int i = 0; i < user3Name.length(); i++){
                        if(user3Name[i] == '/'){
                            user3Name = "";
                            break;
                        }
                    }
                }
            }
            cout << endl;
        }

        cout << "Randomly generating user order now." << endl;
        cout << "User order is:";

        while(turnOrder.size() != numOfUsers){ //While the turnOrder string hasn't been fully populated
            currentSelectedUser = rand() % numOfUsers;
            for(int i = 0; i < turnOrder.size(); i++){
                if(turnOrder[i] == currentSelectedUser){
                    selectUserBool = false;
                    break;
                }
            }

            if(selectUserBool == true){
                cout << " --> ";
                if(currentSelectedUser == 0){
                    cout << user0Name;
                }
                else if(currentSelectedUser == 1){
                    cout << user1Name;
                }
                else if(currentSelectedUser == 2){
                    cout << user2Name;
                }
                else{
                    cout << user3Name;
                }
                turnOrder.push_back(currentSelectedUser);
            }
            selectUserBool = true;
        }
        cout << endl;
        cout << "-----------------------------------" << endl;

        gameBoard.setAllInitVals(numVersion, user0Name, user1Name, user2Name, user3Name, turnOrder);

        cout << "Welcome to " << gameBoard.getVersionName() << " Monopoly, " << user0Name << "!" << endl << endl;
    }
    else{ //If the game was loaded
        turnOrder = gameBoard.getTurnOrder();
        for(int i = 0; i < turnOrder.size(); i++){ //Sets the turn to the user
            if(turnOrder[i] == 0){
                whoseTurnIndex = i;
            }
        }
        user0Name = gameBoard.getUsernameAt(0);
        user1Name = gameBoard.getUsernameAt(1);
        user2Name = gameBoard.getUsernameAt(2);
        user3Name = gameBoard.getUsernameAt(3);
        numOfUsers = gameBoard.getNumUsers();
        cout << endl << "Welcome back to " << gameBoard.getVersionName() << " Monopoly, " << user0Name << "!" << endl << endl;
    }
    cout << "Enter anything to continue." << endl;
    cin >> continueInput;
    cout << "-----------------------------------" << endl;

    while(gameIsOver == false){ //While the game isn't over
        whoseTurn = turnOrder[whoseTurnIndex];
        if(jailReturn == false){
            cout << "It is now " << gameBoard.getUsernameAt(whoseTurn) << "'s turn." << endl;
        }
        choice = 0; //Reset the choice to 0.
        canCurrentlyAfford = true;
        roll1 = 0;
        roll2 = 0;
        totalRoll = 0;
        currentNumDoubles = 0;
        currentUserSpace = 0;
        repeatTurn = true;
        jailReturn = false;
        if(whoseTurn == 0){ //If the user is real
            if(gameBoard.getInJailAt(whoseTurn) == true){ //If they are in jail
                while(choice != 7 && choice != 10){ //If they didn't roll the dice or quit
                    choice = menu(true);

                    if(choice == 1){ //View board
                        gameBoard.viewBoard();
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 2){ //View space information
                        cout << endl;
                        gameBoard.allPropNames(); //View all the property names
                        cout << endl << "Which space would you like to view details of?" << endl;
                        cout << "--Enter a space number below--" << endl;
                        cin >> inChoice;
                        for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                            if(inChoice[i] < 48 || inChoice[i] > 57){
                                goodInChoice = false;
                                break;
                            }
                        }
                        if(goodInChoice == true){
                            if(stoi(inChoice) < 0 || stoi(inChoice) > 39){
                                goodInChoice = false;
                            }
                        }
                        while(goodInChoice == false){
                            goodInChoice = true;
                            cout << "Please enter a number between 0 and 39" << endl;
                            cin >> inChoice;
                            for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                                if(inChoice[i] < 48 || inChoice[i] > 57){
                                    goodInChoice = false;
                                    break;
                                }
                            }
                            if(goodInChoice == true){
                                if(stoi(inChoice) < 0 || stoi(inChoice) > 39){
                                    goodInChoice = false;
                                }
                            }
                        }
                        gameBoard.viewSpace(stoi(inChoice)); //View the entered space
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 3){ //View all of a user's properties
                        cout << endl << "Which user would you like to view the properties of?" << endl;
                        cout << "0 - " << user0Name << " (you)" << endl;
                        cout << "1 - " << user1Name << endl;
                        if(user2Name != ""){
                            cout << "2 - " << user2Name << endl;
                        }
                        if(user3Name != ""){
                            cout << "3 - " << user3Name << endl;
                        }

                        cin >> inChoice;
                        for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                            if(inChoice[i] < 48 || inChoice[i] > 57){
                                goodInChoice = false;
                                break;
                            }
                        }
                        if(goodInChoice == true){
                            if(stoi(inChoice) < 0 || stoi(inChoice) > (numOfUsers - 1)){
                                goodInChoice = false;
                            }
                        }
                        while(goodInChoice == false){
                            goodInChoice = true;
                            cout << "Please enter a number between 0 and " << (numOfUsers - 1) << endl;
                            cin >> inChoice;
                            for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                                if(inChoice[i] < 48 || inChoice[i] > 57){
                                    goodInChoice = false;
                                    break;
                                }
                            }
                            if(goodInChoice == true){
                                if(stoi(inChoice) < 0 || stoi(inChoice) > (numOfUsers - 1)){
                                    goodInChoice = false;
                                }
                            }
                        }
                        cout << endl;
                        gameBoard.printAllProps(stoi(inChoice), 2);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 4){ //Buy houses/hotels
                        cout << endl;
                        gameBoard.buyHouses(whoseTurn);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 5){ //Sell houses/hotels
                        cout << endl;
                        gameBoard.sellHouses(whoseTurn, 0);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 6){ //Mortgage/Unmortgage a property
                        cout << endl;
                        cout << "Would you like to mortgage or unmortgage property?" << endl;
                        cout << "1 - Mortgage property" << endl;
                        cout << "2 - Unmortgage property" << endl;
                        cin >> inChoice;
                        while(inChoice != "1" && inChoice != "2"){
                            cout << "Please enter 1 or 2." << endl;
                            cin >> inChoice;
                        }

                        if(inChoice == "1"){
                            gameBoard.mortgageProperty(whoseTurn);
                        }
                        else{
                            gameBoard.unMortgageProperty(whoseTurn);
                        }
                    }
                    else if(choice == 7){ //Roll the dice
                        cout << endl;
                        if(gameBoard.getNumDoublesAt(whoseTurn) == 0){
                            cout << "This is your first attempt for rolling out of jail." << endl;
                        }
                        else if(gameBoard.getNumDoublesAt(whoseTurn) == 1){
                            cout << "This is your second attempt for rolling out of jail." << endl;
                        }
                        else{
                            cout << "This is your final attempt for rolling out of jail." << endl;
                        }
                        roll1 = rollDie();
                        roll2 = rollDie();
                        totalRoll = roll1 + roll2;
                        cout << "You rolled a " << totalRoll << " (" << roll1 << " & " << roll2 << ")." << endl;
                        if(roll1 == roll2){ //If they rolled a double
                            gameBoard.setInJailAt(whoseTurn, false);
                            gameBoard.setNumDoublesAt(whoseTurn, 0);
                            cout << "You have rolled doubles! You are now out of jail!" << endl;
                            if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                                cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                            }
                            else{
                                cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                            }
                            currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                            if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                                canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                                canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                            }
                            else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                                canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                            }
                            else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                                canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                            }
                            else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                                canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                            }
                            else if(currentUserSpace == 20){ //Free parking
                                gameBoard.landFreeParking(whoseTurn);
                            }
                            else if(currentUserSpace == 30){ //Go to jail
                                gameBoard.goToJail(whoseTurn);
                            }
                            else{ //Any regular property
                                canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                            }
                        }
                        else{ //If they didn't roll a double
                            if(gameBoard.getNumDoublesAt(whoseTurn) == 2){
                                canCurrentlyAfford = gameBoard.inJailNotDoubles(whoseTurn, false);
                                if(canCurrentlyAfford == true){
                                    if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                                        cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                                        gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                                        gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                                    }
                                    else{
                                        cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                                        gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                                        gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                                    }
                                    currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                                    if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                                        canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                                    }
                                    else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                                        canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                                    }
                                    else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                                        canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                                    }
                                    else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                                        canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                                    }
                                    else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                                    }
                                    else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                                        canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                                    }
                                    else if(currentUserSpace == 20){ //Free parking
                                        gameBoard.landFreeParking(whoseTurn);
                                    }
                                    else if(currentUserSpace == 30){ //Go to jail
                                        gameBoard.goToJail(whoseTurn);
                                    }
                                    else{ //Any regular property
                                        canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                                    }
                                }
                            }
                            else{
                                cout << "Sorry, you did not roll doubles." << endl;
                                gameBoard.setNumDoublesAt(whoseTurn, (gameBoard.getNumDoublesAt(whoseTurn) + 1));
                            }
                        }

                        if(canCurrentlyAfford == false){ //If they couldn't afford at some point in their roll
                            gameIsOver = true;
                        }
                    }
                    else if(choice == 8){ //Try to get out of jail
                        cout << endl;
                        jailReturn = gameBoard.inJailNotDoubles(whoseTurn, true);
                        if(jailReturn == false){
                            cout << endl << "Enter anything to continue." << endl;
                            cin >> continueInput;
                            cout << "-----------------------------------" << endl;
                        }
                    }
                    else if(choice == 9){ //Save the game
                        gameBoard.saveGame();
                        cout << "The game has been successfuly saved." << endl;
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else{ //Quit
                        cout << "Would you like to save before quitting? (y/n)" << endl;
                        cin >> inChoice;
                        while(inChoice != "Y" && inChoice != "y" && inChoice != "N" && inChoice != "n"){
                            cout << "Please enter y or n" << endl;
                            cin >> inChoice;
                        }

                        if(inChoice == "Y" || inChoice == "y"){
                            gameBoard.saveGame();
                            cout << endl << "The game has been successfuly saved." << endl;
                        }

                        cout << "Goodbye!" << endl;
                        return 0;
                    }
                    if(jailReturn == true){
                        break;
                    }
                }
            }
            else{ //If they aren't in jail
                while(choice != 7 && choice != 9){ //If they didn't roll the dice or quit
                    if(choice == 11){ //If they're rolling again for doubles
                        choice = 7;
                    }
                    else{ //If they aren't rolling again for doubles
                        choice = menu(false);
                    }

                    if(choice == 1){ //View board
                        gameBoard.viewBoard();
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 2){ //View space information
                        cout << endl;
                        gameBoard.allPropNames(); //View all the property names
                        cout << endl << "Which space would you like to view details of?" << endl;
                        cout << "--Enter a space number below--" << endl;
                        cin >> inChoice;
                        for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                            if(inChoice[i] < 48 || inChoice[i] > 57){
                                goodInChoice = false;
                                break;
                            }
                        }
                        if(goodInChoice == true){
                            if(stoi(inChoice) < 0 || stoi(inChoice) > 39){
                                goodInChoice = false;
                            }
                        }
                        while(goodInChoice == false){
                            goodInChoice = true;
                            cout << "Please enter a number between 0 and 39" << endl;
                            cin >> inChoice;
                            for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                                if(inChoice[i] < 48 || inChoice[i] > 57){
                                    goodInChoice = false;
                                    break;
                                }
                            }
                            if(goodInChoice == true){
                                if(stoi(inChoice) < 0 || stoi(inChoice) > 39){
                                    goodInChoice = false;
                                }
                            }
                        }
                        gameBoard.viewSpace(stoi(inChoice)); //View the entered space
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 3){ //View all of a user's properties
                        cout << endl << "Which user would you like to view the properties of?" << endl;
                        cout << "0 - " << user0Name << " (you)" << endl;
                        cout << "1 - " << user1Name << endl;
                        if(user2Name != ""){
                            cout << "2 - " << user2Name << endl;
                        }
                        if(user3Name != ""){
                            cout << "3 - " << user3Name << endl;
                        }

                        cin >> inChoice;
                        for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                            if(inChoice[i] < 48 || inChoice[i] > 57){
                                goodInChoice = false;
                                break;
                            }
                        }
                        if(goodInChoice == true){
                            if(stoi(inChoice) < 0 || stoi(inChoice) > (numOfUsers - 1)){
                                goodInChoice = false;
                            }
                        }
                        while(goodInChoice == false){
                            goodInChoice = true;
                            cout << "Please enter a number between 0 and " << (numOfUsers - 1) << endl;
                            cin >> inChoice;
                            for(int i = 0; i < inChoice.length(); i++){ //Loop through to make sure it's a numerical input
                                if(inChoice[i] < 48 || inChoice[i] > 57){
                                    goodInChoice = false;
                                    break;
                                }
                            }
                            if(goodInChoice == true){
                                if(stoi(inChoice) < 0 || stoi(inChoice) > (numOfUsers - 1)){
                                    goodInChoice = false;
                                }
                            }
                        }
                        cout << endl;
                        gameBoard.printAllProps(stoi(inChoice), 2);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 4){ //Buy houses/hotels
                        cout << endl;
                        gameBoard.buyHouses(whoseTurn);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 5){ //Sell houses/hotels
                        cout << endl;
                        gameBoard.sellHouses(whoseTurn, 0);
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 6){ //Mortgage/Unmortgage a property
                        cout << endl;
                        cout << "Would you like to mortgage or unmortgage property?" << endl;
                        cout << "1 - Mortgage property" << endl;
                        cout << "2 - Unmortgage property" << endl;
                        cin >> inChoice;
                        while(inChoice != "1" && inChoice != "2"){
                            cout << "Please enter 1 or 2." << endl;
                            cin >> inChoice;
                        }

                        cout << endl;
                        if(inChoice == "1"){
                            gameBoard.mortgageProperty(whoseTurn);
                        }
                        else{
                            gameBoard.unMortgageProperty(whoseTurn);
                        }
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else if(choice == 7){ //Roll the dice
                        cout << endl;
                        roll1 = rollDie();
                        roll2 = rollDie();
                        totalRoll = roll1 + roll2;
                        cout << "You rolled a " << totalRoll << " (" << roll1 << " & " << roll2 << ")." << endl;
                        if(currentNumDoubles == 2 && roll1 == roll2){ //If this is their 3rd double
                            cout << "This is your third double in a row!" << endl;
                            gameBoard.goToJail(whoseTurn);
                        }
                        else{
                            if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                                cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                            }
                            else{
                                cout << "You landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                            }
                            currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                            if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                                canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                                canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                            }
                            else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                                canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                            }
                            else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                                canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                            }
                            else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                                canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                            }
                            else if(currentUserSpace == 20){ //Free parking
                                gameBoard.landFreeParking(whoseTurn);
                            }
                            else if(currentUserSpace == 30){ //Go to jail
                                gameBoard.goToJail(whoseTurn);
                            }
                            else{ //Any regular property
                                canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                            }
                        }

                        if(canCurrentlyAfford == false){ //If they couldn't afford at some point in their roll
                            gameIsOver = true;
                        }
                        else if(roll1 == roll2 && gameBoard.getInJailAt(whoseTurn) == false){ //If they rolled doubles
                            cout << "You rolled doubles this turn! You get to roll again." << endl;
                            choice = 11;
                        }
                    }
                    else if(choice == 8){ //Save the game
                        cout << endl;
                        gameBoard.saveGame();
                        cout << "The game has been successfuly saved." << endl;
                        cout << endl << "Enter anything to continue." << endl;
                        cin >> continueInput;
                        cout << "-----------------------------------" << endl;
                    }
                    else{ //Quit
                        cout << endl << "Would you like to save before quitting? (y/n)" << endl;
                        cin >> inChoice;
                        while(inChoice != "Y" && inChoice != "y" && inChoice != "N" && inChoice != "n"){
                            cout << "Please enter y or n" << endl;
                            cin >> inChoice;
                        }

                        if(inChoice == "Y" || inChoice == "y"){
                            gameBoard.saveGame();
                            cout << endl << "The game has been successfuly saved." << endl;
                        }

                        cout << endl << "Goodbye!" << endl;
                        return 0;
                    }
                }
            }
        }
        else{ //If the user is a CPU
            gameBoard.unMortgageProperty(whoseTurn); //Attempt to unmortgage/buy houses
            gameBoard.buyHouses(whoseTurn);

            if(gameBoard.getInJailAt(whoseTurn) == true){ //If they are in jail
                gameBoard.inJailNotDoubles(whoseTurn, true);

                if(gameBoard.getNumDoublesAt(whoseTurn) == 0){
                    cout << "This is " << gameBoard.getUsernameAt(whoseTurn) << "'s first attempt for rolling out of jail." << endl;
                }
                else if(gameBoard.getNumDoublesAt(whoseTurn) == 1){
                    cout << "This is " << gameBoard.getUsernameAt(whoseTurn) << "'s second attempt for rolling out of jail." << endl;
                }
                else{
                    cout << "This is " << gameBoard.getUsernameAt(whoseTurn) << "'s final attempt for rolling out of jail." << endl;
                }
                roll1 = rollDie();
                roll2 = rollDie();
                totalRoll = roll1 + roll2;
                cout << gameBoard.getUsernameAt(whoseTurn) << " rolled a " << totalRoll << " (" << roll1 << " & " << roll2 << ")." << endl;
                if(roll1 == roll2){ //If they rolled a double
                    cout << "They have rolled doubles! They are now out of jail!" << endl;
                    gameBoard.setInJailAt(whoseTurn, false);
                    gameBoard.setNumDoublesAt(whoseTurn, 0);
                    if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                        cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                        gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                        gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                    }
                    else{
                        cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                        gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                        gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                    }
                    currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                    if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                        canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                    }
                    else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                        canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                    }
                    else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                        canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                    }
                    else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                        canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                    }
                    else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                    }
                    else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                        canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                    }
                    else if(currentUserSpace == 20){ //Free parking
                        gameBoard.landFreeParking(whoseTurn);
                    }
                    else if(currentUserSpace == 30){ //Go to jail
                        gameBoard.goToJail(whoseTurn);
                    }
                    else{ //Any regular property
                        canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                    }
                }
                else{ //If they didn't roll a double
                    if(gameBoard.getNumDoublesAt(whoseTurn) == 2){
                        canCurrentlyAfford = gameBoard.inJailNotDoubles(whoseTurn, false);
                        if(canCurrentlyAfford == true){
                            if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                                cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                            }
                            else{
                                cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                                gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                                gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                            }
                            currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                            if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                                canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                                canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                            }
                            else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                                canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                            }
                            else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                                canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                            }
                            else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                            }
                            else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                                canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                            }
                            else if(currentUserSpace == 20){ //Free parking
                                gameBoard.landFreeParking(whoseTurn);
                            }
                            else if(currentUserSpace == 30){ //Go to jail
                                gameBoard.goToJail(whoseTurn);
                            }
                            else{ //Any regular property
                                canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                            }
                        }
                    }
                    else{
                        cout << gameBoard.getUsernameAt(whoseTurn) << " did not roll doubles." << endl;
                        gameBoard.setNumDoublesAt(whoseTurn, (gameBoard.getNumDoublesAt(whoseTurn) + 1));
                    }
                }
            }
            else{ //If they aren't in jail
                while(repeatTurn == true){
                    roll1 = rollDie();
                    roll2 = rollDie();
                    totalRoll = roll1 + roll2;
                    cout << gameBoard.getUsernameAt(whoseTurn) << " rolled a " << totalRoll << " (" << roll1 << " & " << roll2 << ")." << endl;
                    if(currentNumDoubles == 2 && roll1 == roll2){ //If this is their 3rd double
                        cout << "This is " << gameBoard.getUsernameAt(whoseTurn) << "'s third double in a row!" << endl;
                        gameBoard.goToJail(whoseTurn);
                    }
                    else{
                        if((gameBoard.getSpaceAt(whoseTurn) + totalRoll) >= 40){
                            cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40) << endl;
                            gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40), whoseTurn);
                            gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll - 40));
                        }
                        else{
                            cout << gameBoard.getUsernameAt(whoseTurn) << " landed on " << gameBoard.getPropNameAt(gameBoard.getSpaceAt(whoseTurn) + totalRoll) << endl;
                            gameBoard.passedGoCheck((gameBoard.getSpaceAt(whoseTurn) + totalRoll), whoseTurn);
                            gameBoard.setSpaceAt(whoseTurn, (gameBoard.getSpaceAt(whoseTurn) + totalRoll));
                        }
                        currentUserSpace = gameBoard.getSpaceAt(whoseTurn);
                        if(currentUserSpace == 2 || currentUserSpace == 17 || currentUserSpace == 33){ //If they landed on a community chest space
                            canCurrentlyAfford = gameBoard.drawCard(true, whoseTurn, totalRoll);
                        }
                        else if(currentUserSpace == 4 || currentUserSpace == 38){ //If they landed on a tax
                            canCurrentlyAfford = gameBoard.landTax(whoseTurn, currentUserSpace);
                        }
                        else if(currentUserSpace == 5 || currentUserSpace == 15 || currentUserSpace == 25 || currentUserSpace == 35){ //If they landed on a railroad
                            canCurrentlyAfford = gameBoard.landRailroad(currentUserSpace, whoseTurn, false);
                        }
                        else if(currentUserSpace == 7 || currentUserSpace == 22 || currentUserSpace == 36){ //Chance space
                            canCurrentlyAfford = gameBoard.drawCard(false, whoseTurn, totalRoll);
                        }
                        else if(currentUserSpace == 0 || currentUserSpace == 10){ //Visiting jail or go (nothing happens)

                        }
                        else if(currentUserSpace == 12 || currentUserSpace == 28){ //Utility
                            canCurrentlyAfford = gameBoard.landUtility(currentUserSpace, whoseTurn, false, totalRoll);
                        }
                        else if(currentUserSpace == 20){ //Free parking
                            gameBoard.landFreeParking(whoseTurn);
                        }
                        else if(currentUserSpace == 30){ //Go to jail
                            gameBoard.goToJail(whoseTurn);
                        }
                        else{ //Any regular property
                            canCurrentlyAfford = gameBoard.landProperty(currentUserSpace, whoseTurn);
                        }
                    }

                    if(roll1 == roll2 && gameBoard.getInJailAt(whoseTurn) == false){ //If they rolled doubles
                        cout << gameBoard.getUsernameAt(whoseTurn) << " rolled doubles this turn, they get to roll again." << endl << endl;
                        currentNumDoubles++;
                    }
                    else{
                        repeatTurn = false;
                    }
                }
            }
        }

        gameBoard.setCorrectRents();

        if(jailReturn == false){
            cout << endl << "Enter anything to continue." << endl;
            cin >> continueInput;

            if(whoseTurnIndex != (numOfUsers - 1)){ //If it isn't at the end of the turnOrder string
                whoseTurnIndex++;
            }
            else{
                whoseTurnIndex = 0;
                gameBoard.setTurnNum(gameBoard.getTurnNum() + 1);
            }
        }
        cout << "-----------------------------------" << endl;
    }
}
