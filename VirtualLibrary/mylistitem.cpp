#include "mylistitem.h"

MyListItem::MyListItem(QString author, QString name, int year, int pages, double price)
{
    this->author = author;
    this->name = name;
    this->year = year;
    this->pages = pages;
    this->price = price;
    this->next = nullptr;
}

MyListItem::MyListItem()
{
    this->next = nullptr;
}

MyListItem &MyListItem::operator =(MyListItem *item)
{
    this->author = item->author;
    this->name = item->name;
    this->year = item->year;
    this->pages = item->pages;
    this->price = item->price;

    return *item;
}
