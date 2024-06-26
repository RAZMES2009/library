#include "./book/book.h"
#include "./person/person.h"
#include "main.h"

using namespace std;

bool runApp = true;

int32_t choiceAdminOption()
{
    string choice;
    getline(cin, choice);
    if (choice.size() == 2)
    {
        if ((isdigit(choice[0]) && stoi(choice) > 0 && stoi(choice) < 11) || choice == "10")
            return stoi(choice);
    }
    cout << "Enter the valid number" << endl;
    return choiceAdminOption();
}

int main(int argc, char const *argv[])
{
    run_app();

    return 0;
}

void run_app()
{
    List_person list_person;
    List_book list_book;
    while (runApp)
    {
        cout << "\t\tAdmin panel" << endl
             << endl
             << "Please, choose the options: " << endl
             << "1. Show all available books" << endl
             << "2. Show all rented books" << endl
             << "3. Add a new book" << endl
             << "4. Delete book" << endl
             << "5. Find a book" << endl
             << "6. Add a new person" << endl
             << "7. Find a person by name" << endl
             << "8. Delete a person by name/id" << endl
             << "9. Rent book" << endl
             << "10. Save and Exit" << endl;

        switch (choiceAdminOption())
        {
        case 1:
            list_book.print(true);
            break;
        case 2:
            list_book.print(false);
            break;
        case 3:
            add_new_book(list_book);
            break;
        case 4:
        {
            cout << endl
                 << "Please, enter name book: ";
            string tmp = "";
            getline(cin, tmp);
            list_book.remove_by_name(tmp);
            break;
        }
        case 5:
        {
            cout << endl
                 << "Please, enter name book: ";
            string tmp = "";
            getline(cin, tmp);
            list_book.find_book(tmp);
            break;
        }
        case 6:
            add_new_user(list_person);
            break;
        case 7:
        {
            cout << endl
                 << "Please, enter full name user: ";
            string tmp = "";
            getline(cin, tmp);
            list_person.find(tmp);
            break;
        }
        case 8:
        {
            string uid = "", name = "";
            cout << endl
                 << "Please, enter id user: ";
            getline(cin, uid);
            cout << endl
                 << "Please, enter full name user: ";
            getline(cin, name);
            list_person.remove(name, stoi(uid));
            break;
        }
        case 9:
        {
            string uid = "", name = "", bkid = "";
            cout << endl
                 << "Please, enter id user: ";
            getline(cin, uid);
            cout << endl
                 << "Please, enter full name user: ";
            getline(cin, name);
            cout << endl
                 << "Please, enter book id: ";
            getline(cin, bkid);
            list_person.rent_book(name, stoi(uid), stoi(bkid));
            list_book.rent_book(stoi(uid), stoi(bkid));
            break;
        }
        case 10:
            runApp = false;
        }
    }
}

void add_new_user(List_person &list_person)
{
    map<string, any> newPerson{
        {"uId", 0},
        {"uFullName", ""},
        {"Adress", ""},
        {"isRentBook", false},
        {"bookId", -1},
        {"fine", 0},
    };
    newPerson["uId"] = list_person.count_user();
    cout << endl
         << "Please, enter full name new user: ";
    string tmp = "";
    getline(cin, tmp);
    newPerson["uFullName"] = tmp;
    tmp.clear();
    cout << endl
         << "Please, enter adress new user: ";
    getline(cin, tmp);
    newPerson["Adress"] = tmp;
    list_person.push_back(newPerson);
}

void add_new_book(List_book &list_book)
{
    map<std::string, std::any> newBook{
        {"bkId", 0},
        {"bkName", "default"},
        {"isAvailable", true},
        {"userId", -1},
        {"returnTime", "00/00/00\0"},
    };
    newBook["bkId"] = list_book.count_book();
    cout << endl
         << "Please, enter name book: ";
    string tmp = "";
    getline(cin, tmp);
    newBook["bkName"] = tmp;
    list_book.push_back(newBook);
}