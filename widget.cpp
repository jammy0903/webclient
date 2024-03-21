#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{

    ui->setupUi(this);
    QObject::connect(&Socket_,&QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&Socket_,&QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&Socket_,&QAbstractSocket::readyRead,this,&Widget::doReadyRead);

    QObject::connect(&SSLSocket_,&QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&SSLSocket_,&QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&SSLSocket_,&QAbstractSocket::readyRead,this,&Widget::doReadyRead);

}


Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){

    if(SSL){ ui->pteMessage->insertPlainText("SSL connected");
    }else{  ui->pteMessage->insertPlainText("TCP connected"); }

    //연결 되면 disconnect버튼 활성화
    ui->pb_disconect->setEnabled(true);
    ui->pb_connect->setEnabled(false);
}


void Widget::doDisconnected(){
    if(SSL){
        ui->pteMessage->insertPlainText("SSL Disconnected \n");
    }else{
    ui->pteMessage->insertPlainText("TCP Disconnected \n");
    }

    //연결 되면 connect버튼 비활성화
    ui->pb_disconect->setEnabled(false);
    ui->pb_connect->setEnabled(true);
}




void Widget::doReadyRead() {
    if (SSL && SSLSocket_.state() == QAbstractSocket::ConnectedState) {
        ui->pteMessage->insertPlainText(SSLSocket_.readAll());
    } else if (Socket_.state() == QAbstractSocket::ConnectedState) {
        ui->pteMessage->insertPlainText(Socket_.readAll());
    }
}



void Widget::on_pb_connect_clicked()
{
    QString host = ui->le_Host->text();
    if (SSL) {
        qDebug() << "SSL포트로 간다443!";
        SSLSocket_.connectToHostEncrypted(host, 443);
        ui->pteMessage->insertPlainText("connecting SSL... \n");
    } else {
        qDebug() << "TCP포트로 간다!80";
        Socket_.connectToHost(host, 80);
        ui->pteMessage->insertPlainText("connecting TCP... \n");
    }
}


void Widget::on_pb_disconect_clicked()
{
    Socket_.disconnectFromHost();
    SSLSocket_.disconnectFromHost();

    ui->pb_disconect->setDefault(0);
}


void Widget::on_pbSend_clicked()
{
    //string chg to byte array!!
    if(SSL){
        SSLSocket_.write(ui->pteSend->toPlainText().toUtf8());
    }else{
        Socket_.write(ui->pteSend->toPlainText().toUtf8());
    }
}


void Widget::on_pb_Clear_clicked()
{
    ui->pteMessage->clear();
}


void Widget::on_SSL_select_checkbox_toggled(bool checked)
{
    SSL = checked;
    if (SSL) {
        ui->le_Port->setText("443"); // SSL 포트로 설정
        qDebug() << "Port set to 443 for SSL.";
    } else {
        ui->le_Port->setText("80"); // TCP 포트
    }
}

