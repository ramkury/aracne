#include "aracnewindow.h"
#include "ui_aracnewindow.h"
#include "HttpRequest.h"

AracneWindow::AracneWindow(uint16_t browserPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AracneWindow)
{
    ui->setupUi(this);
    browserSocket.Initialize(browserPort);
    buffer = new char[BUFFER_SIZE];
}

void AracneWindow::StartProxy()
{
    browserSocket.AwaitConnection();
    int n;
    while ((n = browserSocket.ReadRequest(buffer, BUFFER_SIZE)) < 5)
    {

    }
    buffer[n] = '\0';
    ui->textRequest->setPlainText(buffer);
}

AracneWindow::~AracneWindow()
{
    delete ui;
    delete[] buffer;
}

void AracneWindow::on_btnSendRequest_clicked()
{
    QString req_qstr = ui->textRequest->toPlainText();
    QByteArray req_data = req_qstr.toLocal8Bit();
    char * szRequest = new char[req_data.length() + 1];
    strcpy(szRequest, req_data.data());
    aracne::HttpRequest request(szRequest);
    delete[] szRequest;

    int n = internetSocket.SendRequest(request, buffer, BUFFER_SIZE);
    buffer[n] = '\0';
    ui->textResponse->setPlainText(buffer);

    //TODO move this action to when SendResponse is clicked
    browserSocket.SendResponse(buffer, n);
}
