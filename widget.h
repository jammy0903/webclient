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
QTcpSocket Socket_;
QSslSocket SSLSocket_;

bool SSL=false;

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

    void on_pb_Clear_clicked();

    void on_SSL_select_checkbox_toggled(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
