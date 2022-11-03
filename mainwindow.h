#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <net.h>
#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setNetwork(NetManager* network);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void connectClicked();
    void disconnectClicked();
    void sendClicked();

public slots:
    void blockConnectButton();
    void processNewMessage(QString message);

signals:
    void portsReceived(int localPort, int remotePort);
    void messageTextReceived(QString message);
    void closeConnection();
};
#endif // MAINWINDOW_H
