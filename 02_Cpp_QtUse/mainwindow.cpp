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

    // ����Ĭ������·��
    QString downloadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    ui->downloadPathEdit->setText(downloadPath);

    updateStatus("����");
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
    // ����������������ź�
    connect(networkManager, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply *reply) {
                // ͳһ����ɴ����ڸ��Ե�slot�д���
                reply->deleteLater();
            });
}

void MainWindow::on_selectUploadFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
            this,
            "ѡ��Ҫ�ϴ����ļ�",
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
            "ѡ������Ŀ¼",
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
        updateStatus("��ѡ����Ч���ļ�", true);
        return;
    }

    if (serverUrl.isEmpty()) {
        updateStatus("�����������URL", true);
        return;
    }

    // ���ļ�
    currentFile = new QFile(filePath);
    if (!currentFile->open(QIODevice::ReadOnly)) {
        updateStatus("�޷����ļ�: " + currentFile->errorString(), true);
        delete currentFile;
        currentFile = nullptr;
        return;
    }

    // �����ಿ������:cite[2]:cite[5]
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // �ļ�����
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(QString("form-data; name=\"file\"; filename=\"%1\"")
                                        .arg(QFileInfo(filePath).fileName())));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QVariant(getMimeType(filePath)));

    currentFile->setParent(multiPart); // �ļ�����multiPart�Զ�ɾ��
    filePart.setBodyDevice(currentFile);
    multiPart->append(filePart);

    // ��ѡ�������������
    if (!ui->convertFormatEdit->text().isEmpty()) {
        QHttpPart formatPart;
        formatPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                             QVariant("form-data; name=\"format\""));
        formatPart.setBody(ui->convertFormatEdit->text().toUtf8());
        multiPart->append(formatPart);
    }

    // ��������
    QNetworkRequest request(QUrl(serverUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, "FileTransferTool/1.0");

    // ��������:cite[1]
    currentReply = networkManager->post(request, multiPart);
    multiPart->setParent(currentReply); // multiPart����reply�Զ�ɾ��

    // �����ź�
    connect(currentReply, &QNetworkReply::uploadProgress,
            this, &MainWindow::onUploadProgress);
    connect(currentReply, &QNetworkReply::finished,
            this, &MainWindow::onUploadFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &MainWindow::onNetworkError);

    updateStatus("��ʼ�ϴ��ļ�...");
    ui->uploadButton->setEnabled(false);
}

void MainWindow::on_downloadButton_clicked()
{
    QString downloadUrl = ui->downloadUrlEdit->text();
    QString savePath = ui->downloadPathEdit->text();
    QString fileName = ui->fileNameEdit->text();

    if (downloadUrl.isEmpty()) {
        updateStatus("����������URL", true);
        return;
    }

    if (savePath.isEmpty() || fileName.isEmpty()) {
        updateStatus("��ָ������·�����ļ���", true);
        return;
    }

    // ������������·��
    QString fullPath = QDir(savePath).filePath(fileName);

    // ���ļ�
    currentFile = new QFile(fullPath);
    if (!currentFile->open(QIODevice::WriteOnly)) {
        updateStatus("�޷������ļ�: " + currentFile->errorString(), true);
        delete currentFile;
        currentFile = nullptr;
        return;
    }

    // ��������:cite[2]
    QNetworkRequest request(QUrl(downloadUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, "FileTransferTool/1.0");

    // ��������
    currentReply = networkManager->get(request);

    // �����ź�
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

    updateStatus("��ʼ�����ļ�...");
    ui->downloadButton->setEnabled(false);
}

void MainWindow::on_convertButton_clicked()
{
    QString filePath = ui->uploadFileEdit->text();
    QString targetFormat = ui->convertFormatEdit->text();

    if (filePath.isEmpty() || !QFile::exists(filePath)) {
        updateStatus("��ѡ��Ҫת�����ļ�", true);
        return;
    }

    if (targetFormat.isEmpty()) {
        updateStatus("������Ŀ���ʽ", true);
        return;
    }

    // ������Ҫ����ʵ�ʵ�ת������API��ʵ��
    // ������һ��ʾ��ʵ��

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        updateStatus("�޷����ļ�", true);
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // �ļ�����
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(QString("form-data; name=\"file\"; filename=\"%1\"")
                                        .arg(QFileInfo(filePath).fileName())));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       QVariant(getMimeType(filePath)));
    filePart.setBodyDevice(&file);
    file.setParent(multiPart);
    multiPart->append(filePart);

    // ת����ʽ����
    QHttpPart formatPart;
    formatPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         QVariant("form-data; name=\"target_format\""));
    formatPart.setBody(targetFormat.toUtf8());
    multiPart->append(formatPart);

    // ʹ��ʾ��ת������URL - ��Ҫ�滻Ϊʵ�ʵ�ת������
    QNetworkRequest request(QUrl("https://api.example.com/convert"));
    currentReply = networkManager->post(request, multiPart);
    multiPart->setParent(currentReply);

    connect(currentReply, &QNetworkReply::finished,
            this, &MainWindow::onConvertFinished);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &MainWindow::onNetworkError);

    updateStatus("��ʼ�ļ�ת��...");
    ui->convertButton->setEnabled(false);
}

void MainWindow::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesSent * 100) / bytesTotal);
        ui->uploadProgress->setValue(progress);
        updateStatus(QString("�ϴ�����: %1% (%2/%3 �ֽ�)")
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
        updateStatus(QString("���ؽ���: %1% (%2/%3 �ֽ�)")
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
        updateStatus("�ϴ���ɣ���������Ӧ: " + QString(response));

        // �������ת��������һ���֣����������ﴦ����Ӧ
        QJsonDocument doc = QJsonDocument::fromJson(response);
        if (!doc.isNull()) {
            QJsonObject obj = doc.object();
            if (obj.contains("file_id")) {
                QString fileId = obj["file_id"].toString();
                // �����ļ�ID������ʹ��
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
        // ȷ��д����������
        if (currentFile) {
            currentFile->write(currentReply->readAll());
            currentFile->close();
        }
        updateStatus("������ɣ�");
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
                updateStatus("ת����ɣ�����URL���Զ����");
            } else {
                updateStatus("ת����ɣ�" + QString(response));
            }
        } else {
            updateStatus("ת����ɣ�");
        }
    }

    currentReply->deleteLater();
    currentReply = nullptr;
}

void MainWindow::onNetworkError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)

    if (currentReply) {
        updateStatus("�������: " + currentReply->errorString(), true);

        // �������ð�ť
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