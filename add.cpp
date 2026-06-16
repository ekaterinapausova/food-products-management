#include "add.h"
#include "ui_add.h"
#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddDialog) {
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

// Проверка перед закрытием окна
void AddDialog::accept() {
    if (ui->batchEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите номер партии!");
        ui->batchEdit->setFocus();
        return;
    }
    if (ui->nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите наименование товара!");
        ui->nameEdit->setFocus();
        return;
    }
    if (ui->qtySpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Количество должно быть больше нуля!");
        ui->qtySpin->setFocus();
        return;
    }
    if (ui->lifeSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Срок годности должен быть больше нуля!");
        ui->lifeSpin->setFocus();
        return;
    }

    // Если всё ОК, закрываем диалог с кодом Accepted
    QDialog::accept();
}

Product AddDialog::getProduct() {
    Product p;
    p.batch = ui->batchEdit->text().trimmed();
    p.name = ui->nameEdit->text().trimmed();
    p.quantity = ui->qtySpin->value();
    p.deliveryDate = ui->dateEdit->date();
    p.shelfLifeDays = ui->lifeSpin->value();
    return p;
}
