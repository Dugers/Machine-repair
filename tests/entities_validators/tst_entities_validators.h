#ifndef TST_ENTITIES_VALIDATORS_H
#define TST_ENTITIES_VALIDATORS_H

#include <QTest>

class entities_validators : public QObject
{
    Q_OBJECT

public:
    entities_validators();
    ~entities_validators();
private slots:
    void validate_name();
    void validate_login();
    void validate_password();
    void validate_role();
private:
};


#endif // TST_ENTITIES_VALIDATORS_H
