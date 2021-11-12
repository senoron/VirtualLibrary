#ifndef EDITFORM_H
#define EDITFORM_H

#include <QDialog>
#include "mylist.h"

namespace Ui {
class EditForm;
}

class EditForm : public QDialog
{
    Q_OBJECT

public:
    explicit EditForm(MyListItem *item);
    ~EditForm();

signals:
    void fillIn();

private slots:
    void on_EditButton_released();

    void on_CloseButton_released();

    void on_AuthorEdit_textChanged(const QString &arg1);

private:
    Ui::EditForm *ui;
    MyListItem *item;
};

#endif // EDITFORM_H
