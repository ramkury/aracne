#ifndef ARACNEWINDOW_H
#define ARACNEWINDOW_H

#include <QMainWindow>

namespace Ui {
class AracneWindow;
}

class AracneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AracneWindow(QWidget *parent = nullptr);
    ~AracneWindow();

private slots:
    void on_actionSpider_triggered();

    void on_pushButton_clicked();

private:
    Ui::AracneWindow *ui;
};

#endif // ARACNEWINDOW_H
