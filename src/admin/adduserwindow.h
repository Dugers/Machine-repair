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
    void validate();
    static void validate(const QString& name, const QString& login, const QString& password, const QString& role);
    User prepare_data();
    static QString generate_login(QString name);

private slots:
    void on_go_area_button_clicked();

    void on_add_button_clicked();

private:
    Ui::AddUserWindow *ui;
    const int mUser_id;
};

#endif // ADDUSERWINDOW_H
