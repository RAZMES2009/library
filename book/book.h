#pragma once

#include "../header.h"

struct Book
{
    std::map<std::string, std::any> bookInfo;
    Book *next;

    Book(std::map<std::string, std::any> bkInfo) : bookInfo(bkInfo), next(nullptr) {};
};

class List_book
{
    Book *first;
    Book *last;

    inline const bool is_empty() const
    {
        return first == nullptr;
    }
    void get_element_books(Book *&) const;
    void remove_first();
    void remove_last();

public:
    List_book() : first(nullptr), last(nullptr) {};

    void push_back(const std::map<std::string, std::any>&);
    void print(bool) const;
    void remove_by_name(const std::string&);
    void find_book(const std::string&);
    void rent_book(const int& uid, const int& bkid);
    void set_time(char*);
    const int count_book() const;
};