#ifndef CHATAPP_H
#define CHATAPP_H

#include <QApplication>
#include <net.h>
#include <memory>
#include <mainwindow.h>

class ChatApp : public QApplication
{
    Q_OBJECT
public:
    ChatApp(int & argc, char ** argv);
    ~ChatApp();
    void showMainWindow();

private:
    std::unique_ptr<NetManager> network;
    std::unique_ptr<MainWindow> main_window;
    QThread* net;
    void makeConnections();
};

#endif // CHATAPP_H
