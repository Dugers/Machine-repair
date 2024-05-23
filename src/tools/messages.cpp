#include "messages.h"
#include <QMessageBox>
#include "confirmationdialog.h"


void show_error(std::exception& e, QWidget* window) {
    return show_error(e.what(), window);
}

void show_error(const char* text, QWidget* window) {
    QMessageBox msg_box{window};
    msg_box.setText(text);
    msg_box.setIcon(QMessageBox::Critical);
    msg_box.exec();
}


void show_info(const QString& text, bool is_modal, QWidget* window) {
    QMessageBox msg_box{window};
    msg_box.setText(text);
    msg_box.setIcon(QMessageBox::Information);
    msg_box.setModal(is_modal);
    msg_box.exec();
}

void open_window(QWidget* new_window, QWidget* current_window) {
    current_window->close();
    new_window->show();
}

bool show_confirm(QWidget* parent) {
    ConfirmationDialog confirm_dialog(parent);
    confirm_dialog.setModal(true);
    return confirm_dialog.exec() == QDialog::Accepted;
}
