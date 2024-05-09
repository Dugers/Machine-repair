#ifndef ADMINAREAWINDOW_H
#define ADMINAREAWINDOW_H

#include <QWidget>

namespace Ui {
class AdminAreaWindow;
}

class AdminAreaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminAreaWindow(const int& id, QWidget *parent = nullptr);
    ~AdminAreaWindow();

private slots:
    void on_add_user_button_clicked();

    void on_edit_user_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::AdminAreaWindow *ui;
    const int mUser_id;
};

#endif // ADMINAREAWINDOW_H
