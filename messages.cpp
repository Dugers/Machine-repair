#include "messages.h"
#include <QMessageBox>


void show_error(std::exception& e, QWidget* parrent) {
    QMessageBox msg_box;
    msg_box.setText(e.what());
    msg_box.setIcon(QMessageBox::Critical);
    msg_box.exec();
}


void show_info(const QString& text, bool is_modal, QWidget* parrent) {
    QMessageBox msg_box;
    msg_box.setText("Данные успешно сохранены");
    msg_box.setIcon(QMessageBox::Information);
    msg_box.exec();
}
