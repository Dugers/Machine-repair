#ifndef WIDGETS_H
#define WIDGETS_H
#include <QTableWidget>
#include <QVector>

#ifndef DISABLE_BUTTON
    #define DISABLE_BUTTON(button) button->setEnabled(false);
#endif

#ifndef ENABLE_BUTTON
    #define ENABLE_BUTTON(button) button->setEnabled(true);
#endif

void fill_table(QTableWidget* table, const QVector<QVector<QString>>& table_values);

#endif // WIDGETS_H
