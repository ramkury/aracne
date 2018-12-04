#ifndef ARACNEWINDOW_H
#define ARACNEWINDOW_H

#include <QMainWindow>
#include <cstdint>
#include "BrowserSocket.h"
#include "InternetSocket.h"

#define BUFFER_SIZE (1024 * 1024)

namespace Ui {
class AracneWindow;
}

class AracneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AracneWindow(uint16_t browserPort, QWidget *parent = nullptr);
    ~AracneWindow();

private slots:
    void on_btnSendRequest_clicked();

    void on_btnSendResponse_clicked();

private:
    Ui::AracneWindow *ui;
    aracne::BrowserSocket browserSocket;
    aracne::InternetSocket internetSocket;
    aracne::HttpRequest request;
    int response_size = 0;
    void StartProxy();
    void getRequest();
    void sendRequest();
    void sendResponse();
    char* buffer;
};

#endif // ARACNEWINDOW_H
