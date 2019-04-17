//
//  Book.h
//  assignment5-2
//
//  Created by Lee Yi Wei on 2019/4/9.
//  Copyright © 2019 Lee Yi Wei. All rights reserved.
//

#ifndef Book_h
#define Book_h

#include <string>
#include "Person.h"
class Book
{
private:
    string   title;
    string   author;
    string   category;
    int      bookID;
    Person * personPtr = nullptr;
    
public:
    Book(int id, string bookName, string auth, string cat);
    string   getTitle();
    string   getAuthor();
    string   getCategory();
    int      getId();
    void     setPersonPtr(Person * ptr);
    Person * getPersonPtr();
};

#endif /* Book_h */
