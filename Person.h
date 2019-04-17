//
//  Person.h
//  assignment5-2
//
//  Created by Lee Yi Wei on 2019/4/9.
//  Copyright © 2019 Lee Yi Wei. All rights reserved.
//

#ifndef Person_h
#define Person_h
#include <string>
#include <vector>
using namespace std;

class Person
{
private:
    string firstName;
    string lastName;
    int    cardID;
    bool   active;
    
public:
    Person (int cardNo, bool act, string fName, string lName);
    string getFirstName();
    string getLastName();
    int    getId();
    void   setActive(bool act);
    bool   isActive();
    string fullName();
};

#endif /* Person_h */
