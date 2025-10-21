/**
 * @Author houlijia 
 * @Date   2025-10-21 21:44
 * @Desc
**/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ����Ӧ�ó�����Ϣ
    QApplication::setApplicationName("File Transfer Tool");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Your Company");

    MainWindow w;
    w.show();

    return a.exec();
}