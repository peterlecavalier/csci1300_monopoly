// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - User.cpp

#include <iostream>
#include <string>
#include "User.h"
using namespace std;

User::User(){ // Default
    username = "";
    money = 1500;
    numGetOutOfJail = 0;
    space = 0;
    numUtil = 0;
    numRail = 0;
    isReal = false;
    numDoubles = 0;
    inJail = false;
}

User::User(string uName, int monVal, int jailCard, int spaceVal, int numUt, int numRa, bool isRe, int numDub, bool inJa, bool isBan){ // Parameterized
    username = uName;
    money = monVal;
    numGetOutOfJail = jailCard;
    space = spaceVal;
    numUtil = numUt;
    numRail = numRa;
    isReal = isRe;
    numDoubles = numDub;
    inJail = inJa;
    isBankrupt = isBan;
}

void User::setUsername(string userInput){ //username setter
    username = userInput;
}

string User::getUsername(){ //username getter
    return username;
}

void User::setMoney(int moneyInput){ //money amount setter
    money = moneyInput;
}

int User::getMoney(){ //money amount getter
    return money;
}

void User::setGetOutOfJail(int jailInput){ //set amount of get out of jail free cards
    numGetOutOfJail = jailInput;
}

int User::getGetOutOfJail(){ //get out of jail free card getter
    return numGetOutOfJail;
}

void User::setSpace(int spaceInput){ //Set the current space the user is on the board
    space = spaceInput;
}

int User::getSpace(){ //Get the current space the user is on on the board
    return space;
}

void User::setNumUtil(int utilInput){ //Sets the number of utilities the user has
    numUtil = utilInput;
}

int User::getNumUtil(){ //Gets the number of utilities the user has
    return numUtil;
}

void User::setNumRail(int railInput){ //Sets the number of railroads the user has
    numRail = railInput;
}

int User::getNumRail(){ //Gets the number of railroads the user has
    return numRail;
}

void User::setIsReal(bool realInput){ //sets whether the user is real or a cpu
    isReal = realInput;
}

bool User::getIsReal(){ //gets whether the user is real or a cpu
    return isReal;
}

void User::setNumDoubles(int doublesInput){ // numDoubles setter
    numDoubles = doublesInput;
}

int User::getNumDoubles(){ // numDoubles getter
    return numDoubles;
}

void User::setInJail(bool inJailInput){ //inJail setter
    inJail = inJailInput;
}

bool User::getInJail(){ //inJail getter
    return inJail;
}

void User::setIsBankrupt(bool bankruptInput){ //isBankrupt setter
    isBankrupt = bankruptInput;
}

bool User::getIsBankrupt(){ //isBankrupt getter
    return isBankrupt;
}