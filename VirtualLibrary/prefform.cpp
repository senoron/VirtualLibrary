#include "prefform.h"
#include "ui_prefform.h"
#include "warningform.h"

PrefForm::PrefForm(bool *isCheked) :
    QDialog(),
    ui(new Ui::PrefForm)
{
    ui->setupUi(this);
    if(*isCheked){
        ui->checkBox->setChecked(true);
    }else{
        ui->checkBox->setChecked(false);
    }

    update = isCheked;

    this->setWindowTitle("Preferences");
}

PrefForm::~PrefForm()
{
    delete ui;
}

void PrefForm::on_OkButton_released()
{
    if(ui->checkBox->isChecked())
    {
        qDebug() << "true";
        (*update) = true;
    }else{
        qDebug() << "false";
       (*update) = false;
    }
    accept();
}

void PrefForm::on_pushButton_released()
{
    emit deleteAll();
}
