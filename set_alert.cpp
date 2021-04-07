#include "set_alert.h"
#include "ui_set_alert.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QRandomGenerator>
#include <QMessageBox>




Set_Alert::Set_Alert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_Alert)
{
    ui->setupUi(this);
}

Set_Alert::~Set_Alert()
{
    delete ui;

}

void Set_Alert::on_pushButton_clicked()
{

    QString cur_name;
    QString price_alert;

    cur_name= ui->plainTextEdit->toPlainText();
    price_alert= ui->plainTextEdit_2->toPlainText();

    quint32 Alert_ID=QRandomGenerator::global()->generate();                                //create ID for alarm

    QFile write_symbols(QDir::currentPath()+"/Alerts/"+"AlertID.txt");
    write_symbols.open(QFile::WriteOnly|QIODevice::Text|QFile::Append);


    QTextStream out(&write_symbols);
    out<<Alert_ID<<Qt::endl;

    write_symbols.close();


    QFile write_file(QDir::currentPath()+"/Alerts/"+QString::number(Alert_ID)+".txt");
    write_file.open(QFile::WriteOnly|QIODevice::Text|QFile::Append);

    QTextStream out1(&write_file);
    out1<<cur_name<<Qt::endl;
    out1<<price_alert<<Qt::endl;
    write_file.write(ui->comboBox->currentText().toUtf8());


    if(write_file.isOpen()){
    QMessageBox *message=new QMessageBox;
    message->setText("هشدار فعال شد.");
    message->exec();
}


    write_file.close();

    Set_Alert::close();


}



