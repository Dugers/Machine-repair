#ifndef MESSAGES_H
#define MESSAGES_H

#include <exception>
#include <QString>
#include <QWidget>
#include <functional>
#include "permissioncontroller.h"

#ifndef ERROR_CHECK_BEGIN
    #define ERROR_CHECK_BEGIN try {
#endif
#ifndef ERROR_CHECK_END
    #define ERROR_CHECK_END(window)                     \
}                                                       \
catch (permission_error e) {                            \
    show_error(e);                                      \
    window->close();                                    \
    open_window(new AuthWindow, window);                \
}                                                       \
catch (std::exception& e) {                             \
    show_error(e, window);                              \
}
#endif

void show_error(std::exception& e, QWidget* window = nullptr);
void show_error(const char* e, QWidget* window = nullptr);
void show_info(const QString& text, bool is_modal = false, QWidget* window = nullptr);
bool show_confirm(QWidget* parent);
void open_window(QWidget* new_window, QWidget* current_window);

#endif // MESSAGES_H
