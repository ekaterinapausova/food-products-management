// information.cpp
#include "information.h"
#include "ui_information.h"
InformationDialog::InformationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::InformationDialog) {
    ui->setupUi(this);
}
void InformationDialog::setText(const QString& text) { ui->textEdit->setPlainText(text); }
