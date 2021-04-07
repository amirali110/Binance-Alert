#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "get_price.h"
#include "ui_get_price.h"
#include "set_alert.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QMediaPlayer>
#include <QInputDialog>





QString MainWindow::req(QString symbol1){

    QEventLoop event;
    QNetworkAccessManager acc;
    QNetworkRequest req ;

    QString url="https://api3.binance.com/api/v3/ticker/price?symbol="+symbol1;

    req.setUrl(QUrl(url));
    QNetworkReply *rep=acc.get(req);                   //Send Request
    QObject::connect(rep,&QNetworkReply::finished,&event,&QEventLoop::quit);
    event.exec();

    QJsonDocument doc=QJsonDocument::fromJson(rep->readAll());
    QJsonObject obj=doc.object();
    return obj.value("price").toString();


}



MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    MainWindow::setWindowTitle("Binance_Alert");
    MainWindow::setWindowIcon(QIcon(QDir::currentPath()+"/binance.png"));

    QFile read_time(QDir::currentPath()+"/time.txt");                           //read update time from file
    read_time.open(QFile::ReadOnly);

    int time=(read_time.readLine().toInt())*1000;                             //convert to milisecond


  QTimer *timer = new QTimer(this);

  connect(timer,&QTimer::timeout,this,[=](){

      QFile read_AlertID(QDir::currentPath()+"/Alerts/"+"AlertID.txt");                        //read alert id from file
      read_AlertID.open(QFile::ReadOnly|QFile::Text);


      while(read_AlertID.atEnd()!=true){

          QString ID=read_AlertID.readLine();
          ID.remove('\n');


          QFile read_price(QDir::currentPath()+"/Alerts"+"/"+ID+".txt");                   //opne alarm file to read alarm Specifications
          read_price.open(QFile::ReadOnly|QFile::Text);


           if(read_price.isOpen()){

          QString symbol_alert=read_price.readLine();
          symbol_alert.remove('\n');

          QString price_alert=read_price.readLine();
          QString type=read_price.readLine();
          QString price_live=req(symbol_alert);


         if(type=="صعودی"){

             if(price_live.toDouble()>=price_alert.toDouble()){

                 QMediaPlayer *player=new QMediaPlayer;
                 player->setMedia(QUrl(QDir::currentPath()+"/Media/music.mp3"));
                 player->setVolume(50);
                 player->play();


                 QMessageBox *message=new QMessageBox;
                 message->setText("نماد "+symbol_alert + "بالاتر از قیمت "+price_alert+ "قرار گرفت."+'\n'+"قیمت کنونی برابر "+price_live+ "می باشد.");
                 message->exec();

                 read_price.close();

                 if(message->clickedButton()){
                     player->stop();
                    QFile::remove(QDir::currentPath()+"/Alerts/"+ID+".txt");
                 }

             }
         }

         else if(type=="نزولی"){

             if(price_live.toDouble()<=price_alert.toDouble()){


                 QMediaPlayer *player=new QMediaPlayer;
                 player->setMedia(QUrl(QDir::currentPath()+"/Media/music.mp3"));
                 player->setVolume(50);
                 player->play();


                 QMessageBox *message=new QMessageBox;
                 message->setText("نماد "+symbol_alert + "پایینتر از قیمت "+price_alert+ "قرار گرفت."+'\n'+"قیمت کنونی برابر "+price_live+ "می باشد.");
                 message->exec();

                 read_price.close();

                 if(message->clickedButton()){

                     player->stop();
                     QFile::remove(QDir::currentPath()+"/Alerts/"+ID+".txt");

                 }
             }
         }
           }
      }

  });




timer->start(time);             //start timer


}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    Get_Price *get=new Get_Price;
    get->exec();

}


void MainWindow::on_pushButton_3_clicked()
{

    Set_Alert *alert_window=new Set_Alert;
    alert_window->exec();

}

void MainWindow::on_pushButton_4_clicked()
{

    QInputDialog *dialog=new QInputDialog;
    QString time=dialog->getText(this,tr("تنظیم زمان"),tr("لطفا زمان مدنظر خود را جهت به روز شدن قیمت ها وارد کنید.(ثانیه)"));

    QFile write_time(QDir::currentPath()+"/time.txt");
    write_time.open(QFile::WriteOnly);

    write_time.write(time.toUtf8());

    write_time.close();


}




