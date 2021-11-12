#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addform.h"
#include "editform.h"
#include "onewarningform.h"
#include "prefform.h"
#include <QList>
#include <QDebug>
#include "mylistitem.h"
#include "mylist.h"
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    currentSort = nullptr;

    ui->HomeButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/HomeButton.png"));
    ui->HomeButton->setIconSize(QSize(49, 49));
    ui->OpenButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/OpenButton.png"));
    ui->OpenButton->setIconSize(QSize(49, 49));
    ui->AddButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/AddButton.png"));
    ui->AddButton->setIconSize(QSize(49, 49));
    ui->EditButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/EditButton.png"));
    ui->EditButton->setIconSize(QSize(49, 49));
    ui->SaveButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/SaveButton.png"));
    ui->SaveButton->setIconSize(QSize(49, 49));
    ui->PreferencesButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/PreferencesButton.png"));
    ui->PreferencesButton->setIconSize(QSize(49, 49));
    ui->DeleteButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/DeleteButton.png"));
    ui->DeleteButton->setIconSize(QSize(49, 49));
    ui->PlayButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/PlayIco.png"));
    ui->PlayButton->setIconSize(QSize(351, 101));
    ui->BooksButton->setIcon(QIcon("D:/code/qt/VirtualLibrary/BookIco.png"));
    ui->BooksButton->setIconSize(QSize(351, 101));
    ui->MainIcon->setPixmap(QPixmap("D:/code/qt/VirtualLibrary/MainIcon.png"));

    ui->PlayButton->hide();
    ui->BooksButton->hide();

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setFixedWidth(ui->tableWidget->width());

    ui->tableWidget->horizontalHeader()->resizeSection(0, 311);
    ui->tableWidget->horizontalHeader()->resizeSection(1, 361);
    ui->tableWidget->horizontalHeader()->resizeSection(2, 145);
    ui->tableWidget->horizontalHeader()->resizeSection(3, 145);
    ui->tableWidget->horizontalHeader()->resizeSection(4, 145);

    ui->tableWidget->hide();

    connect(ui->EmptyOpen, SIGNAL(released()), this, SLOT(on_OpenButton_released()));

    connect(ui->AuthorButton, SIGNAL(released()), this, SLOT(on_Sort_released()));
    connect(ui->NameButton, SIGNAL(released()), this, SLOT(on_Sort_released()));
    connect(ui->YearButton, SIGNAL(released()), this, SLOT(on_Sort_released()));
    connect(ui->PagesButton, SIGNAL(released()), this, SLOT(on_Sort_released()));
    connect(ui->PriceButton, SIGNAL(released()), this, SLOT(on_Sort_released()));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResult);

    currentRow = 0;

    //ui->image->setScaledContents(true);
    isUpdate = true;


    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(on_OpenButton_released()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this, SLOT(on_AddButton_released()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(on_SaveButton_released()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Comma), this, SLOT(on_PreferencesButton_released()));
    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(on_DeleteButton_released()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_E), this, SLOT(on_EditButton_released()));

    this->setWindowIcon(QIcon("D:/code/qt/VirtualLibrary/TitleIcon.png"));

//    ui->tableWidget->setToolTip("Double click for more info");
//    ui->tableWidget->setToolTipDuration(3000);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
}



void MainWindow::fillTable()
{
    int count = ui->tableWidget->rowCount();
    for(int i = 0; i < count; i++)
    {
        ui->tableWidget->removeRow(0);
    }

    ui->EmptyFrame->hide();
    ui->tableWidget->show();

    MyListItem *temp = List.getHead();
    int i = 0;
    while(temp) {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        for(int j = 0; j < 5; j++)
        {
            QTableWidgetItem *itm1 = new QTableWidgetItem(temp->getAuthor());
            ui->tableWidget->setItem(i, 0, itm1);
            QTableWidgetItem *itm2 = new QTableWidgetItem(temp->getName());
            ui->tableWidget->setItem(i, 1, itm2);
            QTableWidgetItem *itm3 = new QTableWidgetItem(QString::number(temp->getYear()));
            ui->tableWidget->setItem(i, 2, itm3);
            QTableWidgetItem *itm4 = new QTableWidgetItem(QString::number(temp->getPages()));
            ui->tableWidget->setItem(i, 3, itm4);
            QTableWidgetItem *itm5 = new QTableWidgetItem("₴" + QString::number(temp->getPrice()));
            ui->tableWidget->setItem(i, 4, itm5);
        }
        temp = temp->next;
        i++;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!List.count())return;

    WarningForm *form = new WarningForm("You are trying to exit without saving", "Do you want to save books?", "Save", "Close");
    int res = form->exec();
    if(res == QDialog::Accepted){
        on_SaveButton_released();
        event->accept();
    }else{event->accept();}
}

void MainWindow::fillIn()
{
    fillTable();
}

void MainWindow::deleteAll()
{
    if(!List.count()){return;}

    WarningForm *form = new WarningForm("ALL books will be deleted", "Are you sure?", "Yes", "Cancel");
    int res = form->exec();
    if(res == QDialog::Rejected)
    {
        return;
    }
    delete form;

    List.free();
    fillTable();
    ui->tableWidget->hide();
    ui->EmptyFrame->show();
    if(currentSort)currentSort->setStyleSheet("QPushButton\n{\n	border: 0px solid;\n	background:transparent;\n	color: rgb(159, 159, 159);\n}\n\nQPushButton:hover\n{\n	border: 0px solid;\n	background-color: #5C669E;\n	color: rgb(159, 159, 159);\n}");
    currentSort = nullptr;

    ui->image->hide();
    ui->AuthorInfo->hide();
    ui->PlayButton->hide();
    ui->BookInfo->hide();
    ui->BooksButton->hide();
    ui->LangInfo->hide();
    ui->WelcomeFrame->show();
}

void MainWindow::on_OpenButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file","",tr("*.txt"));
    if(fileName.isEmpty()){return;}

    bool isReaded = List.readFromFile(fileName);
//    List.print();
    if(isReaded){
        fillTable();
        ui->WelcomeFrame->hide();
    }
}

void MainWindow::on_Sort_released()
{
    QPushButton *button = (QPushButton *)sender();

    if(!List.count())
    {
        return;
    }

    QString text = button->text();

    if(currentSort)
    {
        currentSort->setStyleSheet("QPushButton\n{\n	border: 0px solid;\n	background:transparent;\n	color: rgb(159, 159, 159);\n}\n\nQPushButton:hover\n{\n	border: 0px solid;\n	background-color: #5C669E;\n	color: rgb(159, 159, 159);\n}\n\nQPushButton:pressed\n{\n	border: 0px solid;\n	background-color: rgb(83, 91, 135);\n	color: rgb(159, 159, 159);\n}");
        currentSort = button;
        button->setStyleSheet("border: 0px solid;background: #5C669E;color: white;");
    }else{
        currentSort = button;
        button->setStyleSheet("border: 0px solid;background: #5C669E;color: white;");
    }

    List.sort(text);

    fillTable();
}

void MainWindow::on_AddButton_released()
{
    AddForm *form = new AddForm(&List);
    if(List.count() > 1500)
    {
        OneWarningForm *form = new OneWarningForm("Maximum books number", "You can't open more than 1500 books", "Close", true);
        form->exec();
        delete form;
        return;
    }
    connect(form, SIGNAL(fillIn()), this, SLOT(fillIn()));
    form->exec();
    delete form;
}

void MainWindow::on_EditButton_released()
{
    if(ui->tableWidget->selectionModel()->selectedRows().size() <= 0)
    {
        OneWarningForm *form = new OneWarningForm("No books selected", "Select book and try again", "Ok");
        form->exec();
        delete form;
        return;
    }

    QList list = ui->tableWidget->selectedItems();
    if((list.length() / ui->tableWidget->columnCount()) > 1)
    {
        OneWarningForm *form = new OneWarningForm("Too many books selected", "Select only one book and try again", "Ok");
        form->exec();
        delete form;
        return;
    }

    QTableWidgetItem *item = (QTableWidgetItem *)list.at(0);

    EditForm *form = new EditForm(List.at(item->row()));
    connect(form, SIGNAL(fillIn()), this, SLOT(fillIn()));
    form->exec();
    delete form;
}

void MainWindow::on_SaveButton_released()
{
    if(!List.count()) return;

    QString fileName = QFileDialog::getSaveFileName(this, "Save file as...", "", tr("*.txt"));
    if(fileName.isEmpty()){return;}
    List.saveToFile(fileName);
}

void MainWindow::onResult(QNetworkReply *reply)
{
    qDebug() << "reply";
    if(!reply->error())
    {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();

        if(root.value("totalItems").toInt() <= 0)
        {
            QPixmap pix("D:/code/qt/VirtualLibrary/FindError.png");
            ui->image->setPixmap(pix);
            ui->AuthorInfo->clear();
            ui->LangInfo->clear();
            ui->BookInfo->setText("Please enter correct Author name and Book title.");
            ui->PlayButton->hide();
            ui->BooksButton->hide();
            return;
        }

        MyListItem *item = List.at(currentRow);

        QPixmap pix("D:/code/qt/VirtualLibrary/FindLoading.png");
        ui->image->setPixmap(pix);

        QJsonArray ja = root.value("items").toArray();
        QString link = ja.at(0).toObject().value("volumeInfo").toObject().value("imageLinks").toObject().value("smallThumbnail").toString();

        QString title = ja.at(0).toObject().value("volumeInfo").toObject().value("title").toString();
        ui->BookInfo->setText(title);

        QJsonArray authors = ja.at(0).toObject().value("volumeInfo").toObject().value("authors").toArray();
        ui->AuthorInfo->setText(authors.at(0).toString());

        QString lang = ja.at(0).toObject().value("volumeInfo").toObject().value("language").toString();
        ui->LangInfo->setText("Language: " + lang);

        int pages = ja.at(0).toObject().value("volumeInfo").toObject().value("pageCount").toInt();
        if(pages && isUpdate)item->setPages(pages);

        int year = ja.at(0).toObject().value("volumeInfo").toObject().value("publishedDate").toString().left(4).toInt();
        if(pages && isUpdate)item->setYear(year);
        qDebug() << year;

        if(ja.at(0).toObject().value("saleInfo").toObject().value("saleability").toString() == "FOR_SALE")
        {
            ui->PlayButton->show();
            ui->BooksButton->hide();
            currentUrl = ja.at(0).toObject().value("volumeInfo").toObject().value("canonicalVolumeLink").toString();

            double price = ja.at(0).toObject().value("saleInfo").toObject().value("retailPrice").toObject().value("amount").toDouble();
            if(price && isUpdate)item->setPrice(price);
        }else{
            ui->PlayButton->hide();
            ui->BooksButton->show();
            currentUrl = ja.at(0).toObject().value("volumeInfo").toObject().value("canonicalVolumeLink").toString();
        }

        fillTable();
        ui->tableWidget->selectRow(currentRow);

        QNetworkAccessManager * imageManager = new QNetworkAccessManager(this);
        connect(imageManager, &QNetworkAccessManager::finished, this, &MainWindow::onImageResult);
        QUrl url(link);
        imageManager->get(QNetworkRequest(url));

        //imageManager->deleteLater();

    }else{
        OneWarningForm *form = new OneWarningForm("Json can't be readed", reply->errorString(), "Ok");
        form->exec();
        delete form;
    }

    reply->deleteLater();
}

void MainWindow::onImageResult(QNetworkReply *reply)
{
    ui->BookInfo->show();
    ui->image->show();
    ui->LangInfo->show();
    if(!reply->error())
    {
        QByteArray jpegData = reply->readAll();
        QPixmap pix;
        pix.loadFromData(jpegData);
        ui->image->setPixmap(pix);
        ui->image->setScaledContents(true);
    }else{
        qDebug() << "Image can't be readed";
    }
}

void MainWindow::on_tableWidget_cellActivated(int row, int column)
{
    MyListItem *item = List.at(row);
    QStringList authorList = item->getAuthor().split(" ");
    QString author = authorList.at(authorList.length() - 1);
    QString name = item->getName().replace(" ", "_");
    QString link = "https://www.googleapis.com/books/v1/volumes?q=" + name.toLower() + "+inauthor:" + author.toLower() + "&key=AIzaSyAtqGnqL6qk_tKOrGsEbHvGiXjLEorQT5k";
    networkManager->get(QNetworkRequest(QUrl(link)));
    qDebug() << link;
    currentRow = row;

}

void MainWindow::on_PlayButton_released()
{
    QDesktopServices::openUrl(QUrl(currentUrl));
}

void MainWindow::on_BooksButton_released()
{
    QDesktopServices::openUrl(QUrl(currentUrl));
}

void MainWindow::on_DeleteButton_released()
{
    if(ui->tableWidget->selectionModel()->selectedRows().size() <= 0)
    {
        OneWarningForm *form = new OneWarningForm("No books selected", "Select a book and try again", "Ok");
        form->exec();
        delete form;
        return;
    }

    WarningForm *form = new WarningForm("Seleсted books will be deleted permanently", "Are you sure?", "Yes", "Canel");
    int res = form->exec();
    if(res == QDialog::Rejected)return;

    QList list = ui->tableWidget->selectedItems();

    int lenght = list.length();
    int colCount = ui->tableWidget->columnCount();

    int counter = 0;
    for (int i = 0; i < lenght; i += colCount) {
        QTableWidgetItem *item = (QTableWidgetItem *)list.at(i);
        qDebug() << item->row();
        List.deletePos(item->row() - counter);
        counter++;
    }
    fillTable();
   if(!ui->tableWidget->rowCount())
   {
       ui->EmptyFrame->show();
       ui->tableWidget->hide();
   }
}

void MainWindow::on_PreferencesButton_released()
{
    PrefForm *form = new PrefForm(&isUpdate);
    connect(form, SIGNAL(deleteAll()), this, SLOT(deleteAll()));
    form->exec();
    delete form;
}
