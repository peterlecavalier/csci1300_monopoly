#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string username;
    int money;
    int numGetOutOfJail;
    int space;
    int numUtil;
    int numRail;
    bool isReal;
    int numDoubles;
    bool inJail;
    bool isBankrupt;

public:
    User(); // Default ructor
    User(string uName, int monVal, int jailCard, int spaceVal, int numUt, int numRa, bool isRe, int numDub, bool inJa, bool isBan);

    // Member function declarations
    void setUsername(string userInput);
    string getUsername();
    void setMoney(int moneyInput);
    int getMoney();
    void setGetOutOfJail(int jailInput);
    int getGetOutOfJail();
    void setSpace(int spaceInput);
    int getSpace();
    void setNumUtil(int utilInput);
    int getNumUtil();
    void setNumRail(int railInput);
    int getNumRail();
    void setIsReal(bool realInput);
    bool getIsReal();
    void setNumDoubles(int doublesInput);
    int getNumDoubles();
    void setInJail(bool inJailInput);
    bool getInJail();
    void setIsBankrupt(bool bankruptInput);
    bool getIsBankrupt();
};

#endif // USER_H