#include <iostream>
#include <fstream>
#include <sstream>
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
    string amount;

public:
Journals(){

    }

    Journals(int id, string title)
        : LibraryItem(id, title) {}


    Journals(int id, string title,string amount)
        : LibraryItem(id, title), amount(amount){}

    string get_type() override {
         return "->Title: " + get_title();
    }

    string get_details_Journal(){
        return LibraryItem::get_details_Journal();
    }

    string get_amount(){
        return amount;
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
    User* user2[200];
    //vector<User*> users;
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

 void register_user(const string& username, const string& user_type, int index) {
        User* user = new User(username, user_type);
        //users.push_back(user);
         if(index < 200) {
        user2[index++] = user;
         }else{
            cout<<"Out of Range: ";
         }
    }


    User* find_user(const string& username) {
        for (User* user : user2) {
            if (user->get_name() == username) {
                return user;
            }
        }
        return nullptr;
    }

    void find_all_user(int index) {
        for (int i =0;i<index;i++) {
            cout<<"User Name: "<<user2[i]->get_name()<<"\nUser Type: "<<user2[i]->get_user_type()<<endl;
        }
    }

    string find_books_by_title(string& title,  Book* data, int index) {
        for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                return "->Unique Identifier: "+to_string(data[i].get_identifier())+"\n->Count: "+ to_string(data[i].get_count()) +"\n->Title: " + title + "\n->Author: "+data[i].get_authorname()+"\n->ISBN: " +data[i].get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with the title: "+ title+"\n";
    }

     string find_books_by_Author(string& author,  Book* data, int index) {
        for(int i =0;i<index;i++){
            if(data[i].get_authorname()==author){
                return "->Unique Identifier:: "+to_string(data[i].get_identifier())+"\n->Count: "+ to_string(data[i].get_count()) +"\n->Title: " + data[i].get_title() + "\n->Author: "+data[i].get_authorname()+"\n->ISBN: " + data[i].get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with the Author: "+ author+"\n";
    }

     string find_books_by_ISBN(string& ISBN,  Book* data, int index) {
        for(int i =0;i<index;i++){
            if(data[i].get_ISBN()==ISBN){
                return "->Unique Identifier: "+to_string(data[i].get_identifier())+"\n->Count: "+ to_string(data[i].get_count()) +"\n->Title: " + data[i].get_title() + "\n->Author: "+data[i].get_authorname()+"\n->ISBN: " + data[i].get_ISBN()+ "\n\n";
            }
        }
        return "No Book Found with ISBN: "+ ISBN+"\n";
    }

     string find_publication_by_title(string& title,  Publications* data, int index) {
        for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                return "->Unique Identifier: "+to_string(data[i].get_identifier())+"\n->Count: "+ to_string(data[i].get_count()) +"\n->Title: " + data[i].get_title() + "\n\n";
            }
        }
        return "No Publications Found with the title: "+ title+"\n";
    }

     string find_journal_by_title(string& title,  Journals* data, int index) {
        for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                return "->Unique Identifier: "+to_string(data[i].get_identifier())+"\n->Count: "+ to_string(data[i].get_count()) +"\n->Title: " + data[i].get_title() + "\n\n";
            }
        }
        return "No Journals Found with title: "+ title+"\n";
    }

    string borrow_books_by_title(string& title,  Book* data, User* user, int index){
         for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                if(data[i].get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                   data[i].set_count(data[i].get_count()-1);
                    if(user->get_user_type()=="student"){
                      due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                      due_date = 6;
                    }else{
                        return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" + data[i].get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
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

string borrow_books_by_Author(string& author,  Book* data, User* user, int index){
         for(int i =0;i<index;i++){
            if(data[i].get_authorname()==author){
                if(data[i].get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    data[i].set_count(data[i].get_count()-1);
                    if(user->get_user_type()=="student"){
                         due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                         due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" +data[i].get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                 }
            }
    }
    return "Sorry! No Item was found.\n";
}


string borrow_books_by_ISBN(string& isbn,  Book* data, User* user, int index){
         for(int i =0;i<index;i++){
            if(data[i].get_ISBN()==isbn){
                if(data[i].get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    data[i].set_count(data[i].get_count()-1);
                    if(user->get_user_type()=="student"){
                       due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
               return "You have successfully borrowed '" + data[i].get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
                 }
            }
    }
    return "Sorry! No Item was found.\n";
}

string borrow_publication_by_title(string& title,  Publications* data, User* user, int index){
         for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                if(data[i].get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    data[i].set_count(data[i].get_count()-1);
                    if(user->get_user_type()=="student"){
                        due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 1;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" + data[i].get_title() + "'. and Due date is "+ to_string(due_date) + " months from "+todaysdate()+"\n";
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

string borrow_journal_by_title(string& title,  Journals* data, User* user, int index){
         for(int i =0;i<index;i++){
            if(data[i].get_title()==title){
                if(data[i].get_count()!=0){
                    borrower = user->get_name();
                    borrow_date = time(0);
                    int due_date;
                    data[i].set_count(data[i].get_count()-1);
                    if(user->get_user_type()=="student"){
                         due_date = 1;
                    }else if(user->get_user_type()=="faculty"){
                        due_date = 6;
                    }else{
                return " Not a valid User Type";
                    }
                return "You have successfully borrowed '" +data[i].get_title() + "'.and Due date is "+ to_string(due_date) + " month/s from "+todaysdate()+"\n";
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

Book* addnewBooks(string& author,string& title,string& isbn, Book* book, int index){
      for(int i =0;i<index;i++){
            if(book[i].get_ISBN()==isbn){
                cout<< "A book with "+isbn+ " is already present in the library: \n";
                exit(0);
            }
     }
     Book* bk = &book[index--];
     int ind = bk->get_identifier() +1;
     Book* book_1 = new Book(ind,author,title,isbn,to_string(1));
    //  book.push_back(book_1);
    cout<< "New Book has been Successfully Added to the library with \n->title: "+title+"\n->author: " + author +"\n->ISBN: "+isbn+"\n";
    return book_1;
}
  
};

Book* readCSVFileBooks(const string& filename) {
    Library library;
    Book book;
    //vector<Book*> data;
    Book* data= new Book[100];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        exit(1);
    }

    string line;
    int identifier = 1;

    //Skip the first column
    getline(file, line);

    int i=0;
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
        // cout<< "->Count: "+ to_string(item->get_count()) +"\n->Title: " + item->get_title() + "\n->Author: "+ item->get_authorname()+"\n->ISBN: " +  item->get_ISBN()+ "\n\n";
        // library.add_item(item);
        data[i]= Book(identifier, title, author, ISBN, count);
        i++;
        identifier++; 
    }
    file.close();
    return data;
}


Publications* readCSVFilepublications(const string& filename) {

    Publications* data= new Publications[200];
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
    int i=0;
    while (getline(file, line)) {
        istringstream ss(line);
        string title;
        getline(ss, title, ',');
         // Dynamically initialing the constructor 
        // cout<< "->Title: " + item->get_title()+"\n\n";
        data[i]=Publications(identifier, title);
        // library.add_item(item);
        identifier++; 
        i++;
    }
    file.close();
    return data;
}


Journals* readCSVFilejournals(const string& filename,bool check) {

    Journals* data =  new Journals[200];
    Library library;

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open the CSV file." << endl;
        exit(1);
    }

    string line;
    int identifier = 1;
    string amount;
    int i=0;
    while (getline(file, line)) {
        istringstream ss(line);
        string title;
        getline(ss, title, ',');
        getline(ss, amount, ',');
         // Dynamically initialing the constructor 
        if(!check){
        data[i] = Journals(identifier, title);
         }else{
        data[i] = Journals(identifier, title,amount);
         }
        // cout<< "->Title: " + item->get_title()+"\n\n";
        // library.add_item(item);
        identifier++; 
        i++;
    }
    file.close();
    return data;
}

int main() {
   
    Publications* publications  = readCSVFilepublications("master_publications_rank.csv");
    Book* book = readCSVFileBooks("goodbooks-10k_master_samples_books.csv");
    Journals* journals  = readCSVFilejournals("journals - journals.csv",false);


    int index_user  = 0 ;
    int index_book  = 99 ;
    int index_journal  = 99 ;
    int index_publication  = 80 ;

    Library library;
    LibraryItem LibraryItem;;
    // 2 Initial Users

        library.register_user("Akshet","student",index_user++); 
        library.register_user("Aman","faculty",index_user++); 
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

        cout<<"Enter your choice from below options: "<<endl;
		cout<<"Menu:"<<endl;
        cout<<"1. Add New User"<<endl;
		cout<<"2. Find All Library Items"<<endl;
		cout<<"3. Search Library Items"<<endl;
		cout<<"4. Borrow Library Items"<<endl;
        cout<<"5. show all users"<<endl;
        cout<<"6. Add new Books"<<endl;
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
                    library.register_user(name,type,index_user++);
                    cout<<"New User Added! "<<endl; 
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
                        for( int i =0;i<index_book;i++){
                            cout<<book[i].get_details_Book();
                        }
                    //    for(Book* ele : book){
                    //         cout<<ele->get_details_Book();
                    //    }
                    }
                    else if(check == 2){
                        for( int i =0;i<index_publication;i++){
                            cout<<publications[i].get_details_Publication();
                       }
                    }
                    else if(check == 3){
                       for( int i =0;i<index_journal;i++){
                            cout<<journals[i].get_details_Journal();
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
                            cout<<"->Date: "<<Library::todaysdate()<<"\n"<<library.find_books_by_title(title,book,index_book);
                        }
                         if(check_1 ==2){
                            string Author;
                            cout<<"Enter the Author of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, Author);
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_books_by_Author(Author,book, index_book);
                        }
                         if(check_1 ==3){
                            string ISBN;
                            cout<<"Enter the ISBN of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, ISBN);
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_books_by_ISBN(ISBN,book, index_book);
                        }
                    }
                    else if(check == 2){
                        cout<<"You want to find a Publications: "<<endl;
                        string title;
                            cout<<"Enter the title of the Publications: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_publication_by_title(title,publications,index_publication);
                    }
                    else if(check == 3){
                        cout<<"You want to find a Journals: "<<endl;
                        string title;
                            cout<<"Enter the title of the Journals: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                        cout<<"->Date: "<<Library::todaysdate()<<" \n"<<library.find_journal_by_title(title,journals,index_journal);
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
                            cout<<library.borrow_books_by_title(title,book,currentuser, index_book);
                        }
                         if(check_1 ==2){
                            string Author;
                            cout<<"Enter the Author of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, Author);
                            cout<<library.borrow_books_by_Author(Author,book,currentuser, index_book);
                        }
                         if(check_1 ==3){
                            string ISBN;
                            cout<<"Enter the ISBN of the Book: "<<endl;
                            cin.ignore();
                            getline(cin, ISBN);
                            cout<<library.borrow_books_by_ISBN(ISBN,book,currentuser, index_book);
                        }
                    }
                    else if(check == 2){
                        cout<<"You want to find a Publications: "<<endl;
                        string title;
                            cout<<"Enter the title of the Publications: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                            cout<<library.borrow_publication_by_title(title,publications,currentuser, index_publication);
                    }
                    else if(check == 3){
                        cout<<"You want to find a Journals: "<<endl;
                        string title;
                            cout<<"Enter the title of the Journals: "<<endl;
                            cin.ignore();
                            getline(cin, title); 
                        cout<<library.borrow_journal_by_title(title,journals,currentuser, index_journal);
                    }
                    break;
            }  
            case 5 : 
            {
            if(currentuser->get_user_type()=="faculty"){
                cout<<"Total Users: "<<endl;
                library.find_all_user(index_user);
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
                Book* newbook= library.addnewBooks(author,title,isbn,book, index_book);
                book[index_book++] =*newbook;
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
