#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>
#include <QDataStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::connectClicked(){
    if(ui->localPortLine->text().isEmpty() ||
            ui->remotePortLine->text().isEmpty()){
        QMessageBox::warning(this, "Внимание!", "Не указаны порты, введите необходимую информацию");
        return;
    }

    int localPort = ui->localPortLine->text().toInt();
    int remotePort = ui->remotePortLine->text().toInt();
    emit portsReceived(localPort, remotePort);
}

void MainWindow::disconnectClicked(){
    emit closeConnection();
     ui->connectButton->setEnabled(true);
}

void MainWindow::sendClicked(){
    if(ui->connectButton->isEnabled()){
        QMessageBox::warning(this, "Внимание!", "Соединение не установлено, нажмите <Подключить>");
        return;
    }

    QString message = ui->messageLine->text();
    emit messageTextReceived(message);
    ui->messageTextBrowser->append(message);
    ui->messageLine->clear();
}

void MainWindow::processNewMessage(QString message){
    ui->messageTextBrowser->append(message);
}

void MainWindow::blockConnectButton(){
    ui->connectButton->setEnabled(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}

