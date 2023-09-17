#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class LibraryItem {

    private:
    string title;
    string authorname;
    string ISBN;
    int count;
    int identifier;

public:

    LibraryItem(){

    }

    LibraryItem(int &identifier, const string& title, const string& author, const string& ISBN, string &count){
        this->title = title;
        this->authorname = author ;
        this->ISBN = ISBN;
        this->count = stoi(count);
        this->identifier = identifier;
    }

   LibraryItem(int &identifier, const string& title){
        this->title = title;
        this->count = 1;
        this->identifier = identifier;
    }

     string get_title() {
        return title;
    }
     string get_authorname() {
        return authorname;
    }
     string get_ISBN() {
        return ISBN;
    }
    int get_identifier() {
        return identifier;
    }
    int get_count() {
        return count;
    }

    void set_count(int count){
        this->count = count;
    }

   virtual string get_type(){
        return "retunr the type of the Library Item:";
    }

    bool is_available() {
        if(count == 0 )
            return false;
        else
            return true;
    }

     int get_identifier() const {
        return identifier;
    }

    string get_details_Book() {
        return "->Count: "+ to_string(count) +"\n->Title: " + title + "\n->Author: "+authorname+"\n->ISBN: " + ISBN+ "\n\n";
    }

    string get_details_Publication() {
        return "->Title: "+title+"\n\n";
    }


    string get_details_Journal() {
        return "->Title: "+title+"\n\n";
    }
};


class Book : public LibraryItem {

    private:
    string title;
    string authorname;
    string ISBN;
    int count;
    int identifier;

public:

    Book(){

    }

    Book(int id, string title, string author, string ISBN, string count)
        : LibraryItem(id, title, author, ISBN, count) {}

    string get_type() override {
        return "Book";
    }

    string get_details_Book() {
        return LibraryItem::get_details_Book();
    }

};


class Publications : public LibraryItem {

public:
    Publications(){

        }

    Publications(int id, string title)
        : LibraryItem(id, title) {}

    string get_type() override {
        return "->Title: " + get_title();
    }

    string get_details_Publication(){
        return LibraryItem::get_details_Publication();
    }

};


class Journals : public LibraryItem {

    private:
    string title;
    int id;

public:
Journals(){

    }

    Journals(int id, string title)
        : LibraryItem(id, title) {}

    string get_type() override {
         return "->Title: " + get_title();
    }

    string get_details_Journal(){
        return LibraryItem::get_details_Journal();
    }
};


class User {

    private:
    string name;
    string user_type;
public:

    User(){
    }

    User(string name,string user_type){
        this->name = name;
        this->user_type = user_type ;
    }

    string get_name() const {
        return name;
    }

    string get_user_type() const {
        return user_type;
    }
};


class OtherBorrowing {

private:
    string InstituteName;
    string borrower;
    string dueDate;
    Book* item_1;
    Journals* item_2;
    Publications* item_3;

public:
    OtherBorrowing(Book* item,const string& InstituteName, string borrower, const string& dueDate){
        this->item_1=item;
        this->InstituteName = InstituteName ;
        this->borrower = borrower;
        this->dueDate = dueDate;
    }
     OtherBorrowing(Publications* item,const string& InstituteName, string borrower, const string& dueDate){
        this->item_3 = item;
        this->InstituteName = InstituteName ;
        this->borrower = borrower;
        this->dueDate = dueDate;
    }

    OtherBorrowing(Journals* item,const string& InstituteName, string borrower, const string& dueDate){
        this->item_2 = item;
        this->InstituteName = InstituteName ;
        this->borrower = borrower;
        this->dueDate = dueDate;
    }

    Book* getBook(){
        return item_1;
    }

    Publications* getPublication(){
        return item_3;
    }

    Journals* getJournal(){
        return item_2;
    }

    string getBorrower(){
        return borrower;
    }

    string getInstituteName(){
      return InstituteName;
    }

    string getBorowwerName(){
        return borrower;
    }

};

class Library {

private:
    vector<User*> users;
    string borrower;
    time_t borrow_date;

public:
    
    static string todaysdate() {
        time_t currentTime = time(0);
        struct tm* localTime = localtime(&currentTime);
        int year = localTime->tm_year + 1900; 
        int month = localTime->tm_mon + 1;   
        int day = localTime->tm_mday;
    return to_string(year) + "-"+ to_string(month) + "-" + to_string(day);
    }

 void register_user(const string& username, const string& user_type) {
        User* user = new User(username, user_type);
        users.push_back(user);
    }


    User* find_user(const string& username) {
        for (User* user : users) {
            if (user->get_name() == username) {
                return user;
            }
        }
        return nullptr;
    }

    void find_all_user() {
        for (User* user : users) {
            cout<<"User Name: "<<user->get_name()<<"\nUser Type: "<<user->get_user_type()<<endl;
        }
    }

    string find_books_by_title(string& title,  vector<Book*> data) {
        for( Book* bk : data){
            if(bk->get_title()==title){
                return "->Unique Identifier: "+to_string(bk->get_identifier())+"\n->Count: "+ to_string(bk->get_count()) +"\n->Title: " + title + "\n->Author: "+bk->get_authorname()+"\n->ISBN: " + bk->get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with the title: "+ title+"\n";
    }

     string find_books_by_Author(string& author,  vector<Book*> data) {
        for( Book* bk : data){
            if(bk->get_authorname()==author){
                return "->Unique Identifier:: "+to_string(bk->get_identifier())+"\n->Count: "+ to_string(bk->get_count()) +"\n->Title: " + bk->get_title() + "\n->Author: "+bk->get_authorname()+"\n->ISBN: " + bk->get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with the Author: "+ author+"\n";
    }

     string find_books_by_ISBN(string& ISBN,  vector<Book*> data) {
        for( Book* bk : data){
            if(bk->get_ISBN()==ISBN){
                return "->Unique Identifier: "+to_string(bk->get_identifier())+"\n->Count: "+ to_string(bk->get_count()) +"\n->Title: " + bk->get_title() + "\n->Author: "+bk->get_authorname()+"\n->ISBN: " + bk->get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with ISBN: "+ ISBN+"\n";
    }

     string find_publication_by_title(string& title,  vector<Publications*> data) {
        for( Publications* bk : data){
            if(bk->get_title()==title){
                return "->Unique Identifier: "+to_string(bk->get_identifier())+"\n->Count: "+ to_string(bk->get_count()) +"\n->Title: " + bk->get_title() + "\n\n";
            }
        }
        return "No Publications Found with the title: "+ title+"\n";
    }

     string find_journal_by_title(string& title,  vector<Journals*> data) {
        for( Journals* bk : data){
            if(bk->get_title()==title){
                return "->Unique Identifier: "+to_string(bk->get_identifier())+"\n->Count: "+ to_string(bk->get_count()) +"\n->Title: " + bk->get_title() + "\n\n";
            }
        }
        return "No Journals Found with title: "+ title+"\n";
    }

    string borrow_books_by_title(string& title,  vector<Book*> data, User* user){
         for( Book* bk : data){
            if(bk->get_title()==title){
                if(bk->get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    bk->set_count(bk->get_count()-1);
                    if(user->get_user_type()=="student"){
                      due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                      due_date = 6;
                    }else{
                        return " Not a valid User Type";
                    }
                    cout<<due_date<<endl;
                return "You have successfully borrowed '" + bk->get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                 }
             }
            //else{
            //     return "Sorry! the Item named as '" + bk->get_title()  + "' is already borrowed.";
            // }
    }
 return "Sorry! No Item was found.\n";
}


   string borrow_books_by_title(string& title,  OtherBorrowing* bk){
            if(bk->getBook()->get_title() == title){
                if(bk->getBook()->get_count()!=0){
                    borrower = bk->getBorrower();
                    borrow_date = time(0);
                    bk->getBook()->set_count(bk->getBook()->get_count()-1);
                return "You have successfully borrowed '" + bk->getBook()->get_title() + "'. and Due date is "+ to_string(1) + " months from "+todaysdate()+" with a delay of 7 days with below details: \n"+"->Unique Identifier: "+to_string(bk->getBook()->get_identifier())+"\n->Borrower: "+bk->getBorowwerName()+"\n->Lending Institute: "+bk->getInstituteName()+"\n";
                 }
            else{
                return "Sorry! the Item named as '" + bk->getBook()->get_title()  + "' is already borrowed.\n";
            }
        }
 return "Sorry! No Item was found.\n";
}

string borrow_books_by_Author(string& author,  vector<Book*> data, User* user){
         for( Book* bk : data){
            if(bk->get_authorname()==author){
                if(bk->get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    bk->set_count(bk->get_count()-1);
                    if(user->get_user_type()=="student"){
                         due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                         due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" + bk->get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                 }
            }
    }
    return "Sorry! No Item was found.\n";
}


string borrow_books_by_ISBN(string& isbn,  vector<Book*> data, User* user){
         for( Book* bk : data){
            if(bk->get_ISBN()==isbn){
                if(bk->get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    bk->set_count(bk->get_count()-1);
                    if(user->get_user_type()=="student"){
                       due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
               return "You have successfully borrowed '" + bk->get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                 }
            }
    }
    return "Sorry! No Item was found.\n";
}

string borrow_publication_by_title(string& title,  vector<Publications*> data, User* user){
         for( Publications* bk : data){
            if(bk->get_title()==title){
                if(bk->get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    bk->set_count(bk->get_count()-1);
                    if(user->get_user_type()=="student"){
                        due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 1;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" + bk->get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                }
            }
    }
     return "Sorry! No Item was found.\n";
}

string borrow_publication_by_title(string& title,  OtherBorrowing* bk){
        cout<<"title: "<<bk->getPublication()->get_title()<<"more: "<<title<<endl;
            if(bk->getPublication()->get_title() == title){
                cout<<"count: "<<bk->getPublication()->get_count()<<endl;
                if(bk->getPublication()->get_count()!=0){
                    borrower = bk->getBorrower();
                    borrow_date = time(0);
                    bk->getPublication()->set_count(bk->getPublication()->get_count()-1);
                return "You have successfully borrowed '" + bk->getPublication()->get_title() + "'. and Due date is "+ to_string(1) + " months from "+todaysdate()+" with a delay of 7 days with below details: \n"+"->Unique Identifier: "+to_string(bk->getPublication()->get_identifier())+"\n->Borrower: "+bk->getBorowwerName()+"\n->Lending Institute: "+bk->getInstituteName()+"\n";
                 }
            else{
                return "Sorry! the Item named as '" + bk->getPublication()->get_title()  + "' is already borrowed.\n";
            }
        }
         return "Sorry! No Item was found.\n";
}

string borrow_journal_by_title(string& title,  vector<Journals*> data, User* user){
         for( Journals* bk : data){
            if(bk->get_title()==title){
                if(bk->get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    bk->set_count(bk->get_count()-1);
                    if(user->get_user_type()=="student"){
                         due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" + bk->get_title() + "'.and Due date is "+ to_string(due_date) + " month/s from "+todaysdate()+"\n";
                }
            }
    }
     return "Sorry! No Item was found.\n";
}

string borrow_journal_by_title(string& title,  OtherBorrowing* bk){
            if(bk->getJournal()->get_title() == title){
                if(bk->getJournal()->get_count()!=0){
                    borrower = bk->getBorrower();
                    borrow_date = time(0);
                    bk->getJournal()->set_count(bk->getJournal()->get_count()-1);
                return "You have successfully borrowed '" + bk->getJournal()->get_title() + "'. and Due date is "+ to_string(1) + " months from "+todaysdate()+" with a delay of 7 days with below details: \n"+"->Unique Identifier: "+to_string(bk->getJournal()->get_identifier())+"\n->Borrower: "+bk->getBorowwerName()+"\n->Lending Institute: "+bk->getInstituteName()+"\n";
                 }
            else{
                return "Sorry! the Item named as '" + bk->getJournal()->get_title()  + "' is already borrowed.\n";
            }
        }
         return "Sorry! No Item was found.\n";
}

Book* addnewBooks(string& author,string& title,string& isbn, vector<Book*> book){
     for( Book* bk : book){
            if(bk->get_ISBN()==isbn){
                cout<< "A book with "+isbn+ " is already present in the library: \n";
                exit(0);
            }
     }
     Book* bk = book.back();
     int ind = bk->get_identifier() +1;
     Book* book_1 = new Book(ind,author,title,isbn,to_string(1));
    //  book.push_back(book_1);
    cout<< "New Book has been Successfully Added to the library with \n->title: "+title+"\n->author: " + author +"\n->ISBN: "+isbn+"\n";
    return book_1;
}
  
};

vector<Book*> readCSVFileBooks(const string& filename) {
    Library library;
    Book book;
    vector<Book*> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        exit(1);
    }

    string line;
    int identifier = 1;

    //Skip the first column
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string title, author, ISBN;
        string count;
        string skip;

        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, count, ',');
        getline(ss, ISBN, ',');
        getline(ss, skip, ',');
        getline(ss, author, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, title, ',');
         // Dynamically initialing the constructor 
        Book* item = new Book(identifier, title, author, ISBN, count);
        // cout<< "->Count: "+ to_string(item->get_count()) +"\n->Title: " + item->get_title() + "\n->Author: "+ item->get_authorname()+"\n->ISBN: " +  item->get_ISBN()+ "\n\n";
        // library.add_item(item);
        data.push_back(item);
        identifier++; 
    }
    file.close();
    return data;
}


vector<Publications*> readCSVFilepublications(const string& filename) {

    vector<Publications*> data;
    Library library;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        exit(1);
    }

    string line;
    int identifier = 1;

    //Skip the first column
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string title;
        getline(ss, title, ',');
         // Dynamically initialing the constructor 
        Publications* item = new Publications(identifier, title);
        // cout<< "->Title: " + item->get_title()+"\n\n";
        data.push_back(item);
        // library.add_item(item);
        identifier++; 
    }
    file.close();
    return data;
}


vector<Journals*> readCSVFilejournals(const string& filename) {

    vector<Journals*> data;
    Library library;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        exit(1);
    }

    string line;
    int identifier = 1;

    while (getline(file, line)) {
        istringstream ss(line);
        string title;
        getline(ss, title, ',');
         // Dynamically initialing the constructor 
        Journals* item = new Journals(identifier, title);
        // cout<< "->Title: " + item->get_title()+"\n\n";
        // library.add_item(item);
        data.push_back(item);
        identifier++; 
    }
    file.close();
    return data;
}

int main() {
   
    vector<Publications*> publications  = readCSVFilepublications("master_publications_rank.csv");
    vector<Book*> book = readCSVFileBooks("goodbooks-10k_master_samples_books.csv");
    vector<Journals*> journals  = readCSVFilejournals("journals - journals.csv");
    Library library;
    LibraryItem LibraryItem;
    vector<OtherBorrowing*> loanitems;
    // 2 Initial Users

        library.register_user("Akshet","student"); 
        library.register_user("Aman","faculty"); 
        int choice;
        cout<<"\t\t\t\t\t Library Management System "<<endl;
		cout<<endl;

        cout<<"Enter your user name: "<<endl;
        cout<<"Name: ";
        string name;
        cin>>name;

        User* currentuser = library.find_user(name);

        if(currentuser!=nullptr){
            cout<<"Found the USer"<<endl;
            cout<<"User Name: "<<currentuser->get_name()<<endl;
            cout<<"user Type: "<<currentuser->get_user_type()<<endl;
        }else{
            cout<<"No user with the name "<<name<<" is found"<<endl;
            return 0;
        }


    Book* bk = new Book(1001, "Introduction to Programming","Akshet","98765", to_string(10));
    Journals* jr = new Journals(2001,"IEEE somemthing on Computers");
    Publications* pb = new Publications(3001,"The Guardian");

    OtherBorrowing* item_1 = new OtherBorrowing(bk,"Indian Institue of Technology Delhi",currentuser->get_name(),Library::todaysdate());
    OtherBorrowing* items_2 = new OtherBorrowing(jr,"Indian Institue of Technology kanpur",currentuser->get_name(),Library::todaysdate());
    OtherBorrowing* items_3 = new OtherBorrowing(pb,"Indian Institue of Technology Mandi",currentuser->get_name(),Library::todaysdate());

        loanitems.push_back(item_1);
        loanitems.push_back(items_2);
        loanitems.push_back(items_3);


        cout<<"Enter your choice from below options: "<<endl;
		cout<<"Menu:"<<endl;
        cout<<"1. Add New User"<<endl;
		cout<<"2. Find All Library Items"<<endl;
		cout<<"3. Search Library Items"<<endl;
		cout<<"4. Borrow Library Items"<<endl;
        cout<<"5. show all users"<<endl;
        cout<<"6. Add new Books"<<endl;
        cout<<"7. Find Items from Other Institute"<<endl;
        cout<<"8. Borrow Books From Other Universities"<<endl;
		cout<<"0 to exit"<<endl;
        cout<<"Enter your Choice: "<<endl;
		cin>>choice;
	string no2;
	bool check = true;

    try{
    while(check){
        switch(choice)
        {
            case 1 :
            {   
                cout<<"Add new users "<<endl;
                    cout<<"User Name: ";
                    string name;
                    cin>>name;
                    cout<<"User Type: ";
                    string type;
                    cin>>type;
                    library.register_user(name,type); 
                    break;
            }
            case 2 : 
            {
                 cout<<"Which Library Item you want to find: \n";
                        cout<<"Enter 1 for Books: "<<endl;
                        cout<<"Enter 2 for Publications: "<<endl;
                        cout<<"Enter 3 for Journals: "<<endl;
                    int check;
                    cin>>check;
                    if (cin.fail()){
                            throw 505;
                        }
                    if(check == 1){
                       for(Book* ele : book){
                            cout<<ele->get_details_Book();
                       }
                    }
                    else if(check == 2){
                        for(Publications* ele : publications){
                            cout<<ele->get_details_Publication();
                       }
                    }
                    else if(check == 3){
                       for(Journals *ele : journals){
                            cout<<ele->get_details_Journal();
                       }
                    }
                    break;
            }
            case 3 : 
            {
                cout<<"Which Library Item you want to find: \n";
                        cout<<"Enter 1 from Books: "<<endl;
                        cout<<"Enter 2 from Publications: "<<endl;
                        cout<<"Enter 3 from Journals: "<<endl;
                    int check;
                    cin>>check;
                    if (cin.fail()){
                            throw 505;
                        }
                    if(check == 1){
                        int check_1;
                        cout<<"You want to find a Book: "<<endl;
                        cout<<"Enter 1 to find from title: "<<endl;
                        cout<<"Enter 2 to find from Author: "<<endl;
                        cout<<"Enter 3 to find from ISBN: "<<endl;
                        cin>>check_1;
                        if (cin.fail()){
                            throw 505;
                        }
                        if(check_1 ==1){
                            string title;
                            cout<<"Enter the title of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<"->Date: "<<Library::todaysdate()<<"\n"<<library.find_books_by_title(title,book);
                        }
                         if(check_1 ==2){
                            string Author;
                            cout<<"Enter the Author of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, Author);
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_books_by_Author(Author,book);
                        }
                         if(check_1 ==3){
                            string ISBN;
                            cout<<"Enter the ISBN of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, ISBN);
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_books_by_ISBN(ISBN,book);
                        }
                    }
                    else if(check == 2){
                        cout<<"You want to find a Publications: "<<endl;
                        string title;
                            cout<<"Enter the title of the Publications: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_publication_by_title(title,publications);
                    }
                    else if(check == 3){
                        cout<<"You want to find a Journals: "<<endl;
                        string title;
                            cout<<"Enter the title of the Journals: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                        cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_journal_by_title(title,journals);
                    }
                    break;
            }
            case 4 :
            {
                cout<<"Which Library Item you want to Borrow: \n";
                        cout<<"Enter 1 from Books: "<<endl;
                        cout<<"Enter 2 from Publications: "<<endl;
                        cout<<"Enter 3 from Journals: "<<endl;
                    int check;
                    cin>>check;
                    if (cin.fail()){
                            throw 505;
                        }
                    if(check == 1){
                        int check_1;
                        cout<<"You want to Borrow a Book: "<<endl;
                        cout<<"Enter 1 to find from title: "<<endl;
                        cout<<"Enter 2 to find from Author: "<<endl;
                        cout<<"Enter 3 to find from ISBN: "<<endl;
                        cin>>check_1;
                        if (cin.fail()){
                            throw 505;
                        }
                        if(check_1 ==1){
                            string title;
                            cout<<"Enter the title of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<library.borrow_books_by_title(title,book,currentuser);
                        }
                         if(check_1 ==2){
                            string Author;
                            cout<<"Enter the Author of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, Author);
                            cout<<library.borrow_books_by_Author(Author,book,currentuser);
                        }
                         if(check_1 ==3){
                            string ISBN;
                            cout<<"Enter the ISBN of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, ISBN);
                            cout<<library.borrow_books_by_ISBN(ISBN,book,currentuser);
                        }
                    }
                    else if(check == 2){
                        cout<<"You want to find a Publications: "<<endl;
                        string title;
                            cout<<"Enter the title of the Publications: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<library.borrow_publication_by_title(title,publications,currentuser);
                    }
                    else if(check == 3){
                        cout<<"You want to find a Journals: "<<endl;
                        string title;
                            cout<<"Enter the title of the Journals: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                        cout<<library.borrow_journal_by_title(title,journals,currentuser);
                    }
                    break;
            }  
            case 5 : 
            {
            if(currentuser->get_user_type()=="faculty"){
                cout<<"Total Users: "<<endl;
                library.find_all_user();
            }else{
                cout<<"you do not have the permission: "<<endl;
            }
            break;
            } 
            case 6 : 
            {
                cout<<"Add new Books:\n";
                cout<<"Enter the Author name: "<<endl;
                string author;
                cin.ignore();
                getline(cin, author);
                cout<<"Enter the Title: "<<endl;
                string title;
                getline(cin, title);
                cout<<"Enter the ISBN: "<<endl;
                string isbn;
                getline(cin, isbn);
                Book* newbook= library.addnewBooks(author,title,isbn,book);
                book.push_back(newbook);
            break; 
        }
         case 7 : 
            {
                cout<<"Find Items in Other Institue: "<<endl;
                cout<<"Books"<<endl;
                cout<<item_1->getBook()->get_details_Book()<<endl;
                cout<<"Journals"<<endl;
                cout<<items_2->getJournal()->get_details_Journal()<<endl;
                cout<<"Publications"<<endl;
                cout<<items_3->getPublication()->get_details_Publication()<<endl;
            break; 
        }
        case 8 : 
            {
                cout<<"Lend Items from other Institute:\n";
                cout<<"Press 1 if you want to Borrow a Book\n";
                cout<<"Press 2 if you want to Borrow a Journal\n";
                cout<<"Press 3 if you want to Borrow a Publication \n";
                int check_2;
                cin>>check_2;
                if (cin.fail()){
                   throw 505;
                }
                if(check_2 ==1){
                    cout<<"Enter Title of the Book:"<<endl;
                    string title;
                    cin.ignore();
                    getline(cin, title); 
                    cout<<library.borrow_books_by_title(title,item_1);
                }
                else if(check_2 ==3){
                    cout<<"Enter Title of the Publications:"<<endl;
                    string title;
                    cin.ignore();
                    getline(cin, title); 
                    cout<<library.borrow_publication_by_title(title,items_3);
                }
                else if(check_2 ==2){
                    cout<<"Enter Title of the Journals:"<<endl;
                    string title;
                    cin.ignore();
                    getline(cin, title); 
                    cout<<library.borrow_journal_by_title(title,items_2);
                }else{
                    cout<<"Please Enter from the above numbers only"<<endl;
                }
            break; 
        }
            case 0 :
            {
                cout<<"Thanks for visiting!"; 
                    exit(-1);
                    break;
            }
            default:
                    cout<<"Please Enter from the given options only!"<<endl;
        }
        cout<<"Enter your Choice: "<<endl;
		cin>>choice;
    }
    }catch(...){
        cout << "Invalid input! Please enter integers only!" << endl;
        }
    return 0;
}
