#include "service.h"

Duration::Duration(const unsigned int& months, const unsigned int& days, const unsigned int& hours, const unsigned int& minutes) :
    mMonths{months},
    mDays{days},
    mHours{hours},
    mMinutes{minutes}
{
    if (months > 11 || days > 30 || hours > 24 || minutes > 60)
        throw std::invalid_argument{"You can point out only months <= 11, days <= 30, hours <= 24, minutes <= 60"};
}
void Duration::set_months(const int& months) {
    mMonths = months;
}

void Duration::set_days(const int& days) {
    mDays = days;
}

void Duration::set_hours(const int& hours) {
    mHours = hours;
}

void Duration::set_minutes(const int& minutes) {
    mMinutes = minutes;
}

const unsigned int& Duration::months() const {
    return mMonths;
}
const unsigned int& Duration::days() const {
    return mDays;
}
const unsigned int& Duration::hours() const {
    return mHours;
}
const unsigned int& Duration::minutes() const {
    return mMinutes;
}
const QString Duration::months_str() const { // i18n?
    QString answer = QString::number(mMonths) + " ";
    if (mMonths == 1)
        answer += "месяц";
    else if (mMonths >= 2 && mMonths <= 4)
        answer += "месяца";
    else
        answer += "месяцев";
    return answer;
}
const QString Duration::days_str() const {
    QString answer = QString::number(mDays) + " ";
    int day_ost = mDays % 10;
    if (day_ost == 1)
        answer += "день";
    else if ((mDays < 10 || mDays > 20) && day_ost >= 2 && day_ost <= 4)
        answer += "дня";
    else
        answer += "дней";
    return answer;
}
const QString Duration::hours_str() const {
    QString answer = QString::number(mHours) + " ";
    if (mHours == 1 || mHours == 21)
        answer += "час";
    else if ((mHours >= 5 && mHours <= 20) || mHours == 0)
        answer += "часов";
    else
        answer += "часа";
    return answer;
}
const QString Duration::minutes_str() const {
    QString answer = QString::number(mMinutes) + " ";
    int minutes_ost = mMinutes % 10;
    if (minutes_ost == 1)
        answer += "минута";
    else if ((mMinutes < 10 || mMinutes > 20) && minutes_ost >= 2 && minutes_ost <= 4)
        answer += "минуты";
    else
        answer += "минут";
    return answer;
}
Duration::operator QString() const {
    QString answer;
    if (mMonths) {
        answer = this->months_str();
        if (mDays || mHours || mMinutes)
            answer += " ";
    }
    if (mDays) {
        answer += this->days_str();
        if (mHours || mMinutes)
            answer += " ";
    }
    if (mHours) {
        answer += this->hours_str();
        if (mMinutes)
            answer += " ";
    }
    if (mMinutes) {
        answer += this->minutes_str();
    }
    if (!answer.size())
        answer = "Моментально";
    return answer;
}


Service::Service(const QString& name, const Duration& duration, const double& price) : mName{name}, mDuration{duration}, mPrice{price} {}
Service::Service(QString&& name, Duration&& duration, double&& price) noexcept : mName{std::move(name)}, mDuration{std::move(duration)}, mPrice{std::move(price)} {}
void Service::set_name(const QString& name) {
    mName = name;
}
void Service::set_name(QString&& name) noexcept {
    mName = std::move(name);
}
void Service::set_duration(const Duration& duration) {
    mDuration = duration;
}
void Service::set_duration(Duration&& duration) noexcept {
    mDuration = std::move(duration);
}
const QString& Service::name() const {
    return mName;
}
const Duration& Service::durtaion() const {
    return mDuration;
}

void Service::set_price(const double& price) {
    mPrice = price;
}
void Service::set_price(double&& price) noexcept {
    mPrice = std::move(price);
}

const double& Service::price() const {
    return mPrice;
}
