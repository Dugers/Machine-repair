#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include "entities/user.h"


namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();
    static QSharedPointer<QPair<int, User>> check_auth(const QString& login, const QString& password);
private slots:
    void on_auth_button_clicked();

    void on_make_dump_action_triggered();

    void on_load_dump_action_triggered();

    void on_drop_action_triggered();

    void open_user_window(UserRole role);

private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
