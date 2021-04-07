#include "get_price.h"
#include "ui_get_price.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>


void Get_Price::fin(QNetworkReply *reply){

    QByteArray byte=reply->readAll();
    QJsonDocument doc=QJsonDocument::fromJson(byte);

    QJsonObject obj =doc.object();
    QJsonValue val;

    val=obj.value("symbol");
    QString symbol="Symbol: "+val.toString();

    val=obj.value("price");
    QString price ="Price: "+val.toString();

    QDateTime d;

    ui->textBrowser->append(symbol);
    ui->textBrowser->append(price);
    ui->textBrowser->append(d.currentDateTime().toString());
    ui->textBrowser->append("---------------------------------------");

}
Get_Price::Get_Price(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Get_Price)
{
    ui->setupUi(this);

    ui->textBrowser->setFontWeight(15);
    ui->textBrowser->setFontPointSize(15);
}


Get_Price::~Get_Price()
{
    delete ui;
}


void Get_Price::on_pushButton_clicked()
{

    QString currency_Url;

    currency_Url="https://api3.binance.com/api/v3/ticker/price?symbol="+ui->plainTextEdit->toPlainText();

    QNetworkAccessManager *acc_man=new QNetworkAccessManager(this);

    connect(acc_man,&QNetworkAccessManager::finished,this,&Get_Price::fin);

    const QUrl main_url=QUrl(currency_Url);

    QNetworkRequest req;
    req.setUrl(main_url);


    acc_man->get(req);                  //send request

}




