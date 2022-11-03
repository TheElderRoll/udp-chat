#include "net.h"
#include <QUdpSocket>
#include <QDataStream>
#include <thread>
#include <QtDebug>
#include <QThread>
NetManager::NetManager():QObject(){}

void NetManager::initConnection(int localPort, int remotePort){
    this->socket = new QUdpSocket(this);
    this->socket->bind(QHostAddress::Any, localPort);
    connect(socket, &QUdpSocket::readyRead, this, &NetManager::read);
    this->remotePort = remotePort;
    qDebug()<<QThread::currentThreadId();
    emit socketCreated();
}

void NetManager::sendMessage(QString message){
    socket->writeDatagram(message.toUtf8(), QHostAddress::LocalHost, this->remotePort);
}

void NetManager::read(){
    QHostAddress sender;
    quint16 senderPort;

    while(socket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        this->messageStory.push_back(QString(datagram));
        emit newMessage(datagram);
    }
}

void NetManager::closeSocket(){
    this->socket->close();
    delete socket;
}

void NetManager::setRemotePort(int remotePort){
    this->remotePort = remotePort;
}

NetManager::~NetManager(){
    delete socket;
}
