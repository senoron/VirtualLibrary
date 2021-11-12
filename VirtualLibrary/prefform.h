#ifndef PREFFORM_H
#define PREFFORM_H

#include <QDialog>

namespace Ui {
class PrefForm;
}

class PrefForm : public QDialog
{
    Q_OBJECT

public:
    explicit PrefForm(bool *isCheked);
    ~PrefForm();
signals:
    void deleteAll();

private slots:
    void on_OkButton_released();
    void on_pushButton_released();

private:
    Ui::PrefForm *ui;

    bool *update;
};

#endif // PREFFORM_H
