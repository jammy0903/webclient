#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Socket_.connected(); //not gen function. signal function.
    //Socket_.readyRead();
    QObject::connect(&Socket_,&QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&Socket_,&QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&Socket_,&QAbstractSocket::readyRead,this,&Widget::doReadyRead);
}


Widget::~Widget()
{
    delete ui;
}
//#################public slot area###################################
void Widget::doConnected(){
    //when we connected, this event will begin
    ui->pteMessage->insertPlainText("connected");
}
void Widget::doDisconnected(){
    //when we disconnected, this event will begin
     ui->pteMessage->insertPlainText("\nDisconnected");
}
void Widget::doReadyRead(){
    ui->pteMessage->insertPlainText(Socket_.readAll());
}






//#########################private slot area########################

void Widget::on_pb_connect_clicked()
{
    //this is TCP connecting button
    Socket_.connectToHost(ui->le_Host->text(),ui->le_Port->text().toUShort());

}


void Widget::on_pb_disconect_clicked()
{
    //we close
    //
    Socket_.disconnectFromHost();
}


void Widget::on_pbSend_clicked()
{
    //string chg to byte array!!
    Socket_.write(ui->pteSend->toPlainText().toUtf8());
}


void Widget::on_pb_Clear_clicked()
{
    ui->pteMessage->clear();
}

