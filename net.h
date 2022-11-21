#ifndef NET_H
#define NET_H
#include <QUdpSocket>

class NetManager: public QObject{
    Q_OBJECT

  public:
    NetManager();
    ~NetManager();
    void setRemotePort(int remotePort);

  private:
    QUdpSocket* socket;
    QVector<QString> messageStory;
    int remotePort;

  signals:
    void newMessage(QString message);
    void socketCreated();
    void connectionAlreadyClosed();

  public slots:
    void initConnection(int localPort, int remotePort);
    void sendMessage(QString message);
    void read();
    void closeSocket();
};
#endif // NET_H
