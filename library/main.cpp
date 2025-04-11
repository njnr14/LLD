#include<bits/stdc++.h>

using namespace std;


class User{
    public: 
    static int Uuid;
    int id;
    string name;

    User(string name):id(Uuid++) , name(name){}

};


int User::Uuid =1;


class Book{
    public: 
    static int Buid;
    int id;
    string title;
    string author;
    
    Book(string title , string author):id(Buid++) , title(title) , author(author){}
    void displayBook(){
        cout<<"Book id:"<<id<<endl;
        cout<<"Title:"<<title<<endl;
        cout<<"Book Author"<<author<<endl;
    }
    
};

int Book::Buid = 1;





class Library{
    public:
    unordered_map<int , shared_ptr<Book>> AllBook; // {bookId , book}
    unordered_map<int , bool> BookAvailabilty;
    unordered_map<string , vector<int>> AllAuthor; // {author , {books}}
    unordered_map<string , int> titleToBook; // {titles , {books}}
    unordered_map<int , pair<int,int>> BorrowedBook; // BookId , UserId , date


    void addBook(string BookTitle , string Author){
        shared_ptr<Book> b = make_shared<Book>(BookTitle,Author);
        AllBook[b->id] = b;
        BookAvailabilty[b->id] = true;
        AllAuthor[Author].push_back(b->id);
        titleToBook[BookTitle] = b->id;
    }

    void searchByTitle(string title){
        if(titleToBook.find(title)==titleToBook.end()){
            cout<<"Book not found\n";
            return;
        }
        shared_ptr<Book> b = AllBook[titleToBook[title]];
        b->displayBook();
        cout<<"currently Available :"<<BookAvailabilty[b->id];
    }

    void searchByAuthor(string Author){
        if(AllAuthor.find(Author)==AllAuthor.end()){
            cout<<"Author not found\n";
            return;
        }
        
        vector<int> AuthorBooks = AllAuthor[Author];
        for(auto it : AuthorBooks){
            shared_ptr<Book> b = AllBook[it];
            b->displayBook();
            cout<<"currently Available :"<<BookAvailabilty[b->id];
        }

        return;
    }

    void displayAllBooks(){
        for(auto it : AllBook){
            
            it.second->displayBook();
            cout<<"currently Available :"<<BookAvailabilty[it.first];
        }
    }


    bool BorrowBook(int BookId , shared_ptr<User> u , int date ){
        if(AllBook.find(BookId) == AllBook.end()){
            cout<<"book do not exist \n";
            return false;
        }

        if(!BookAvailabilty[BookId]){
            cout<<"Book not Available\n";
            return false;
        }

        BorrowedBook[BookId]  = {u->id , date};
        BookAvailabilty[BookId] = false;
        return true;

    }
    bool returnBook(int BookId , shared_ptr<User> u  ,int date){
        
        //check for extra fees


        if(BorrowedBook.find(BookId)==BorrowedBook.end()){
            cout<<"Book do not exist\n";
            return false;
        }
        if(BorrowedBook[BookId].second - date > 7 ){
            cout<<"You need to pay:"<<(BorrowedBook[BookId].second - date) *10<<endl;
        }
        BorrowedBook.erase(BookId);
        BookAvailabilty[BookId] = true;
        return true;

    }

};













int main(){

    shared_ptr<User> u = make_shared<User>("alan");

    shared_ptr<Library> lib = make_shared<Library>();

    lib->addBook("Game of thrones" , "George");
    lib->addBook("Harry Potter" , "Jk Rowling");
    lib->addBook("Game of thrones 2" , "George");


    // lib->displayAllBooks();
    lib->searchByTitle("Harry Potter");
    cout<<endl;
    lib->BorrowBook(2 , u , 1);
    lib->searchByTitle("Harry Potter");
    
    cout<<endl;
    lib->returnBook(2, u , 10);
    cout<<endl;
    
    lib->searchByTitle("Harry Potter");

    return 0;
}