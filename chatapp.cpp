#include "chatapp.h"
#include <QThread>

ChatApp::ChatApp(int & argc, char ** argv):QApplication(argc, argv){
    this->network = std::make_unique<NetManager>();
    this->main_window = std::make_unique<MainWindow>();

    this->net = new QThread;
    this->network->moveToThread(net);
    connect(main_window.get(), &MainWindow::portsReceived, network.get(), &NetManager::initConnection, Qt::QueuedConnection);
    connect(main_window.get(), &MainWindow::messageTextReceived, network.get(), &NetManager::sendMessage, Qt::QueuedConnection);
    connect(network.get(), &NetManager::socketCreated, main_window.get(),&MainWindow::blockConnectButton, Qt::QueuedConnection);
    connect(network.get(), &NetManager::newMessage, main_window.get(),&MainWindow::processNewMessage, Qt::QueuedConnection);
    connect(main_window.get(), &MainWindow::closeConnection, network.get(), &NetManager::closeSocket, Qt::QueuedConnection);
    net->start();
}

void ChatApp::showMainWindow(){
    this->main_window->show();
}

ChatApp::~ChatApp(){
    this->net->quit();
    if(!this->net->wait(50)){
        this->net->terminate();
    }
    delete net;
}
