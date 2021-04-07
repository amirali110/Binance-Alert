#ifndef GET_PRICE_H
#define GET_PRICE_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class Get_Price;
}

class Get_Price : public QDialog
{
    Q_OBJECT

public:
    explicit Get_Price(QWidget *parent = nullptr);
    ~Get_Price();

private slots:
    void on_pushButton_clicked();
    void fin(QNetworkReply *);

private:
    Ui::Get_Price *ui;
};

#endif // GET_PRICE_H
