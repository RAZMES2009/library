#include "book.h"

const int List_book::count_book() const
{
    if (is_empty())
        return 0;

    Book *p = first;
    int count = 0;
    
    while (p)
    {
        count++;
        p = p->next;
    }
    return count;
}

void List_book::find_book(const std::string &name)
{
    if (is_empty())
        return;
    if (std::any_cast<std::string>(first->bookInfo.at("bkName")) == name)
    {
        get_element_books(first);
        return;
    }
    if (std::any_cast<std::string>(last->bookInfo.at("bkName")) == name)
    {
        get_element_books(last);
        return;
    }

    Book *slow = first;
    Book *fast = first->next;

    while (fast && std::any_cast<std::string>(fast->bookInfo.at("bkName")) != name)
    {
        slow = slow->next;
        fast = fast->next;
    }
    if (!fast)
    {
        std::cout << "The book of name " << name << " is not find" << std::endl;
        return;
    }
    get_element_books(fast);
}

void List_book::remove_first()
{
    if (is_empty())
        return;

    Book *p = first;
    first = p->next;
    delete p;
}

void List_book::remove_last()
{
    if (is_empty())
        return;

    if (last == first)
        remove_first();

    Book *p = first;
    while (p->next != last)
        p = p->next;

    p->next = nullptr;
    delete last;
    last = p;
}

void List_book::remove_by_name(const std::string &name)
{
    if (is_empty())
        return;
    if (std::any_cast<std::string>(first->bookInfo.at("bkName")) == name)
    {
        remove_first();
        return;
    }
    if (std::any_cast<std::string>(last->bookInfo.at("bkName")) == name)
    {
        remove_last();
        return;
    }

    Book *slow = first;
    Book *fast = first->next;

    while (fast && std::any_cast<std::string>(fast->bookInfo.at("bkName")) != name)
    {
        slow = slow->next;
        fast = fast->next;
    }
    if (!fast)
    {
        std::cout << "The book of name " << name << " is not find" << std::endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
}

void List_book::push_back(const std::map<std::string, std::any> &bkInfo)
{
    Book *p = new Book(bkInfo);
    if (is_empty())
    {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
}

void List_book::print(bool isAvailable) const
{
    if (is_empty())
        return;

    Book *p = first;
    while (p)
    {
        if (isAvailable && std::any_cast<bool>(p->bookInfo.at("isAvailable")) == 1)
            get_element_books(p);
        else if (!isAvailable && std::any_cast<bool>(p->bookInfo.at("isAvailable")) == 0)
            get_element_books(p);

        p = p->next;
    }
}
void List_book::get_element_books(Book *&p) const
{
    for (auto const &[key, val] : p->bookInfo)
    {
        std::cout << key << ' ';
        try
        {
            if (val.type() == typeid(int))
                std::cout << std::any_cast<int>(val);
            else if (val.type() == typeid(bool))
                std::cout << std::any_cast<bool>(val);
            else if (val.type() == typeid(const char *))
                std::cout << std::any_cast<const char *>(val);
            else if (val.type() == typeid(std::string))
                std::cout << std::any_cast<std::string>(val);
            else
                std::cerr << "Unsupported type";
        }
        catch (const std::bad_any_cast &e)
        {
            std::cerr << "Bad any cast: " << e.what();
        }
        std::cout << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
};

void List_book::rent_book(const int &uid, const int &bkid)
{
    if (is_empty())
        return;
    char timeR[10];
    if (std::any_cast<int>(first->bookInfo.at("bkId")) == bkid)
    {
        if (std::any_cast<bool>(first->bookInfo.at("isAvailable")))
        {
            first->bookInfo.at("isAvailable") = false;
            first->bookInfo.at("userId") = uid;
            set_time(timeR);
            std::string str(timeR, 10);
            first->bookInfo.at("returnTime") = str;
            std::cout << "Successful registration!" << std::endl;
            return;
        }
        std::cout << "Registration failed" << std::endl;
        return;
    }
    if (std::any_cast<int>(last->bookInfo.at("bkId")) == bkid)
    {
        if (std::any_cast<bool>(last->bookInfo.at("isAvailable")))
        {
            last->bookInfo.at("isAvailable") = false;
            last->bookInfo.at("userId") = uid;
            set_time(timeR);
            std::string str(timeR, 10);
            last->bookInfo.at("returnTime") = str;
            std::cout << "Successful registration!" << std::endl;
            return;
        }
        std::cout << "Registration failed" << std::endl;
        return;
    }

    Book *slow = first;
    Book *fast = first->next;

    while (fast && std::any_cast<int>(fast->bookInfo.at("bkid")) != bkid)
    {
        slow = slow->next;
        fast = fast->next;
    }
    if (!fast)
    {
        std::cout << "The book id " << bkid << " doesn't find" << std::endl;
        return;
    }
    if (std::any_cast<bool>(fast->bookInfo.at("isAvailable")))
    {
        fast->bookInfo.at("isAvailable") = false;
        fast->bookInfo.at("userId") = uid;
        set_time(timeR);
        std::string str(timeR, 10);
        fast->bookInfo.at("returnTime") = str;
        std::cout << "Successful registration!" << std::endl;
        return;
    }
    std::cout << "Registration failed" << std::endl;
    return;
}

void List_book::set_time(char *timeR)
{
    std::cout << "How many days is the book for rent?" << std::endl;
    int32_t days;
    scanf("%d", &days);

    time_t result = time(nullptr);
    result += days * 86400;

    struct tm *timeInfo = localtime(&result);

    strftime(timeR, 10, "%d/%m/%y", timeInfo);
}
