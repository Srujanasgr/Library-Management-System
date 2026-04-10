#include <iostream>
#include <unordered_map>
using namespace std;

// ------------------ BOOK CLASS ------------------

class Book {
public:
    int id;
    string name;
    string author;
    int copies;

    // Default constructor (IMPORTANT)
    Book() {}

    Book(int id, string name, string author, int copies)
        : id(id), name(name), author(author), copies(copies) {}
};

// ------------------ MEMBER CLASS ------------------

class Member {
public:
    int id;
    string name;
    int issuedBookId;

    // Default constructor (IMPORTANT)
    Member() {
        issuedBookId = -1;
    }

    Member(int id, string name)
        : id(id), name(name), issuedBookId(-1) {}
};

// ------------------ DATA STORAGE ------------------

unordered_map<int, Book> books;
unordered_map<int, Member> members;

// ------------------ BOOK FUNCTIONS ------------------

void addBook() {
    int id, copies;
    string name, author;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Name: ";
    getline(cin, name);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Copies: ";
    cin >> copies;

    books[id] = Book(id, name, author, copies);

    cout << "Book Added Successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books available\n";
        return;
    }

    for (auto &p : books) {
        cout << p.second.id << " | " << p.second.name
             << " | " << p.second.author
             << " | Copies: " << p.second.copies << endl;
    }
}

// ------------------ MEMBER FUNCTIONS ------------------

void addMember() {
    int id;
    string name;

    cout << "Enter Member ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, name);

    members[id] = Member(id, name);

    cout << "Member Added Successfully!\n";
}

void displayMembers() {
    if (members.empty()) {
        cout << "No members available\n";
        return;
    }

    for (auto &p : members) {
        cout << p.second.id << " | " << p.second.name
             << " | Issued Book: "
             << (p.second.issuedBookId == -1 ? "None" : to_string(p.second.issuedBookId))
             << endl;
    }
}

// ------------------ ISSUE BOOK ------------------

void issueBook() {
    int memberId, bookId;

    cout << "Enter Member ID: ";
    cin >> memberId;

    cout << "Enter Book ID: ";
    cin >> bookId;

    if (!members.count(memberId)) {
        cout << "Member not found\n";
        return;
    }

    if (!books.count(bookId)) {
        cout << "Book not found\n";
        return;
    }

    if (books[bookId].copies <= 0) {
        cout << "No copies available\n";
        return;
    }

    if (members[memberId].issuedBookId != -1) {
        cout << "Member already has a book\n";
        return;
    }

    books[bookId].copies--;
    members[memberId].issuedBookId = bookId;

    cout << "Book Issued Successfully!\n";
}

// ------------------ RETURN BOOK ------------------

void returnBook() {
    int memberId;

    cout << "Enter Member ID: ";
    cin >> memberId;

    if (!members.count(memberId)) {
        cout << "Member not found\n";
        return;
    }

    int bookId = members[memberId].issuedBookId;

    if (bookId == -1) {
        cout << "No book issued\n";
        return;
    }

    books[bookId].copies++;
    members[memberId].issuedBookId = -1;

    cout << "Book Returned Successfully!\n";
}

// ------------------ SEARCH BOOK ------------------

void searchBook() {
    string name;
    cin.ignore();

    cout << "Enter Book Name to Search: ";
    getline(cin, name);

    bool found = false;

    for (auto &p : books) {
        if (p.second.name == name) {
            cout << "Found: " << p.second.name << " by " << p.second.author << endl;
            found = true;
        }
    }

    if (!found) cout << "Book not found\n";
}

// ------------------ MAIN MENU ------------------

int main() {
    int choice;

    while (true) {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Show Books\n";
        cout << "3. Add Member\n";
        cout << "4. Show Members\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Search Book\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: addMember(); break;
            case 4: displayMembers(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: searchBook(); break;
            case 0: return 0;
            default: cout << "Invalid choice\n";
        }
    }
}