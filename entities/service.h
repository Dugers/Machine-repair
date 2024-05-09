#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QDateTime>
#include "basesqlobject.h"
#include "relationship_wrapper.h"


class Duration
{
private:
    unsigned int mMonths;
    unsigned int mDays;
    unsigned int mHours;
    unsigned int mMinutes;
public:
    Duration(const unsigned int& months = 0, const unsigned int& days = 0, const unsigned int& hours = 0, const unsigned int& minutes = 0);
    void set_months(const int& months);
    void set_days(const int& days);
    void set_hours(const int& hours);
    void set_minutes(const int& minutes);
    const unsigned int& months() const;
    const unsigned int& days() const;
    const unsigned int& hours() const;
    const unsigned int& minutes() const;
    const QString months_str() const;
    const QString days_str() const;
    const QString hours_str() const;
    const QString minutes_str() const;
    operator QString() const;
};

class Service
{
private:
    QString mName;
    Duration mDuration;
    double mPrice;
public:
    Service(const QString& name, const Duration& duration, const double& price);
    Service(QString&& name, Duration&& duration, double&& price) noexcept;
    Service(const Service& service) = default;
    Service(Service&& service) noexcept = default;
    void set_name(const QString& name);
    void set_name(QString&& name) noexcept;
    void set_duration(const Duration& duration);
    void set_duration(Duration&& duration) noexcept;
    void set_price(const double& price);
    void set_price(double&& price) noexcept;
    const QString& name() const;
    const Duration& durtaion() const;
    const double& price() const;
    Service& operator=(const Service& service) = default;
    Service& operator=(Service&& service) noexcept = default;
};


//class ServiceSql :
//    public Service,
//    public BaseSqlObject
//{
//    ServiceSql(const int& id, const QString& name);
//    ServiceSql(const int& id, QString&& name) noexcept;
//};

#endif // SERVICE_H
