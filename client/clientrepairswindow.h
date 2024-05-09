#ifndef CLIENTREPAIRSWINDOW_H
#define CLIENTREPAIRSWINDOW_H

#include <QWidget>

namespace Ui {
class ClientRepairsWindow;
}

class ClientRepairsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientRepairsWindow(const int& user_id, QWidget *parent = nullptr);
    ~ClientRepairsWindow();

private slots:
    void on_go_area_button_clicked();

    void on_order_button_clicked();

    void on_repair_combo_box_currentIndexChanged(int index);

    void on_machine_combo_box_currentIndexChanged(int index);

private:
    Ui::ClientRepairsWindow *ui;
    const int mUser_id;
};

#endif // CLIENTREPAIRSWINDOW_H
