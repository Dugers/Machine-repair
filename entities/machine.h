#ifndef MACHINE_H
#define MACHINE_H
#include <QString>
#include "relationship_wrapper.h"
#include "user.h"

class MachineMark {
public:
    class MachineType
    {
    private:
        QString mName;
    public:
        MachineType(const QString& name);
        MachineType(QString&& name) noexcept;
        MachineType(const MachineType& type) = default;
        MachineType(MachineType&& type) noexcept = default;
        void set_name(const QString& name);
        void set_name(QString&& name) noexcept;
        const QString& name() const;
        MachineType& operator=(const MachineType& type) = default;
        MachineType& operator=(MachineType&& type) noexcept = default;
    };
    class MachineTypeSql :
        public MachineType,
        public SqlObject
    {
    public:
        MachineTypeSql(const QString& name, const int& id);
        MachineTypeSql(QString&& name, const int& id) noexcept;
    };
    class MachineBrand {
    private:
        QString mName;
    public:
        MachineBrand(const QString& name);
        MachineBrand(QString&& name) noexcept;
        MachineBrand(const MachineBrand& brand) = default;
        MachineBrand(MachineBrand&& brand) noexcept = default;
        void set_name(const QString& name);
        void set_name(QString&& name) noexcept;
        const QString& name() const;
        MachineBrand& operator=(const MachineBrand& brand) = default;
        MachineBrand& operator=(MachineBrand&& brand) noexcept = default;
    };
    class MachineBrandSql :
        public MachineBrand,
        public SqlObject
    {
    public:
        MachineBrandSql(const QString& name, const int& id);
        MachineBrandSql(QString&& name, const int& id) noexcept;
    };
private:
    MachineType mType;
    MachineBrand mBrand;
public:
    MachineMark(const MachineType& type, const MachineBrand& brand);
    MachineMark(MachineType&& type, MachineBrand&& brand) noexcept;
    MachineMark(const MachineMark& mark) = default;
    MachineMark(MachineMark&& mark) noexcept = default;
    void set_type(const MachineType& type);
    void set_type(MachineType&& type) noexcept;
    void set_brand(const MachineBrand& brand);
    void set_brand(MachineBrand&& brand) noexcept;
    const MachineType& type() const;
    const MachineBrand& brand() const;
    MachineMark& operator=(const MachineMark& mark) = default;
    MachineMark& operator=(MachineMark&& mark) noexcept = default;
};
class MachineMarkSql :
    public MachineMark,
    public SqlObject
{
public:
    MachineMarkSql(const MachineType& type, const MachineBrand& brand, const int& id);
    MachineMarkSql(MachineType&& type, MachineBrand&& brand, const int& id) noexcept;
};

class Machine
{
private:
    QString mName;
    QSharedPointer<const User> mOwner;
    QSharedPointer<const MachineMark> mMark;
public:
    Machine(const QString& name, const QSharedPointer<const User>& owner, const QSharedPointer<const MachineMark>& mark);
    Machine(const Machine& machine) = default;
    Machine(Machine&& machine) noexcept = default;
    void set_name(const QString& name);
    void set_name(QString&& name) noexcept;
    void set_owner(const QSharedPointer<const User>& owner);
    void set_owner(QSharedPointer<const User>&& owner);
    void set_mark(const QSharedPointer<const MachineMark>& mark);
    void set_mark(QSharedPointer<const MachineMark>&& mark);
    const QSharedPointer<const MachineMark>& mark() const;
    const QSharedPointer<const User>& owner() const;
    const QString& name() const;
    Machine& operator=(const Machine& machine) = default;
    Machine& operator=(Machine&& machine) noexcept = default;
};

class MachineSql :
    public Machine,
    public SqlObject
{
public:
    MachineSql(const QString& name, const QSharedPointer<const User>& owner, const QSharedPointer<const MachineMark>& mark, const int& id);
};

#endif // MACHINE_H
