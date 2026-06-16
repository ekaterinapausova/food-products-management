// search.cpp
#include "search.h"
#include "ui_search.h"
SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SearchDialog) {
    ui->setupUi(this); ui->dateEdit->setDate(QDate::currentDate());
}
QDate SearchDialog::getFromDate() { return ui->dateEdit->date(); }
