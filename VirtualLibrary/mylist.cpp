#include "mylist.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>

MyList::MyList()
{
    this->head = nullptr;
    itemsCount = 0;
}

MyList::~MyList()
{
    free();
}

void MyList::append(MyListItem *item)
{
    MyListItem *temp = head;
    if(head == nullptr)
    {
        head = item;
        itemsCount++;
        return;
    }
    while(temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = item;
    itemsCount++;
}

void MyList::print()
{
    qDebug() << "Print Entered" << head;
    MyListItem *temp = head;
    while (temp) {
        qDebug() << temp->getAuthor() << "  " << temp->getName() << "  " << temp->getYear() << "  " << temp->getPages() << "  " << temp->getPrice();
        temp = temp->next;
    }
    qDebug() << "\n\n";
}

bool MyList::readFromFile(QString fileName)
{
    QFileInfo fi(fileName);
//    QString ext = fi.completeSuffix();
//    if(ext != "txt.TXT" && ext != "txt")
//    {
//        OneWarningForm *form = new OneWarningForm("Incorrect file format", "Choose a correct TXT format", "Ok", true);
//        form->exec();
//        delete form;
//        return false;
//    }

    QFile inFile(fileName);
    if(inFile.open(QIODevice::ReadOnly | QFile::Text))
    {
        qDebug() << inFile.size();

        QTextStream in(&inFile);
        while (!in.atEnd()){
            QString line = in.readLine();
            if((line.count(QLatin1Char(',')) != 4))
            {
                qDebug() << "incorrect format";
                continue;
            }

            QStringList elements = line.split(",");

            QString author = elements.at(0);
            QString name = elements.at(1);
            int year = elements.at(2).toInt();
            int pages = elements.at(3).toInt();
            double price = elements.at(4).toDouble();

            if(author.isEmpty() || name.isEmpty() || year <= 0 || pages <= 0 || price <= 0.0)
            {
                WarningForm *form = new WarningForm("Book incorrect format", "Сorrect the input format and try again. Continue adding correct books?", "Continue", "Cancel");
                int res = form->exec();
                if(res == QDialog::Accepted)
                {
                    continue;
                }else{
                    break;
                }
                continue;
            }

            if(itemsCount > 1500)
            {
                OneWarningForm *form = new OneWarningForm("Maximum books number", "You can't open more than 1500 books", "Close", true);
                form->exec();
                delete form;
                return true;
            }

            MyListItem *item = new MyListItem(author, name, year, pages, price);
            this->append(item);
        }
        inFile.close();
    }
    else
    {
        OneWarningForm *form = new OneWarningForm("We can't open the file", "Check file format and try again", "Close", true);
        form->exec();
        delete form;
        return false;
    }
    return true;
}

MyListItem *MyList::at(int pos)
{
    MyListItem *temp = head;
    for(int i = 0; i < pos; i++)
    {
        if(!temp){return nullptr;}
        temp = temp->next;
    }
    return temp;
}

void MyList::saveToFile(QString fileName)
{
    QFileInfo fi(fileName);
//    QString ext = fi.completeSuffix();
//    if(ext != "txt.TXT" && ext != "txt")
//    {
//        OneWarningForm *form = new OneWarningForm("Incorrect file format", "Choose a correct TXT format", "Ok", true);
//        form->exec();
//        delete form;
//        return;
//    }

    QFile inFile(fileName);
    if(inFile.open(QIODevice::WriteOnly | QFile::Text))
    {
        QTextStream out(&inFile);

        MyListItem *temp = head;

        while (temp) {
            out << temp->getAuthor() << "," << temp->getName() << "," << temp->getYear() << "," <<
                   temp->getPages() << "," << temp->getPrice() << "\n";
            temp = temp->next;
        }
        inFile.close();
    }
    else
    {
        OneWarningForm *form = new OneWarningForm("We can't open the file", "Check file format and try again", "Ok", true);
        form->exec();
        delete form;
    }

}

void MyList::deletePos(int pos)
{
    if(pos < 0){return;}
    if(pos == 0)
    {
        MyListItem *temp = head;
        head = temp->next;
        delete temp;
        itemsCount--;
        return;
    }

    MyListItem *temp = head;
    MyListItem *prev = head;

    for(int i = 0; i < pos; i++)
    {
        if(!temp){return;}
        prev = temp;
        temp = temp->next;
    }

    if(!temp->next)
    {
        prev->next = nullptr;
        delete temp;
        itemsCount--;
        return;
    }
    prev->next = temp->next;
    delete temp;
    itemsCount--;
}

double comparePrice(MyListItem *one, MyListItem *two){
    return (one->getPrice()) - (two->getPrice());
}

double compareYear(MyListItem *one, MyListItem *two)
{
    return (one->getYear()) - (two->getYear());
}

double comparePages(MyListItem *one, MyListItem *two)
{
    return (one->getPages()) - (two->getPages());
}

double compareName(MyListItem *one, MyListItem *two)
{
    if(one->getName() > two->getName()){return 1;}
    else{return 0;}
}

double compareAuthor(MyListItem *one, MyListItem *two)
{
    if(one->getAuthor() > two->getAuthor()){return 1;}
    else{return 0;}
}

void MyList::sort(QString type)
{


    if(type == "Price")  {
        sortNumbers(comparePrice);
    }else if(type == "Pages")  {
        sortNumbers(comparePages);
    }else if(type == "Year")  {
        sortNumbers(compareYear);
    }else if(type == "Name")  {
        sortNumbers(compareName);
    }else if(type == "Author")  {
        sortNumbers(compareAuthor);
    }


}

void MyList::sortNumbers(double (* compare)(MyListItem *one, MyListItem *two))
{
    bool isSorted = false;
    MyListItem *temp = head;
    MyListItem *prevTemp = temp;

    if(!temp){return;}
    do{
        isSorted = false;
        temp = head;

        while(temp->next){
            if(compare(temp, temp->next) > 0)
            {
                if(temp == head)
                {
                    MyListItem *tmp = temp->next;
                    temp->next = temp->next->next;
                    tmp->next = temp;
                    head = tmp;
                }
                else
                {
                   prevTemp->next = temp->next;
                   temp->next = temp->next->next;
                   prevTemp->next->next = temp;
                }
                isSorted = true;
            }
            prevTemp = temp;
            temp = temp->next;
            if(!temp){break;}
        }
    }while(isSorted);
//    frame->hide();
}

void MyList::free()
{
    MyListItem *next = nullptr;
    MyListItem *temp = head;
    while (next) {
        next = temp->next;
        delete temp;
        temp = temp->next;
    }

    head = nullptr;
    itemsCount = 0;
}

