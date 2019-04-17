
// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Person.h"
#include "Book.h"
//#include "Person.cpp"
//#include "Book.cpp"
using namespace std;

void printMenu();
void readBook(vector<Book *> & myBooks);
int readPersons(vector<Person *> &myCardholders);
int checkbookid(vector<Book *> &myBooks,int bookId);
int findbookid(vector<Book *> &myBooks, int bookId);
int checkuserid(vector<Person *> &myCardholders, int cardid);
int finduserid(vector<Person *> &myCardholders, int cardId);
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders);
void bookcheckout(vector<Book *> & myBooks, vector<Person *> myCardholders);
void bookreturn(vector<Book *> & myBooks);
void availablebook(vector<Book *> & myBooks);
void outstandingrentals(vector<Book *> & myBooks);
void cardholderentals(vector<Book *> & myBooks, vector<Person *> myCardholders);
void opennewcard(vector<Person *> &myCardholders, int &newid);
void closecard(vector<Person *> &myCardholders);
void update(vector<Book *> & myBooks, vector<Person *> myCardholders);


void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}
void readBooks(vector<Book *> & myBooks)
{
    string title,author,category,noneed;
    int id;
    Book *b=nullptr;
    ifstream readbook;
    readbook.open("books.txt");
    
    while(readbook>>id)
    {
        getline(readbook,noneed);
        getline(readbook,title);
        getline(readbook,author);
        getline(readbook,category);
       b = new Book(id,title,author,category);
        myBooks.push_back(b);
    }
    b = nullptr;
    readbook.close();

}


int readPersons(vector<Person *> & myCardholders)
{
    int cardid;
    bool active;
    string firstname,lastname;
    Person *personPtr=nullptr;
    ifstream readperson;
    readperson.open("persons.txt");
    
    while(readperson>>cardid>>active>>firstname>>lastname)
    {
        personPtr = new Person(cardid,active,firstname,lastname);
        myCardholders.push_back(personPtr);
    }
    personPtr = nullptr;
    readperson.close();
    
    return cardid+1;
}

//check book id is aviliable
int checkbookid(vector<Book *> &myBooks,int bookId)
{
    int n = -1;
    for(int i=0;i<myBooks.size();i++)//把mybook的vector跑一遍 myBooks.size()是mybooks的數量
    {
        if(bookId == myBooks.at(i)->getId())
        {
            n=2;
            return n;
        }
    }
    return n;
}

//to find out the book id if aviliable then output the id's address
int findbookid(vector<Book *> &myBooks, int bookId)
{
    for(int i=0;i<myBooks.size();i++)
    {
        if(bookId==myBooks.at(i)->getId())
        {
            return i;
        }
    }
    return 0;
}

//check user id is aviliable
int checkuserid(vector<Person *> &myCardholders, int cardId)
{
    int n = -1, cardid = 0;
    for(int i=0;i<myCardholders.size();i++)
    {
        if(cardId==myCardholders.at(i)->getId())
        {
            return cardid = i;
        }
    }
    return n;
}

//to find out the user id if aviliable then output the id's address
int finduserid(vector<Person *> &myCardholders, int cardId)
{
    
    for(int i=0;i<myCardholders.size();i++)
    {
        if(cardId==myCardholders.at(i)->getId())
        {
            return cardId=i;
        }
    }
    return 2;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
    vector<int >vecbookid;
    vector<int >veccardid;
    Person *personPtr = nullptr;
    int bookid,userid,books,people;
    ifstream readRentalsfile;
    readRentalsfile.open("rentals.txt");
    while(readRentalsfile>>bookid>>userid)
    {
        vecbookid.push_back(bookid);
        veccardid.push_back(userid);
    }
    readRentalsfile.close();
    
    for(int i=0;i<vecbookid.size();i++)
    {
        bookid = vecbookid.at(i);
        userid = veccardid.at(i);
        //下面的不懂
        books = findbookid(myBooks, bookid);
        people = finduserid(myCardholders, userid);
        personPtr = myCardholders.at(people);
        myBooks.at(books)->setPersonPtr(personPtr);
        
    }
    personPtr =nullptr;
    
    return ;
}



void bookcheckout(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
    int userid,bookid,cardholder = 0 , bookvail = 0,books,users;
    string name;
    Person *personPtr=nullptr;
    
    //check is there any same user id
    cout<<"Please enter the card ID: ";
    cin>>userid;
    
    cardholder = checkuserid(myCardholders, userid);
    
    // if there is same user id then print out the name
    if(cardholder == -1 || myCardholders.at(cardholder)->isActive() == 0)
    {
        cout<<"Card ID not found"<<endl;
        return ;
    }
    
    else
    {
        //at(cardholder)--> 是因為cardholder是checkuserid時的數字
        cout<<"Cardholder: "<<myCardholders.at(cardholder)->fullName()<<endl;
        
    }
    cin.ignore();
    //check is there any same book id
    cout<<"Please enter the book ID: ";
    cin>>bookid;
    bookvail = checkbookid(myBooks, bookid);
    if(bookvail == -1)
    {
        cout<<"Book Id not found"<<endl;
    }

    
    else{
        for(int j=0;j<myBooks.size();j++)
        {
            //if the bookid at j is in getpersonPtr then print already check out
            if(bookid==myBooks.at(j)->getId() && myBooks.at(j)->getPersonPtr()!=NULL)
            {
                cout<<"Book already checked out"<<endl;
                return ;
            }
        }
        for(int i=0;i<myBooks.size();i++)
        {
            if(bookid==myBooks.at(i)->getId())
            {
                cout<<"Title: "<<myBooks.at(i)->getTitle()<<endl;
                //下面的不懂
                //find out this bookid and this card's userid
                books = findbookid(myBooks, bookid);
                users = finduserid(myCardholders, userid);
                //write this userid in personPtr
                //把personPtr換成myCardholders的也就是把這個換成userid的
                //所以接下來會把userid存進去personPtr嗎
                personPtr = myCardholders.at(users);
                //set this book's id into setpersonPtr??嗎？？
                //把借的人的id存進personPtr嗎
                myBooks.at(books)->setPersonPtr(personPtr);

            }
        }
        cout<<"Rental Completed";
    }

}

void bookreturn(vector<Book *> & myBooks)
{
    int bookid,vailed;
    Person *personPtr=NULL;
    cout<<"Please enter the book id to return: ";
    cin>>bookid;
    vailed = checkbookid(myBooks, bookid);
    if(vailed == -1)
    {
        cout<<"Book ID not found";
        return;
    }
    else{
        for(int i=0; i<myBooks.size();i++)
        {
            if(bookid == myBooks.at(i)->getId())
            {
                cout<<"Title: "<<myBooks.at(i)->getTitle()<<endl;
                //當mybooks在i的時候setpersonPtr
                myBooks.at(i)->setPersonPtr(personPtr);
            }
        }
    }
    cout<<"Return Completed";
}


void availablebook(vector<Book *> & myBooks)
{
    int book=0;
    for(int i=0;i<myBooks.size();i++)
    {
        if(myBooks.at(i)->getPersonPtr()==NULL)
        {
            cout<<"Book ID: "<<myBooks.at(i)->getId()<<endl;
            cout<<"Title: " <<myBooks.at(i)->getTitle()<<endl;
            cout<<"Author: " <<myBooks.at(i)->getAuthor()<<endl;
            cout<<"Category: "<<myBooks.at(i)->getCategory()<<endl;
            book++;
        }
    }
    if(book==0)
    {
        cout<<"No available books"<<endl;

    }
    
}
void outstandingrentals(vector<Book *> & myBooks)
{
    int books =0;
    for(int i=0;i<myBooks.size();i++)
    {
        if(myBooks.at(i)->getPersonPtr()!=NULL)
        {
            cout<<"Book ID: "<<myBooks.at(i)->getId()<<endl;
            cout<<"Title: " <<myBooks.at(i)->getTitle()<<endl;
            cout<<"Author: " <<myBooks.at(i)->getAuthor()<<endl;
            //mybooks read getpersonptr then read the fullname in the getpersonptr
            cout<<"Cardholder: " <<myBooks.at(i)->getPersonPtr()->fullName()<<endl;
            //mybooks read getpersonptr then read the cardid in the getpersonptr
            cout<<"Card ID: " <<myBooks.at(i)->getPersonPtr()->getId()<<endl;
            books++;
        }
    }
    if(books==0)
    {
        cout<<"No outstanding rentals"<<endl;

    }
}
void cardholderentals(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
    int userid, user,checkuser =0;
    cout<<"Please enter the card ID: ";
    cin>>userid;
    //
    user = checkuserid(myCardholders, userid);
    if(user == -1)
    {
        cout<<"Card ID not found"<<endl;
        return ;
    }
    else{
        //print the card holder when mycardholder in user then
        cout<<"Cardholder: "<<myCardholders.at(user)->fullName()<<endl;
        for(int i=0;i<myBooks.size();i++)
        {
            //if mybooks在i的時候getpersonPtr有point
            //和 當userid等於mybooks在i的時候getpersonPtr裡抓到的ID一樣時
            if(myBooks.at(i)->getPersonPtr() != NULL &&
               userid == myBooks.at(i)->getPersonPtr()->getId())
            {
                cout<<endl;
                cout<<"Book ID: "<<myBooks.at(i)->getId()<<endl;
                cout<<"Title: "<<myBooks.at(i)->getTitle()<<endl;
                cout<<"Author: "<<myBooks.at(i)->getAuthor()<<endl;
                checkuser++;
            }
        }
        if(checkuser == 0)
        {
            cout<<"No books currently checked out"<<endl;
        }
    }
    
    
}
void opennewcard(vector<Person *> &myCardholders, int &newid)
{
    string fname,lname;
    bool act =1;
    Person *personPtr = NULL;
    cout<<"Please enter the first name: ";
    cin>>fname;
    cout<<"Please enter the last name: ";
    cin>>lname;
    for(int i=0;i<myCardholders.size();i++)
    {
        if(fname == myCardholders.at(i)->getFirstName()
           && lname == myCardholders.at(i)->getLastName())
        {
            myCardholders.at(i)->setActive(act);
            cout<<"Card ID "<<myCardholders.at(i)->getId()<<" active"<<endl;
            cout<<"Cardholder: "<<myCardholders.at(i)->fullName()<<endl;
            return;
        }
    }
    personPtr = new Person(newid,act,fname,lname);
    myCardholders.push_back(personPtr);
    cout<<"Card ID "<<newid<<" active"<<endl;
    cout<<"Card holder: "<<myCardholders.back()->fullName()<<endl;
    personPtr =NULL;
    
}
void closecard(vector<Person *> &myCardholders)
{
    int cardid,findcard;
    char answer;
    // when the act equal "1" is active
    bool act=0;
    cout<<"Please enter the card ID: ";
    cin>>cardid;
    findcard = finduserid(myCardholders, cardid);
    for(int i=0;i<myCardholders.size();i++)
    {
        if(findcard == 2)
        {
            cout<<"Card ID not found"<<endl;
            return;
        }
        
    }
    //act equal '0' is mean the card is inactive
    //so when the act that find in when mycardholders is at findcard's id catch is it active
    //if act equal 0 then print out
    if(act == myCardholders.at(findcard)->isActive())
    {
        cout<<"Cardholder: "<<myCardholders.at(findcard)->fullName()<<endl;
        cout<<"Card ID is already inactive"<<endl;
    }
    //if act find in when mycardholder is at findcard'd id and catch the active is equal 1
    //then ask
    else{
        cout<<"Are you sure you want to deactivate card (y/n)? ";
        cin>>answer;
        if(answer =='y')
        {
            //setactive's act become '0'
            myCardholders.at(findcard)->setActive(act);
            cout<<"Card ID deactivated";
        }
    }
}

void update(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
    int bookid,userid;
    bool act;
    string fname,lname;
    ofstream newfile;
    //rewrite user>> mycardholders
    newfile.open("persons.txt");
    for(int i=0;i<myCardholders.size();i++)
    {
        userid = myCardholders.at(i)->getId();
        act = myCardholders.at(i)->isActive();
        fname = myCardholders.at(i)->getFirstName();
        lname = myCardholders.at(i)->getLastName();
        newfile<< userid << " "<< act<<" "<<fname<<" "<<lname<<endl;
    }
    newfile.close();
    //rewrite rentals>> mybooks
    newfile.open("rentals.txt");
    for(int j=0;j<myBooks.size();j++)
    {
        //if mybooks's getpersonPtr at j have some dates
        if(myBooks.at(j)->getPersonPtr() != NULL)
        {
            bookid = myBooks.at(j)->getId();
            userid = myBooks.at(j)->getPersonPtr()->getId();
            newfile<<bookid<<" "<<userid<<endl;
        }
    }
    newfile.close();
}

/*
 You are not obligated to use these function d
eclarations - they're just given as examples
 
 
 void openCard(vector<Person *> & myCardholders, int nextID) {
 return;
 }
 
 Book * searchBook(vector<Book *> myBooks, int id) {
 return nullptr;
 }
 */
int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int ID = 0;
    readBooks(books);
    ID = readPersons(cardholders);
    readRentals(books, cardholders);

    
    
     int choice;
     do
     {
     // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
     // the user pressed when entering a menu option. This is still in the input stream.
     printMenu();
     cin >> choice;
    
     switch(choice)
     {
     case 1:
     bookcheckout(books, cardholders);// Book checkout
     break;
     
     case 2:
     // Book return
    bookreturn(books);
     break;
     
     case 3:
     // View all available books
    availablebook(books);
     break;
     
     case 4:
     // View all outstanding rentals
    outstandingrentals(books);
     break;
    
     case 5:
     // View outstanding rentals for a cardholder
    cardholderentals(books, cardholders);
     break;
      
     case 6:
     // Open new library card
    opennewcard(cardholders,ID);
     break;
     
     case 7:
     // Close library card
             closecard(cardholders);
     break;
       
     case 8:
     // Must update records in files here before exiting the program
             update(books,cardholders);
     break;
     
     default:
     cout << "Invalid entry" << endl;
     break;
     }
     cout << endl;
     } while(choice != 8);
     
    return 0;
}


/*
 -load book.txt
 this file is tricky - cout after every read to quickly find bugs
 booksvectore -> book1 - book2 - book3 - book4
 
 -load persons.txt
 personsvector -> person1 - person2 - person3 - person4
 
 Do not store rentals in another data structure
 -read rentals.txt
 you have bookID and cardID for each current rental(like a database)
 -set the personptr in book object to point to the person who has the book
 EX
 
 Book18:          person9
 bookid=          cardid=
 personPtr----->  OBJECT
 title=
 author=
 categornt=
 
 isActive() is used to set the person's card open or closed
 don't use [] with vector, use at()
 
 -if I have myobjectPtr, I have 2 ways to access members:
 (*myObjectPtr).getName();
 myobjectPtr->getName();
 
 -Arrow operator only used with pointers
 */
