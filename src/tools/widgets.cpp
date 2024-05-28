#include "widgets.h"



void fill_table(QTableWidget* table, const QVector<QVector<QString>>& table_values) {
    const qsizetype columns_count = table->columnCount();

    for (int column = 0; column < columns_count; ++column)
        table->setColumnWidth(column, table->width()/columns_count);

    if (table_values.empty()) return;

    const qsizetype rows = table_values.size();
    table->setRowCount(rows);

    for (int row = 0; row < rows; ++row) {

        if (table_values[row].size() > columns_count)
            throw std::runtime_error{"Too much columns in table_values"};

        for (int column = 0; column < table_values[row].size(); ++column)
            table->setItem(row, column, new QTableWidgetItem{table_values[row][column]});
    }
}
