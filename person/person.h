#pragma once

#include "../header.h"

struct Node_person
{
    std::map<std::string, std::any> personInfo;
    Node_person *next;

    Node_person(std::map<std::string, std::any> &pInfo) : personInfo(pInfo), next(nullptr) {};
};

class List_person
{
    Node_person *first;
    Node_person *last;

    inline const bool is_empty() const
    {
        return first == nullptr;
    }

    void get_persons(Node_person *&) const;
    void remove_first();
    void remove_last();
    Node_person *get_user_by_nameID(const std::string &name, const int uid);

public:
    List_person() : first(nullptr), last(nullptr) {};
    void push_back(std::map<std::string, std::any> &);
    void print() const;
    void find(const std::string);
    void remove(const std::string, const int);
    bool rent_book(const std::string, const int, const int);
};
