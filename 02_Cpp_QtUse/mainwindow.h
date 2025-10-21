/**
 * @Author houlijia 
 * @Date   2025-10-21 21:45
 * @Desc
**/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QProgressDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
            // 文件操作
            void on_selectUploadFile_clicked();
    void on_selectDownloadPath_clicked();

    // 网络操作
    void on_uploadButton_clicked();
    void on_downloadButton_clicked();
    void on_convertButton_clicked();

    // 网络响应
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onUploadFinished();
    void onDownloadFinished();
    void onConvertFinished();

    // 错误处理
    void onNetworkError(QNetworkReply::NetworkError error);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QNetworkReply *currentReply;
    QFile *currentFile;
    QString currentFilePath;

    void setupConnections();
    void updateStatus(const QString &message, bool isError = false);
    QString getMimeType(const QString &filePath);
};

#endif // MAINWINDOW_H