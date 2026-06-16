#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add.h"
#include "search.h"
#include "information.h"
#include "draw.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    loadData();
    refreshTable();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadData() {
    products.clear();
    QFile file(dbFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList parts = in.readLine().split(',');
        if (parts.size() == 5) {
            Product p;
            p.batch = parts[0]; p.name = parts[1];
            p.quantity = parts[2].toInt();
            p.deliveryDate = QDate::fromString(parts[3], "yyyy-MM-dd");
            p.shelfLifeDays = parts[4].toInt();
            products.append(p);
        }
    }
    file.close();
}

void MainWindow::saveData() {
    QFile file(dbFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for (const auto& p : products) {
        out << p.batch << "," << p.name << "," << p.quantity << ","
            << p.deliveryDate.toString("yyyy-MM-dd") << "," << p.shelfLifeDays << "\n";
    }
    file.close();
}

void MainWindow::refreshTable() {
    ui->tableWidget->setRowCount(products.size());
    for (int i = 0; i < products.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(products[i].batch));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(products[i].name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(products[i].quantity)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(products[i].deliveryDate.toString("yyyy-MM-dd")));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(products[i].expiryDate().toString("yyyy-MM-dd")));
    }
}

void MainWindow::on_addBtn_clicked() {
    AddDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        products.append(dlg.getProduct());
        saveData(); refreshTable();
    }
}

void MainWindow::on_deleteBtn_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row >= 0) { products.removeAt(row); saveData(); refreshTable(); }
}

void MainWindow::on_searchBtn_clicked() { // Запрос 1
    SearchDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QDate from = dlg.getFromDate();
        QList<Product> filtered;
        for (const auto& p : products)
            if (p.deliveryDate >= from) filtered.append(p);

        InformationDialog info(this);
        QString text;
        if (filtered.isEmpty()) {
            // Показываем сообщение об ошибке
            QMessageBox::information(this, "Поиск завершён",
                                     "Товары с даты " + from.toString("dd.MM.yyyy") + " не найдены.");
            return; // Не показываем пустой диалог
        } else {
            text = "Товары с " + from.toString("dd.MM.yyyy") + ":\n";
            for (const auto& p : filtered)
                text += p.name + " (партия: " + p.batch + ")\n";
            info.setText(text);
            info.exec();
        }
    }
}

void MainWindow::on_expiryBtn_clicked() { // Запрос 2
    QDate today = QDate::currentDate();
    InformationDialog dlg(this);
    QString text = "Срок годности истекает сегодня:\n";
    bool found = false;
    for (const auto& p : products) {
        if (p.expiryDate() == today) { text += p.name + "\n"; found = true; }
    }
    if (!found) text += "Нет таких товаров.\n";
    dlg.setText(text); dlg.exec();
}

void MainWindow::on_perishableBtn_clicked() { // Запрос 3
    if (products.isEmpty()) return;
    int minDays = 1000000;
    QDate today = QDate::currentDate();
    for (const auto& p : products) {
        int daysLeft = p.expiryDate().daysTo(today);
        if (daysLeft < minDays) minDays = daysLeft;
    }
    InformationDialog dlg(this);
    QString text = "Самые скоропортящиеся:\n";
    for (const auto& p : products) {
        if (p.expiryDate().daysTo(today) == minDays)
            text += p.name + " (осталось: " + QString::number(minDays) + " дн.)\n";
    }
    dlg.setText(text); dlg.exec();
}

void MainWindow::on_graphBtn_clicked() { // Запрос 4
    if (products.isEmpty()) {
        QMessageBox::information(this, "График недоступен",
                                 "В базе данных нет товаров. Добавьте хотя бы один товар для построения графика.");
        return;
    }

    DrawDialog dlg(this, products);
    dlg.exec();
}
