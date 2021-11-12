#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylist.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDesktopServices>
#include "warningform.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    void fillTable();

    void closeEvent(QCloseEvent *event);

public slots:
    void fillIn();
    void deleteAll();

private slots:
    void on_OpenButton_released();
    void on_Sort_released();
    void on_AddButton_released();
    void on_EditButton_released();
    void on_SaveButton_released();
    void on_tableWidget_cellActivated(int row, int column);
    void onResult(QNetworkReply *reply);
    void onImageResult(QNetworkReply *reply);
    void on_PlayButton_released();
    void on_BooksButton_released();
    void on_DeleteButton_released();
    void on_PreferencesButton_released();



private:
    MyList List;
    bool isUpdate;
    int currentRow;
    QString currentUrl;
    QNetworkAccessManager *networkManager;
    QPushButton *currentSort;
};
#endif // MAINWINDOW_H
