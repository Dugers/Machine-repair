#include "confirmationdialog.h"
#include "ui_confirmationdialog.h"

ConfirmationDialog::ConfirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationDialog)
{
    ui->setupUi(this);
    connect(this->ui->yes_button, SIGNAL(clicked()), SLOT(accept()));
    connect(this->ui->no_button, SIGNAL(clicked()), SLOT(reject()));
    this->ui->no_button->setDefault(true);
}

ConfirmationDialog::~ConfirmationDialog()
{
    delete ui;
}

