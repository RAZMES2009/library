#include "./book/book.h"
#include "./person/person.h"

using namespace std;

int32_t choiceAdminOption()
{
    string choice;
    getline(cin, choice);
    if (choice.size() == 1)
    {
        if (isdigit(choice[0]) && stoi(choice) > 0 && stoi(choice) < 7)
            return stoi(choice);
    }
    cout << "Enter the valid number" << endl;
    return choiceAdminOption();
}

int main(int argc, char const *argv[])
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
         << "8. Delete a person by name/id" << endl;

    List_person list_person;

    map<string, any> newPerson1{
        {"uId", 0},
        {"uFullName", "Jones David"},
        {"Adress", "Backer street 18"},
        {"isRentBook", false},
        {"bookId", -1},
        {"fine", 0},
    };

    map<string, any> newPerson2{
        {"uId", 1},
        {"uFullName", "Syomin Rostislav"},
        {"Adress", "Patrick st. 224"},
        {"isRentBook", false},
        {"bookId", -1},
        {"fine", 0},
    };

    list_person.push_back(newPerson1);
    list_person.push_back(newPerson2);
    // list_person.find("Syomin Rostislav");
    list_person.print();
    // list_person.remove("Syomin Rostislav", 0);
    // list_person.print();

    List_book listBk;

    // time_t result = time(nullptr);
    // result += 1.21e+6;

    // struct tm *timeInfo = localtime(&result);

    // char timeR[10];
    // strftime(timeR, 10, "%d/%m/%y", timeInfo);
    char time[10] = "00/00/00\0";

    map<string, any> newBook1{
        {"bkId", 0},
        {"bkName", "Metro 2033"},
        {"isAvailable", true},
        {"userId", -1},
        {"returnTime", time},
    };

    map<string, any> newBook2{
        {"bkId", 1},
        {"bkName", "Crime and punishment"},
        {"isAvailable", true},
        {"userId", -1},
        {"returnTime", time},
    };

    listBk.push_back(newBook1);
    listBk.push_back(newBook2);
    // listBk.remove_by_name("Cridme and punishment");
    // listBk.find_book("Crime and punishment");
    listBk.print(1);

    if(list_person.rent_book("Syomin Rostislav", 1, 0))
        listBk.rent_book(1, 0);
    
    list_person.find("Syomin Rostislav");
    listBk.print(0);

    return 0;
}
