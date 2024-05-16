#include "addmachinewindow.h"
#include "ui_addmachinewindow.h"
#include "clientmachineswindow.h"
#include "clientareawindow.h"
#include "../models/db.h"
#include <QMessageBox>

AddMachineWindow::AddMachineWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddMachineWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    QVector<MachineMark::MachineTypeSql> types = db::get_machine_types();
    for (const MachineMark::MachineTypeSql& type : types)
        this->ui->type_combo_box->addItem(type.name(), type.id());
}

AddMachineWindow::~AddMachineWindow()
{
    delete ui;
}


void AddMachineWindow::on_add_button_clicked()
{
    QString name = this->ui->name_line_edit->text().simplified();
    int type_id = this->ui->type_combo_box->currentData().toInt();
    int brand_id = this->ui->brand_combo_box->currentData().toInt();
    try {
        this->validate(name, type_id, brand_id);
        QSharedPointer<MachineMarkSql> mark = db::get_machine_mark(type_id, brand_id);
        if (!mark) {
            db::create_machine_mark(type_id, brand_id);
            mark = db::get_machine_mark(type_id, brand_id);
        }
        if (!db::create_machine(Machine{name, nullptr, nullptr}, mUser_id, mark->id()))
            throw std::runtime_error{"Не удалось выполнить операцию, возможные причины:\n1) Проблемы с базой данных \n2) Станок с таким именем уже есть"};
        (new ClientMachinesWindow{mUser_id})->show();
        this->close();
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void AddMachineWindow::on_type_combo_box_currentIndexChanged(int index)
{
    int type_id = this->ui->type_combo_box->currentData().toInt();
    try {
        QVector<MachineMark::MachineBrandSql> brands = db::get_machine_brands(type_id);
        this->ui->brand_combo_box->clear();
        for (const MachineMark::MachineBrandSql& brand : brands)
            this->ui->brand_combo_box->addItem(brand.name(), brand.id());
        this->ui->brand_combo_box->setEnabled(true);
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void AddMachineWindow::on_go_area_button_clicked()
{
    (new ClientAreaWindow{mUser_id})->show();
    this->close();
}

void AddMachineWindow::validate(const QString& name, const int& type_id, const int& brand_id) {
    if (name.size() <= 3)
        throw std::runtime_error{"Название станка должно быть больше 3 символов"};
}

void AddMachineWindow::on_brand_combo_box_currentIndexChanged(int index)
{
    if (index == -1)
        this->ui->add_button->setEnabled(false);
    else
        this->ui->add_button->setEnabled(true);
}

