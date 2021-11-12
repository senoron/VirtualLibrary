#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDialog>
#include "mylist.h"
#include <QLineEdit>

namespace Ui {
class AddForm;
}

class AddForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddForm(MyList *list);
    ~AddForm();
signals:
    void fillIn();

private slots:

    void on_CloseButton_released();

    void on_AddButton_released();

    void on_AuthorEdit_textChanged(const QString &arg1);


private:
    Ui::AddForm *ui;
    MyList *List;

    QLineEdit *currentEdit;
};

#endif // ADDFORM_H
