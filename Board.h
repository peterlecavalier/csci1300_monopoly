// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Board.h

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Property.h"
#include "Card.h"
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
        int versionInt; //Initialize all variables
        string versionName;
        int numUsers;
        string houseName;
        string hotelName;
        string housePName;
        string hotelPName;
        string moneyName;
        string chanceName;
        string commName;
        string railName;
        string moneySign;
        int middleVal;
        int turnNumber;
        vector <int> turnOrder;
        Property props[40]; //Initialize arrays from other classes
        Card chance[16];
        Card community[16];
        User users[4];
    public:
        Board(); // Default
        Board(int verInt, string verName, int numUs, string houseN, string hotelN, string housePN, string hotelPN, string moneyN, string chanceN, string commN, string railN, string monSign, int middle, int turnN); // Parameterized
        void setAllInitVals(int versionInput, string user0, string user1, string user2, string user3, vector <int> turnOrderInput); //sets the version number, version name, house name, hotel name, money name, chance name,  and community chest name (from .txt)

        //BASIC GETTERS AND SETTERS//
        int getVersion(); //gets the version of the game played as an int
        string getVersionName(); //gets the NAME of the version as a string
        void setNumUsers(int usersInput); //Sets the number of users in the game
        int getNumUsers(); //gets the number of users in the game
        string getHouseName(); //gets the name of a house for the version
        string getHotelName(); //gets the name of a hotel for the version
        string getHousePName(); //gets the name of plural houses for the version
        string getHotelPName(); //gets the name of plural hotels for the version
        string getMoneyName(); //gets the name of money for the version
        string getChanceName(); //gets the name of a chance card for the version
        string getCommName(); //gets the name of a community chest card for the version
        string getRailName(); //gets the name of a railroad for the version
        void setMiddle(int midVal); //sets the amount of money in the middle
        int getMiddle(); //gets the amount of money in the middle
        void setTurnNum(int turnInput); //Sets the turn number
        int getTurnNum(); //Gets the turn number
        void setTurnOrder(vector <int> turnOrderInput); //Sets the turn order
        vector <int> getTurnOrder(); //Gets the turn order vector

        //NESTED GETTERS AND SETTERS//
        bool getBankruptAt(int userInput); //Gets whether the inputted user is bankrupt
        int getNumDoublesAt(int userInput); //Gets the number of doubles for a current user (for jail)
        void setNumDoublesAt(int userInput, int numDubs); //Sets the number of doubles for a current user (for jail)
        bool getInJailAt(int userInput); //Gets whether a user is in jail
        void setInJailAt(int userInput, bool isInJail); //Sets whether a user is in jail
        string getUsernameAt(int userInput); //Gets the username at a specified index
        void setSpaceAt(int userInput, int spaceInput); //Sets the user's space
        int getSpaceAt(int userInput); //Gets the user's space
        string getPropNameAt(int spaceInput); //Gets space name at inputted space

        //SPECIFIC ACTIONS//
        void shuffleCards(bool chanceOrComm); //Shuffles the cards by simply setting the access to false for all. Tests if the get out of jail free card has been accessed and keeps it that way.
        vector <int> printAllProps(int userInput, int returnType); //Prints all the properties that inputted user owns with respective house/hotel values. returnType determines whether it is returning mortgaged properties (0), unmortgaged properties (1), or nothing (2).
        void saveGame(); //Saves the game by writing all modified data to a .txt file.
        bool loadGame(); //Loads the game by reading from the .txt file, returning whether there was a file there or not.
        bool sellHouses(int userInput, int moneyNeeded); //Asks for user input on what house(s) they want to sell, then sells them back to the bank and gives back the correct value to the user.
        void buyHouses(int userInput); //Asks for user input on what house(s) they want to buy, then buys them from the bank and sets the correct number on the properties
        void allPropNames(); //Displays all the property names
        void viewSpace(int space); //View inputted space details
        bool drawCard(bool chanceOrComm, int userInput, int diceRoll); //Drawing a card from the deck, uses a random number generator to pick a random card, makes sure it hasn't been drawn yet. Returns false if the card requires payment and they can't pay.
        void viewBoard(); //Displays the board with lines and numbers, and displays what spaces each user is on.
        bool mortgageProperty(int userInput); //Mortgages property from the inputted user. Returns false if they CAN'T mortgage property, returns true if they can and choose not to/did mortgage.
        void unMortgageProperty(int userInput); //Unmortgages property from the inputted user.
        bool passedGoCheck(int newSpace, int userInput); //Checks whether the user passed go with the current action or not.
        bool landProperty(int spaceInput, int userInput); //Returns a boolean variable for true everytime EXCEPT if they land on a property, can't pay the rent AFTER selling houses/mortgaging.
        bool landRailroad(int spaceInput, int userInput, bool multiplier); //Does action for railroad space, multiplier is if from a card. Returns true everytime EXCEPT if they can't pay the rent
        bool landUtility(int spaceInput, int userInput, bool fromCard, int diceRoll); //Does action for utility space, does x10 no matter what if the boolean is true.
        void landFreeParking(int userInput); //Action for landing on free parking - user receives money from the middle and the middle value is reset to 100.
        bool landTax(int userInput, int spaceInput); //Action for landing on a tax space - returns true everytime EXCEPT if they can't pay the tax.
        void goToJail(int userInput); //Sends the user to jail.
        bool checkMonopoly(string colorInput); //Checks if a monopoly has been made, return true if this is the case.
        bool saveBankruptcy(int userInput, int amtOwed); //Tries to save bankruptcy by selling houses and mortgaging properties. Returns false if their bankruptcy couldn't be saved.
        void setCorrectRents(); //Sets the correct rents based on how many houses are on each property
        void bankruptcy(int bankruptUser, int userOwed); //If a player goes bankrupt, this function is run
        bool inJailNotDoubles(int userInput, bool byChoice); //Action for if a user tried doubles roll for the third time and failed
        void useGetOut(int userInput); //Uses a get out of jail card
        //bool makeTrade(int userInput); //Makes a trade. Asks the user what property/money amount they want to trade for what properties/money with what user. Calculates a sum value of everything being traded
        //and determines whether this trade would be acceptable for the CPU. If not, return false. If so, make the trade by changing necessary variables.
};
#endif
