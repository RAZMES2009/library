#include "./person.h"
#include "person.h"

void List_person::remove_first()
{
    if (is_empty())
        return;

    Node_person *p = first;
    first = first->next;
    delete p;
}

void List_person::remove_last()
{
    if (is_empty())
        return;

    if (first == last)
        remove_first();

    Node_person *p = first;

    while (p->next != last)
        p = p->next;

    p->next = nullptr;
    delete last;
    last = p;
}

void List_person::remove(const std::string name, const int id)
{
    if (is_empty())
        return;

    if (std::any_cast<const char *>(first->personInfo.at("uFullName")) == name &&
        std::any_cast<int>(first->personInfo.at("uId")) == id)
    {
        remove_first();
        return;
    }

    if (std::any_cast<const char *>(last->personInfo.at("uFullName")) == name &&
        std::any_cast<int>(last->personInfo.at("uId")) == id)
    {
        remove_last();
        return;
    }

    Node_person *slow = first;
    Node_person *fast = first->next;

    while (fast && (std::any_cast<const char *>(fast->personInfo.at("uFullName")) != name ||
                    std::any_cast<int>(fast->personInfo.at("uId")) != id))
    {
        slow = slow->next;
        fast = fast->next;
    }
    if (!fast)
    {
        std::cout << "The person with full name " << name << " and id " << id << " doesn't find" << std::endl;
        std::cout << std::string(20, '*') << std::endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
}

void List_person::find(const std::string name)
{
    if (is_empty())
        return;

    if (std::any_cast<const char *>(first->personInfo.at("uFullName")) == name)
    {
        get_persons(first);
        return;
    }

    if (std::any_cast<const char *>(last->personInfo.at("uFullName")) == name)
    {
        get_persons(last);
        return;
    }

    Node_person *fast = get_user_by_nameID(name, -1);
    if (fast != nullptr)
        get_persons(fast);
}

void List_person::push_back(std::map<std::string, std::any> &pInfo)
{
    Node_person *p = new Node_person(pInfo);
    if (is_empty())
    {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
}

void List_person::print() const
{
    if (is_empty())
        return;

    Node_person *p = first;

    while (p)
    {
        get_persons(p);
        p = p->next;
    }
}

void List_person::get_persons(Node_person *&p) const
{
    for (auto const &[key, val] : p->personInfo)
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

bool List_person::rent_book(const std::string name, const int uid, const int bkid)
{
    if (is_empty()){
        return false;
    }

    if (std::any_cast<const char *>(first->personInfo.at("uFullName")) == name &&
        std::any_cast<int>(first->personInfo.at("uId")) == uid)
    {
        if (!std::any_cast<bool>(first->personInfo.at("isRentBook")))
        {
            first->personInfo.at("isRentBook") = true;
            first->personInfo.at("bookId") = bkid;
        }
        return true;
    }

    if (std::any_cast<const char *>(last->personInfo.at("uFullName")) == name &&
        std::any_cast<int>(last->personInfo.at("uId")) == uid)
    {
        if (!std::any_cast<bool>(last->personInfo.at("isRentBook")))
        {
            last->personInfo.at("isRentBook") = true;
            last->personInfo.at("bookId") = bkid;
        }
        return true;
    }

    Node_person *fast = get_user_by_nameID(name, uid);
    if (fast != nullptr)
    {
        if (!std::any_cast<bool>(last->personInfo.at("isRentBook")))
        {
            last->personInfo.at("isRentBook") = true;
            last->personInfo.at("bookId") = bkid;
        }
        return true;
    }
    return false;
}

Node_person *List_person::get_user_by_nameID(const std::string &name, const int uid)
{
    Node_person *slow = first;
    Node_person *fast = first->next;
    while (fast && (std::any_cast<const char *>(fast->personInfo.at("uFullName")) != name ||
                    std::any_cast<int>(fast->personInfo.at("uId")) != uid))
    {
        slow = slow->next;
        fast = fast->next;
    }
    if (!fast)
    {
        std::string stringOut = uid == -1 ? "" : " and id " + uid;
        std::cout << "The person with full name " << name << stringOut << " doesn't find" << std::endl;
        std::cout << std::string(20, '*') << std::endl;
        return nullptr;
    }
    return fast;
}