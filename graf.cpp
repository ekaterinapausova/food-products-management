#include "graf.h"
#include "ui_graf.h"
#include <QMessageBox>

graf::graf(QWidget *parent, QVector<Information> *db)
    : QDialog(parent)
    , ui(new Ui::graf)
    , database(db)
{
    ui->setupUi(this);
    this->setWindowTitle("Построение графика");
}

graf::~graf()
{
    delete ui;
}

void graf::on_buildButton_clicked()
{
    QString productName = ui->productNameEdit->text();
    if (productName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите наименование товара");
        return;
    }

    // Проверяем, существует ли товар в базе
    bool found = false;
    for (const Information &product : *database) {
        if (product.productName.compare(productName, Qt::CaseInsensitive) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Ошибка", "Товар не найден в базе данных");
        return;
    }

    emit productSelected(productName);
    close();
}

void graf::on_cancelButton_clicked()
{
    close();
}

