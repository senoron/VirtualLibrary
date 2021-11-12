#ifndef ONEWARNINGFORM_H
#define ONEWARNINGFORM_H

#include <QDialog>
#include <QCloseEvent>


namespace Ui {
class OneWarningForm;
}

class OneWarningForm : public QDialog
{
    Q_OBJECT

public:
    explicit OneWarningForm(QString warningText, QString underWarningText, QString OkText, bool isError = false);
    ~OneWarningForm();
    void closeEvent (QCloseEvent *event);

private slots:
    void on_OkButton_released();

private:
    Ui::OneWarningForm *ui;
    QString warningText;
    QString underWarningText;
    QString OkText;
};

#endif // ONEWARNINGFORM_H
