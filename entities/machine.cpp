#include "machine.h"

MachineMark::MachineType::MachineType(const QString& name) : mName{name} {}
MachineMark::MachineType::MachineType(QString&& name) noexcept : mName{std::move(name)} {}
void MachineMark::MachineType::set_name(const QString& name) {
    mName = name;
}
void MachineMark::MachineType::set_name(QString&& name) noexcept {
    mName = std::move(name);
}
const QString& MachineMark::MachineType::name() const {
    return mName;
}

MachineMark::MachineBrand::MachineBrand(const QString& name) : mName{name} {}
MachineMark::MachineBrand::MachineBrand(QString&& name) noexcept : mName{std::move(name)} {};
void MachineMark::MachineBrand::set_name(const QString& name) {
    mName = name;
}
void MachineMark::MachineBrand::set_name(QString&& name) noexcept {
    mName = std::move(name);
}
const QString& MachineMark::MachineBrand::name() const {
    return mName;
}

MachineMark::MachineMark(const relationship_wrapper<MachineType>& type, const relationship_wrapper<MachineBrand>& brand) : mType{type}, mBrand{brand} {}
MachineMark::MachineMark(relationship_wrapper<MachineType>&& type, relationship_wrapper<MachineBrand>&& brand) noexcept : mType{std::move(type)}, mBrand{std::move(brand)} {};
void MachineMark::set_type(const relationship_wrapper<MachineType>& type) {
    mType = type;
}
void MachineMark::set_type(relationship_wrapper<MachineType>&& type) noexcept {
    mType = std::move(type);
}
void MachineMark::set_brand(const relationship_wrapper<MachineBrand>& brand) {
    mBrand = brand;
}
void MachineMark::set_brand(relationship_wrapper<MachineBrand>&& brand) noexcept {
    mBrand = std::move(brand);
}
const relationship_wrapper<MachineMark::MachineType>& MachineMark::type() const {
    return mType;
}
const relationship_wrapper<MachineMark::MachineBrand>& MachineMark::brand() const {
    return mBrand;
}


Machine::Machine(const QString& name, const relationship_wrapper<const User>& owner, const relationship_wrapper<const MachineMark>& mark) :
    mName{name}, mOwner{owner}, mMark{mark} {}
void Machine::set_name(const QString& name) {
    mName = name;
}
void Machine::set_name(QString&& name) noexcept {
    mName = std::move(name);
}
void Machine::set_owner(const relationship_wrapper<const User>& owner) {
    mOwner = owner;
}
void Machine::set_owner(relationship_wrapper<const User>&& owner) {
    mOwner = std::move(owner);
}
void Machine::set_mark(const relationship_wrapper<const MachineMark>& mark) {
    mMark = mark;
}
void Machine::set_mark(relationship_wrapper<const MachineMark>&& mark) {
    mMark = std::move(mark);
}
const relationship_wrapper<const MachineMark>& Machine::mark() const {
    return mMark;
}
const relationship_wrapper<const User>& Machine::owner() const {
    return mOwner;
}
const QString& Machine::name() const {
    return mName;
}

// ============================== SQL TYPES ==============================

MachineMark::MachineTypeSql::MachineTypeSql(const QString& name, const int& id) :
    MachineType{name}, SqlObject{id} {}
MachineMark::MachineTypeSql::MachineTypeSql(QString&& name, const int& id) noexcept :
    MachineType{std::move(name)}, SqlObject{std::move(id)} {}

MachineMark::MachineBrandSql::MachineBrandSql(const QString& name, const int& id) :
    MachineBrand{name}, SqlObject{id} {}
MachineMark::MachineBrandSql::MachineBrandSql(QString&& name, const int& id) noexcept :
    MachineBrand{std::move(name)}, SqlObject{std::move(id)} {}

MachineMarkSql::MachineMarkSql(const relationship_wrapper<MachineType>& type, const relationship_wrapper<MachineBrand>& brand, const int& id) :
    MachineMark{type, brand}, SqlObject{id} {}
MachineMarkSql::MachineMarkSql(relationship_wrapper<MachineType>&& type, relationship_wrapper<MachineBrand>&& brand, const int& id) noexcept :
    MachineMark{std::move(type), std::move(brand)}, SqlObject{std::move(id)} {}

MachineSql::MachineSql(const QString& name, const relationship_wrapper<const User>& owner, const relationship_wrapper<const MachineMark>& mark, const int& id) :
    Machine{name, owner, mark}, SqlObject{id} {}
