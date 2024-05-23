#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QWidget>
#include "../entities/user.h"

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserWindow(const int& user_id, const int& edited_user_id, QWidget *parent = nullptr);
    void validate();
    void validate(const QString& name, const QString& login, const QString& password, const UserRole& role);
    bool check_changes(const QString& name, const QString& login, const QString& password, const UserRole& role);
    void update(const QString& name, const QString& login, const QString& password, const UserRole& role);
    ~EditUserWindow();

private slots:
    void on_go_area_button_clicked();

    void on_add_button_clicked();

private:
    Ui::EditUserWindow *ui;
    const int mUser_id;
    const QSharedPointer<UserSql> mEdited_user;
};

#endif // EDITUSERWINDOW_H
