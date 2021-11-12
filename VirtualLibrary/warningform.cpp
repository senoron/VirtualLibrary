#include "warningform.h"
#include "ui_warningform.h"

WarningForm::WarningForm(QString warningText, QString underWarningText, QString OkText, QString CancelText,  bool isError) :
    QDialog(),
    ui(new Ui::WarningForm)
{
    ui->setupUi(this);

    QPixmap pix("D:/code/qt/VirtualLibrary/Warning.png");
    ui->WarningIcon->setPixmap(pix);

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
    this->CancelText = CancelText;

    ui->CancelButton->setText(CancelText);
    ui->OkButton->setText(OkText);
    ui->WarningMainText->setText(warningText);
    ui->UnderWarningMainText->setText(underWarningText);

}

WarningForm::~WarningForm()
{
    delete ui;
}

void WarningForm::on_CancelButton_released()
{
    reject();
}

void WarningForm::on_OkButton_released()
{
    accept();
}

void WarningForm::closeEvent(QCloseEvent *event)
{
    reject();
    event->accept();
}
