#include "mainwindow.h"
#include <net.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <chatapp.h>

int main(int argc, char *argv[])
{
    ChatApp app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Chat_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    app.showMainWindow();
    return app.exec();
}
