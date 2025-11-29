#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() {}

    Book(int id, string title, string author, bool issued) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->issued = issued;
    }

    string toCSV() {
        return to_string(id) + "," + title + "," + author + "," + (issued ? "1" : "0");
    }
};

class Library {
    vector<Book> books;
    string filename = "library.csv";

public:
    Library() {
        loadFromCSV();
    }

    void loadFromCSV() {
        ifstream file(filename);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, title, author, issuedStr;

            getline(ss, idStr, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, issuedStr, ',');

            int id = stoi(idStr);
            bool issued = (issuedStr == "1");

            books.push_back(Book(id, title, author, issued));
        }
        file.close();
    }

    void saveToCSV() {
        ofstream file(filename);
        for (auto &b : books)
            file << b.toCSV() << endl;
        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Book Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author, false));
        saveToCSV();
        cout << "Book Added Successfully!\n";
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to Issue: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (b.issued) {
                    cout << "Book Already Issued!\n";
                } else {
                    b.issued = true;
                    saveToCSV();
                    cout << "Book Issued Successfully!\n";
                }
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to Return: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (!b.issued) {
                    cout << "Book Was Not Issued!\n";
                } else {
                    b.issued = false;
                    saveToCSV();
                    cout << "Book Returned Successfully!\n";
                }
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID to Search: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                cout << "\n--- Book Found ---\n";
                cout << "ID: " << b.id << endl;
                cout << "Title: " << b.title << endl;
                cout << "Author: " << b.author << endl;
                cout << "Issued: " << (b.issued ? "Yes" : "No") << endl;
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    void listBooks() {
        cout << "\n--- Library Books ---\n";
        for (auto &b : books) {
            cout << "ID: " << b.id
                 << " | Title: " << b.title
                 << " | Author: " << b.author
                 << " | Issued: " << (b.issued ? "Yes" : "No")
                 << endl;
        }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n===== Library Book Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. Search Book\n";
        cout << "5. List All Books\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.issueBook(); break;
            case 3: lib.returnBook(); break;
          case 4: lib.searchBook(); break;
            case 5: lib.listBooks(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}