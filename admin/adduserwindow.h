#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QWidget>
#include "../entities/user.h"

namespace Ui {
class AddUserWindow;
}

class AddUserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddUserWindow(const int& user_id, QWidget *parent = nullptr);
    ~AddUserWindow();
    static void validate(const QString& name, const QString& login, const QString& password, const QString& role);
    static void validate_name(const QString& name);
    static void validate_login(const QString& login);
    static void validate_password(const QString& password);
    static void validate_role(const QString& role);
    static void validate_role(const UserRole& role);
    static QString generate_login(QString name);
    static QString generate_password();
    static void translit(QString& string);

private slots:
    void on_go_area_button_clicked();

    void on_add_button_clicked();

private:
    Ui::AddUserWindow *ui;
    const int mUser_id;
};

#endif // ADDUSERWINDOW_H
