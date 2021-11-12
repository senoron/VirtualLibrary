#ifndef MYLIST_H
#define MYLIST_H

#include "mylistitem.h"
#include <QTableWidget>
#include "warningform.h"
#include "onewarningform.h"
#include <QTableWidget>
#include <QLabel>
#include <QFrame>

class MyList
{
public:
    MyList();
    ~MyList();

    void append(MyListItem *item);
    void print();
    bool readFromFile(QString fileName);
    MyListItem *getHead(){return head;}
    MyListItem *at(int pos);
    void saveToFile(QString fileName);
    void deletePos(int pos);
    void free();
    void sort(QString type);
    int count(){return itemsCount;}

private:
    MyListItem *head;
    void sortNumbers(double (* compare)(MyListItem *one, MyListItem *two));
    int itemsCount;
};

#endif // MYLIST_H
