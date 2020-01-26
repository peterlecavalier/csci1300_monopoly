// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Card.h

#include <iostream>
using namespace std;

#ifndef CARD_H
#define CARD_H

class Card{
    private:
        bool isAccessed; //Whether the card has been read or not
        string description; //Description on card
        int cardType; //pay, receive, pay players, receive from players, move spaces, go to jail, move spaces AND do something special, get out of jail free card, repair damages
        int value; //value for paying/receiving OR space to move to
    public:
        Card(); // Default
        Card(bool isAcc, string desc, int type, int val); // Parameterized
        void setAccessed(bool accessedInput); //sets whether that card has been accessed since the last “shuffle”
        bool getAccessed(); //gets whether that card has been accessed since the last “shuffle”
        void setAllInitVals(int versionInput, int index, string fileName); //Int inputs are the version number, index in array, and fileName. Sets the string description, card type, and value (from .txt)
        string getDescription(); //Get the string description of the card
        int getCardType(); //Card type getter
        int getValue(); //Gets the value for the card
};
#endif