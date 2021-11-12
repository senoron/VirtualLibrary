#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(MyList *list):
    QDialog(),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
    this->List = list;

    ui->Error->hide();

    ui->AuthorEdit->setPlaceholderText("Miguel de Cervantes");
    ui->NameEdit->setPlaceholderText("Don Quixote");
    ui->YearEdit->setPlaceholderText("1998");
    ui->PagesEdit->setPlaceholderText("942");
    ui->PriceEdit->setPlaceholderText("125.49");
    this->setFocus();

    connect(ui->AuthorEdit, SIGNAL(textChanged(QString)), this, SLOT(on_AuthorEdit_textChanged(QString)));
    connect(ui->NameEdit, SIGNAL(textChanged(QString)), this, SLOT(on_AuthorEdit_textChanged(QString)));
    connect(ui->YearEdit, SIGNAL(textChanged(QString)), this, SLOT(on_AuthorEdit_textChanged(QString)));
    connect(ui->PagesEdit, SIGNAL(textChanged(QString)), this, SLOT(on_AuthorEdit_textChanged(QString)));
    connect(ui->PriceEdit, SIGNAL(textChanged(QString)), this, SLOT(on_AuthorEdit_textChanged(QString)));

}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::on_CloseButton_released()
{
    this->reject();
}

void AddForm::on_AddButton_released()
{
    QString Author = ui->AuthorEdit->text();
    QString Name = ui->NameEdit->text();

    int Year = 0;
    int Pages = 0;
    double Price = 0.0;
    Year = ui->YearEdit->text().toInt();
    Pages = ui->PagesEdit->text().toInt();
    Price = ui->PriceEdit->text().toDouble();


    if(Author.isEmpty()){ui->AuthorEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #983636;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");ui->Error->show();}
    else{ui->AuthorEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");}

    if(Name.isEmpty()){ui->NameEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #983636;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");ui->Error->show();}
    else{ui->NameEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");}

    if(!Year){ui->YearEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #983636;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");ui->Error->show();}
    else{ui->YearEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");}

    if(!Pages){ui->PagesEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #983636;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");ui->Error->show();}
    else{ui->PagesEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");}

    if(!Price){ui->PriceEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #983636;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");ui->Error->show();}
    else{ui->PriceEdit->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}");}

    if(!Year || !Pages || !Price || Author.isEmpty() || Name.isEmpty()){return;}

    ui->Error->hide();
    MyListItem *item = new MyListItem(Author, Name, Year, Pages, Price);
    List->append(item);

    emit fillIn();

    this->accept();
}

void AddForm::on_AuthorEdit_textChanged(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    if (line->text().isEmpty()) {
        line->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: #686767;\n	border: 2px solid;\n	border-color: #72bcd4;\n}"); // Set your color but remember that Qt will reduce alpha
    } else {
        line->setStyleSheet("QLineEdit\n{\n	background-color: rgb(56, 72, 104);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:hover\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 1px solid;\n	border-color: #858585;\n}\nQLineEdit:focus\n{\n	background-color: rgb(77, 100, 144);\n	color: white;\n	border: 2px solid;\n	border-color: #72bcd4;\n}"); // usual color
    }
}
