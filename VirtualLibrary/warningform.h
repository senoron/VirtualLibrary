#ifndef WARNINGFORM_H
#define WARNINGFORM_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class WarningForm;
}

class WarningForm : public QDialog
{
    Q_OBJECT

public:
    explicit WarningForm(QString warningText, QString underWarningText, QString OkText, QString CancelText,  bool isError = false);
    ~WarningForm();

    void closeEvent (QCloseEvent *event);
private slots:
    void on_CancelButton_released();
    void on_OkButton_released();

private:
    Ui::WarningForm *ui;
    QString warningText;
    QString underWarningText;
    QString OkText;
    QString CancelText;
};

#endif // WARNINGFORM_H
