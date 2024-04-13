#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

signals:
    void authClosed(int id);

private slots:
    void on_authEnterButton_clicked();

    void on_registrationButton_clicked();

    void reject();


private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
