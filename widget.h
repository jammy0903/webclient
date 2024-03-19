#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include<QTcpSocket>
#include<QSslSocket>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //QTcpSocket Socket_;

    // here we code start
    //widget class's memeber varient

    QSslSocket Socket_;
    //QUdpSocket Socket_;

public slots:
    //socket connect body fuction
    void doConnected();
    //disconnected body finction
    void doDisconnected();
    //disconnected body finction
    void doReadyRead();

private slots:
    void on_pb_connect_clicked();

    void on_pb_disconect_clicked();

    void on_pbSend_clicked();

    void on_pb_2_clicked();

    void on_pb_Clear_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
