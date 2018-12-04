#include "aracnewindow.h"
#include "ui_aracnewindow.h"
#include "HttpRequest.h"
#include "Spider.h"
#include <QtConcurrent/QtConcurrent>

AracneWindow::AracneWindow(uint16_t browserPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AracneWindow)
{
    ui->setupUi(this);
    browserSocket.Initialize(browserPort);
    buffer = new char[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    ui->btnSendRequest->setEnabled(false);
    ui->btnSendResponse->setEnabled(false);
}

void AracneWindow::StartProxy()
{
    browserSocket.AwaitConnection();
    getRequest();
}

AracneWindow::~AracneWindow()
{
    delete ui;
    delete[] buffer;
}

void AracneWindow::on_btnSendRequest_clicked()
{
    plainTextToBuffer(ui->textRequest);
    request.Parse(buffer);

    //QtConcurrent::run(this, &AracneWindow::sendRequest);
    sendRequest();
}

void AracneWindow::on_btnSendResponse_clicked()
{
    plainTextToBuffer(ui->textResponse);

    //QtConcurrent::run(this, &AracneWindow::sendResponse);
    sendResponse();
}

void AracneWindow::getRequest()
{
    ui->btnSendRequest->setEnabled(false);
    ui->btnSendResponse->setEnabled(false);
    ui->textRequest->clear();

    if (browserSocket.ReadRequest(buffer, BUFFER_SIZE) == 0)
    {
        // Browser has disconnected from socket. Wait for new connection.
        browserSocket.AwaitConnection();
        browserSocket.ReadRequest(buffer, BUFFER_SIZE);
    }

    ui->textRequest->setPlainText(buffer);
    ui->textResponse->clear();
    ui->btnSendRequest->setEnabled(true);
}

void AracneWindow::sendRequest()
{
    ui->btnSendRequest->setEnabled(false);
    response_size = internetSocket.SendRequest(request, buffer, BUFFER_SIZE);
    ui->textResponse->setPlainText(buffer);
    ui->btnSendResponse->setEnabled(true);
}

void AracneWindow::sendResponse()
{
    ui->btnSendRequest->setEnabled(false);
    ui->btnSendResponse->setEnabled(false);
    browserSocket.SendResponse(buffer, response_size);
    getRequest();
}

void AracneWindow::plainTextToBuffer(QPlainTextEdit* textEdit)
{
    QString qs_request = textEdit->toPlainText();
    qs_request = qs_request.replace("\n", "\r\n").replace("\r\r\n", "\r\n");
    QByteArray byte_arr = qs_request.toLocal8Bit();
    strcpy(buffer, byte_arr.data());
}

void AracneWindow::on_btnStartProxy_clicked()
{
    ui->btnStartProxy->setEnabled(false);
    StartProxy();
}

void AracneWindow::on_btnSpiderStart_clicked()
{
    ui->btnSpiderStart->setEnabled(false);
    ui->textSpiderContent->setPlainText("Running spider...");

    //QtConcurrent::run(this, &AracneWindow::runSpider);
    runSpider();

//    aracne::Spider sp(ui->textSpiderUrl->text().toStdString(), ui->textSpiderHost->text().toStdString());
//    sp.lstAll();
//    aracne::SpiderLst spLst = sp.showSpider();
//    spiderResult = spLst.showC();

//    ui->textSpiderContent->setPlainText(spiderResult);
//    ui->btnSpiderStart->setEnabled(true);
}

void AracneWindow::runSpider()
{
    aracne::Spider sp(ui->textSpiderUrl->text().toStdString(), ui->textSpiderHost->text().toStdString());
    sp.lstAll();
    aracne::SpiderLst spLst = sp.showSpider();
    spiderResult = spLst.showC();

    ui->textSpiderContent->setPlainText(spiderResult);
    ui->btnSpiderStart->setEnabled(true);
}
