// CS1300 Spring 2019
// Author: Peter LeCavalier
// Recitation: 201 – Supriya Naidu
// Cloud9 Workspace Editor Link: https://ide.c9.io/pele6150/csci1300-peter
// Project 3 - Property.h

#include <iostream>
#include <string>
using namespace std;

#ifndef PROPERTY_H
#define PROPERTY_H

class Property{
    private:
        string propName; //Initialize all variables
        bool isOwnable;
        int rent_init;
        int rent1;
        int rent2;
        int rent3;
        int rent4;
        int rent_hotel;
        int mortValue;
        int houseCost;
        int propCost;
        string color;
        int currentRent;
        bool ifMort;
        int currentOwner;
        int numHouses;
        int numHotels;
        bool ifMonopolized;
    public:
        Property(); // Default
        Property(string pName, bool isOwn, int ri, int r1, int r2, int r3, int r4, int rh, int mVal, int hCost, int pCost, string col, int cRent, bool ifM, int currOwn, int nHouse, int nHotel, bool ifMon); // Parameterized
        void setAllInitVals(int versionInput, int index); //Sets the value of the property number, property name, isOwnable, all rent values, mortgage value, house cost, and property costs given the version number (from .txt)
        string getName(); //Gets the name of the property
        bool getIsOwnable(); //Gets whether the property is ownable or not
        int getRentInit(); //gets the initial rent
        int getRent1(); //gets the rent with one house
        int getRent2(); //gets the rent with two houses
        int getRent3(); //gets the rent with three houses
        int getRent4(); //gets the rent with four houses
        int getRentHotel(); //gets the rent with a hotel
        void setCurrentRent(int rentInput); //Sets the current rent of the property
        int getCurrentRent(); //Gets the current rent of the property
        int getHouseCost(); //Gets the cost of one house for the user
        int getMortgageValue(); //Gets the mortgage value of the property
        int getPropCost(); //Gets the property cost
        string getColor(); //Gets the color
        void setIfMortgaged(bool isMortgagedInput); //Sets whether the property is mortgaged
        bool getIfMortgaged(); //Gets whether the property is mortgaged
        void setOwner(int ownerInput); //Sets the current owner of the property
        int getOwner(); //Gets the value of the current owner of the property
        void setNumHouses(int housesInput); //number of houses setter
        int getNumHouses(); //number of houses getter
        void setNumHotels(int hotelsInput); //number of hotels setter
        int getNumHotels(); //number of hotels getter
        void setIfMonopolized(int monopInput); // Sets if the property is part of a monopoly
        bool getIfMonopolized(); // Gets if the property is part of a monopoly
};
#endif