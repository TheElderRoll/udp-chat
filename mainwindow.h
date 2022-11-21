#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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
    void reciveConAlreadyClosed();

signals:
    void portsReceived(int localPort, int remotePort);
    void messageTextReceived(QString message);
    void closeConnection();
};
#endif // MAINWINDOW_H
