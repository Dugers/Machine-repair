#ifndef WEAK_OWNER_H
#define WEAK_OWNER_H

#include <QSharedPointer>

template <typename T>
class weak_owner
{
private:
    const int& mId;
    QSharedPointer<T> mObject;
public:
    weak_owner(const int& id);
    const QSharedPointer<T>& get() const;
    void update();
};

#endif // WEAK_OWNER_H
