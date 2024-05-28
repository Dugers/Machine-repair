#ifndef TST_ENTITIES_STR_H
#define TST_ENTITIES_STR_H

#include <QtTest>

// add necessary includes here

class entities_str : public QObject
{
    Q_OBJECT

public:
    entities_str();
    ~entities_str();

private slots:
    void user_role();
    void user_str();
    void order_str();
    void machine_str();
};


#endif // TST_ENTITIES_STR_H
