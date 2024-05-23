#include "weak_owner.h"

template <typename T>
weak_owner<T>::weak_owner(const int& id) : mId{id}
{

}

template <typename T>
const QSharedPointer<T>& weak_owner<T>::get() const{
    if (mObject)
        return mObject;
    mObject = T::get(mId);
    return mObject;
}



template <typename T>
void weak_owner<T>::update() {
    mObject = T::get(mId);
}
