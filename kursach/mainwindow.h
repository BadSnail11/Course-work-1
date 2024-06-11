#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <classes.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Array <Order> orders;
    Array <Passage> passages;
    Array <Transport> transports;
    Array <Account> accounts;
    Account currentAccount;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool stringIsOkay(QString s);

    bool numberIsOkay(QString s);

    bool dateIsOkay(QString s);

    void on_plus_clicked(QString idx, int id);

    void on_minus_clicked(QString idx, int id);

public slots:
    void on_auth_closed(int id);

private slots:
    void on_ordersButton_clicked();

    void on_passagesButton_clicked();

    void on_transportsButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_order_change_accepted();

    void on_passage_change_accepted();

    void on_transport_change_accepted();

    void on_account_change_accepted();

    void on_addButton_clicked();

    void on_deleteButton_clicked(QString type, int id);

    void on_sortOBox_activated(int index);

    void on_sortTBox_activated(int index);

    void on_sortPBox_activated(int index);

    void on_orderButton_clicked();

    void on_accountsButton_clicked();

    void on_logoutButton_clicked();

    void on_findButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
