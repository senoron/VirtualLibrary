#include "onewarningform.h"
#include "ui_onewarningform.h"

OneWarningForm::OneWarningForm(QString warningText, QString underWarningText, QString OkText, bool isError) :
    QDialog(),
    ui(new Ui::OneWarningForm)
{
    ui->setupUi(this);

    if(!isError){
        QPixmap pix("D:/code/qt/VirtualLibrary/Warning.png");
        ui->WarningIcon->setPixmap(pix);
        this->setWindowTitle("Warning");
        this->setWindowIcon(QIcon("D:/code/qt/VirtualLibrary/Warning.png"));
    }else{
        QPixmap pix("D:/code/qt/VirtualLibrary/Error.png");
        ui->WarningIcon->setPixmap(pix);
        this->setWindowTitle("Error");
        this->setWindowIcon(QIcon("D:/code/qt/VirtualLibrary/Error.png"));
    }

    this->warningText = warningText;
    this->underWarningText = underWarningText;
    this->OkText = OkText;

    ui->OkButton->setText(OkText);
    ui->WarningMainText->setText(warningText);
    ui->UnderWarningMainText->setText(underWarningText);


}

OneWarningForm::~OneWarningForm()
{
    delete ui;
}

void OneWarningForm::closeEvent(QCloseEvent *event)
{
    reject();
}

void OneWarningForm::on_OkButton_released()
{
    accept();
}
