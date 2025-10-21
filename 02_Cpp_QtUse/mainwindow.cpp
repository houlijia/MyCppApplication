/**
 * @Author houlijia 
 * @Date   2025-10-21 21:43
 * @Desc
**/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QHttpPart>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , networkManager(new QNetworkAccessManager(this))
        , currentReply(nullptr)
        , currentFile(nullptr)
{
    ui->setupUi(this);
    setupConnections();

    // 设置默认下载路径
    QString downloadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    ui->downloadPathEdit->setText(downloadPath);

    updateStatus("就绪");
}

MainWindow::~MainWindow()
{
    delete ui;
    if (currentFile) {
        currentFile->deleteLater();
    }
    if (currentReply) {
        currentReply->deleteLater();
    }
}

void MainWindow::setupConnections()
{
    // 连接网络管理器的信号
    connect(networkManager, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply *reply) {
                // 统一的完成处理在各自的slot中处理
                reply->deleteLater();
            });
}

void MainWindow::on_selectUploadFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
            this,
            "选择要上传的文件",
            QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
    );

    if (!filePath.isEmpty()) {
        ui->uploadFileEdit->setText(filePath);
        currentFilePath = filePath;
    }
}

void MainWindow::on_selectDownloadPath_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
            this,
            "选择下载目录",
            QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)
    );

    if (!dirPath.isEmpty()) {
        ui->downloadPathEdit->setText(dirPath);
    }
}

void MainWindow::on_uploadButton_clicked()
{
    QString filePath = ui->uploadFileEdit->text();
    QString serverUrl = ui->serverUrlEdit->text();

    if (filePath.isEmpty() || !QFile::exists(filePath)) {
        updateStatus("请选择有效的文件", true);
        return;
    }

    if (serverUrl.isEmpty()) {
        updateStatus("请输入服务器URL", true);
        return;
    }

    // 打开文件
    currentFile = new QFile(filePath);
    if (!currentFile->open(QIODevice::ReadOnly)) {
        updateStatus("无法打开文件: " + currentFile->errorString(), true);
        delete currentFile;
        currentFile = nullptr;
        return;
    }

    // 创建多部分请求:cite[2]:cite[5]
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 文件部分
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(QString("form-data; name=\"file\"; filename=\"%1\"")
                                        .arg(QFileInfo(filePath).fileName())));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QVariant(getMimeType(filePath)));

    currentFile->setParent(multiPart); // 文件将由multiPart自动删除
    filePart.setBodyDevice(currentFile);
    multiPart->append(filePart);

    // 可选：添加其他参数
    if (!ui->convertFormatEdit->text().isEmpty()) {
        QHttpPart formatPart;
        formatPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                             QVariant("form-data; name=\"format\""));
        formatPart.setBody(ui->convertFormatEdit->text().toUtf8());
        multiPart->append(formatPart);
    }

    // 创建请求
    QNetworkRequest request(QUrl(serverUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, "FileTransferTool/1.0");

    // 发送请求:cite[1]
    currentReply = networkManager->post(request, multiPart);
    multiPart->setParent(currentReply); // multiPart将由reply自动删除

    // 连接信号
    connect(currentReply, &QNetworkReply::uploadProgress,
            this, &MainWindow::onUploadProgress);
    connect(currentReply, &QNetworkReply::finished,
            this, &MainWindow::onUploadFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &MainWindow::onNetworkError);

    updateStatus("开始上传文件...");
    ui->uploadButton->setEnabled(false);
}

void MainWindow::on_downloadButton_clicked()
{
    QString downloadUrl = ui->downloadUrlEdit->text();
    QString savePath = ui->downloadPathEdit->text();
    QString fileName = ui->fileNameEdit->text();

    if (downloadUrl.isEmpty()) {
        updateStatus("请输入下载URL", true);
        return;
    }

    if (savePath.isEmpty() || fileName.isEmpty()) {
        updateStatus("请指定保存路径和文件名", true);
        return;
    }

    // 构建完整保存路径
    QString fullPath = QDir(savePath).filePath(fileName);

    // 打开文件
    currentFile = new QFile(fullPath);
    if (!currentFile->open(QIODevice::WriteOnly)) {
        updateStatus("无法创建文件: " + currentFile->errorString(), true);
        delete currentFile;
        currentFile = nullptr;
        return;
    }

    // 创建请求:cite[2]
    QNetworkRequest request(QUrl(downloadUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, "FileTransferTool/1.0");

    // 发送请求
    currentReply = networkManager->get(request);

    // 连接信号
    connect(currentReply, &QNetworkReply::downloadProgress,
            this, &MainWindow::onDownloadProgress);
    connect(currentReply, &QNetworkReply::readyRead,
            this, [this]() {
                if (currentFile && currentReply) {
                    currentFile->write(currentReply->readAll());
                }
            });
    connect(currentReply, &QNetworkReply::finished,
            this, &MainWindow::onDownloadFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &MainWindow::onNetworkError);

    updateStatus("开始下载文件...");
    ui->downloadButton->setEnabled(false);
}

void MainWindow::on_convertButton_clicked()
{
    QString filePath = ui->uploadFileEdit->text();
    QString targetFormat = ui->convertFormatEdit->text();

    if (filePath.isEmpty() || !QFile::exists(filePath)) {
        updateStatus("请选择要转换的文件", true);
        return;
    }

    if (targetFormat.isEmpty()) {
        updateStatus("请输入目标格式", true);
        return;
    }

    // 这里需要根据实际的转换服务API来实现
    // 以下是一个示例实现

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        updateStatus("无法打开文件", true);
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 文件部分
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(QString("form-data; name=\"file\"; filename=\"%1\"")
                                        .arg(QFileInfo(filePath).fileName())));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QVariant(getMimeType(filePath)));
    filePart.setBodyDevice(&file);
    file.setParent(multiPart);
    multiPart->append(filePart);

    // 转换格式参数
    QHttpPart formatPart;
    formatPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         QVariant("form-data; name=\"target_format\""));
    formatPart.setBody(targetFormat.toUtf8());
    multiPart->append(formatPart);

    // 使用示例转换服务URL - 需要替换为实际的转换服务
    QNetworkRequest request(QUrl("https://api.example.com/convert"));
    currentReply = networkManager->post(request, multiPart);
    multiPart->setParent(currentReply);

    connect(currentReply, &QNetworkReply::finished,
            this, &MainWindow::onConvertFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &MainWindow::onNetworkError);

    updateStatus("开始文件转换...");
    ui->convertButton->setEnabled(false);
}

void MainWindow::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesSent * 100) / bytesTotal);
        ui->uploadProgress->setValue(progress);
        updateStatus(QString("上传进度: %1% (%2/%3 字节)")
                             .arg(progress)
                             .arg(bytesSent)
                             .arg(bytesTotal));
    }
}

void MainWindow::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesReceived * 100) / bytesTotal);
        ui->downloadProgress->setValue(progress);
        updateStatus(QString("下载进度: %1% (%2/%3 字节)")
                             .arg(progress)
                             .arg(bytesReceived)
                             .arg(bytesTotal));
    }
}

void MainWindow::onUploadFinished()
{
    ui->uploadButton->setEnabled(true);
    ui->uploadProgress->setValue(100);

    if (currentReply->error() == QNetworkReply::NoError) {
        QByteArray response = currentReply->readAll();
        updateStatus("上传完成！服务器响应: " + QString(response));

        // 如果这是转换操作的一部分，可以在这里处理响应
        QJsonDocument doc = QJsonDocument::fromJson(response);
        if (!doc.isNull()) {
            QJsonObject obj = doc.object();
            if (obj.contains("file_id")) {
                QString fileId = obj["file_id"].toString();
                // 保存文件ID供下载使用
            }
        }
    }

    currentReply->deleteLater();
    currentReply = nullptr;
    currentFile = nullptr;
}

void MainWindow::onDownloadFinished()
{
    ui->downloadButton->setEnabled(true);
    ui->downloadProgress->setValue(100);

    if (currentFile) {
        currentFile->close();
    }

    if (currentReply->error() == QNetworkReply::NoError) {
        // 确保写入所有数据
        if (currentFile) {
            currentFile->write(currentReply->readAll());
            currentFile->close();
        }
        updateStatus("下载完成！");
    }

    currentReply->deleteLater();
    currentReply = nullptr;
    currentFile = nullptr;
}

void MainWindow::onConvertFinished()
{
    ui->convertButton->setEnabled(true);

    if (currentReply->error() == QNetworkReply::NoError) {
        QByteArray response = currentReply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);

        if (!doc.isNull()) {
            QJsonObject obj = doc.object();
            if (obj.contains("converted_file_url")) {
                QString downloadUrl = obj["converted_file_url"].toString();
                ui->downloadUrlEdit->setText(downloadUrl);
                updateStatus("转换完成！下载URL已自动填充");
            } else {
                updateStatus("转换完成！" + QString(response));
            }
        } else {
            updateStatus("转换完成！");
        }
    }

    currentReply->deleteLater();
    currentReply = nullptr;
}

void MainWindow::onNetworkError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)

    if (currentReply) {
        updateStatus("网络错误: " + currentReply->errorString(), true);

        // 重新启用按钮
        ui->uploadButton->setEnabled(true);
        ui->downloadButton->setEnabled(true);
        ui->convertButton->setEnabled(true);

        if (currentFile) {
            currentFile->close();
            currentFile->deleteLater();
            currentFile = nullptr;
        }

        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

void MainWindow::updateStatus(const QString &message, bool isError)
{
    ui->statusLabel->setText(message);
    if (isError) {
        ui->statusLabel->setStyleSheet("color: red;");
    } else {
        ui->statusLabel->setStyleSheet("color: black;");
    }
}

QString MainWindow::getMimeType(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();

    static QHash<QString, QString> mimeTypes = {
            {"txt", "text/plain"},
            {"pdf", "application/pdf"},
            {"zip", "application/zip"},
            {"jpg", "image/jpeg"},
            {"jpeg", "image/jpeg"},
            {"png", "image/png"},
            {"doc", "application/msword"},
            {"docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"}
    };

    return mimeTypes.value(suffix, "application/octet-stream");
}