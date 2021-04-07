#ifndef SET_ALERT_H
#define SET_ALERT_H

#include <QDialog>

namespace Ui {
class Set_Alert;
}

class Set_Alert : public QDialog
{
    Q_OBJECT

public:
    explicit Set_Alert(QWidget *parent = nullptr);
    ~Set_Alert();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Set_Alert *ui;
};

#endif // SET_ALERT_H
