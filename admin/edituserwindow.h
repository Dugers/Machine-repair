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
    explicit EditUserWindow(const int& user_id, const QString& edited_user_login, QWidget *parent = nullptr);
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
