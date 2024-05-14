#ifndef MESSAGES_H
#define MESSAGES_H

#include <exception>
#include <QString>
#include <QWidget>

void show_error(std::exception& e, QWidget* parrent = nullptr);
void show_info(const QString& text, bool is_modal = false, QWidget* parrent = nullptr);

#endif // MESSAGES_H
