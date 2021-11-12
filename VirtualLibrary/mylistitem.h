#ifndef MYLISTITEM_H
#define MYLISTITEM_H

#include <QString>
#include <QDebug>

class MyListItem
{
public:
    MyListItem(QString author, QString name, int year, int pages, double price);
    MyListItem();

    QString getAuthor() {return author;}
    QString getName()   {return name;}
    int     getYear()   {return year;}
    int     getPages()  {return pages;}
    double  getPrice()  {return price;}

    void setAuthor(QString Author) {this->author = Author;}
    void setName(QString Name)     {this->name = Name;}
    void setYear(int Year)         {this->year = Year;}
    void setPages(int Pages)       {this->pages = Pages;}
    void setPrice(double Price)    {this->price = Price;}

    MyListItem &operator =(MyListItem *item);

    MyListItem *next;
private:
    QString author;
    QString name;
    int year;
    int pages;
    double price;
};

#endif // MYLISTITEM_H
