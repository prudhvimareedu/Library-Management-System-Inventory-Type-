#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Book {
public:
    int id;
    string title;
    bool issued;

    Book(int i, string t, bool is) : id(i), title(t), issued(is) {}
};

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("books.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, issuedStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, issuedStr, ',');

        books.push_back(Book(stoi(idStr), title, stoi(issuedStr)));
    }

    return books;
}

void saveBooks(vector<Book>& books) {
    ofstream file("books.txt");
    for (auto& b : books) {
        file << b.id << "," << b.title << "," << b.issued << endl;
    }
}

void addBook(vector<Book>& books) {
    int id;
    string title;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);

    books.push_back(Book(id, title, false));
    saveBooks(books);

    cout << "Book Added Successfully!\n";
}

void issueBook(vector<Book>& books) {
    int id;
    cout << "Enter Book ID to Issue: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            if (!b.issued) {
                b.issued = true;
                saveBooks(books);
                cout << "Book Issued!\n";
            } else {
                cout << "Book Already Issued!\n";
            }
            return;
        }
    }

    cout << "Book Not Found!\n";
}

void returnBook(vector<Book>& books) {
    int id;
    cout << "Enter Book ID to Return: ";
    cin >> id;

    for (auto& b : books) {
        if (b.id == id) {
            if (b.issued) {
                b.issued = false;
                saveBooks(books);
                cout << "Book Returned!\n";
            } else {
                cout << "Book Was Not Issued!\n";
            }
            return;
        }
    }

    cout << "Book Not Found!\n";
}

void viewBooks(vector<Book>& books) {
    cout << "\n--- Book List ---\n";
    for (auto& b : books) {
        cout << "ID: " << b.id
             << " | Title: " << b.title
             << " | Status: " << (b.issued ? "Issued" : "Available")
             << endl;
    }
}

int main() {
    vector<Book> books = loadBooks();
    int choice;

    do {
        cout << "\n===== Library System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. View Books\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(books); break;
            case 2: issueBook(books); break;
            case 3: returnBook(books); break;
            case 4: viewBooks(books); break;
        }

    } while (choice != 5);

    return 0;
}