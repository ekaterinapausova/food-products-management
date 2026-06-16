#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDate>

struct Product {
    QString batch;
    QString name;
    int quantity;
    QDate deliveryDate;
    int shelfLifeDays;
    QDate expiryDate() const { return deliveryDate.addDays(shelfLifeDays); }
};

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadData();
    void saveData();
    void refreshTable();

private slots:
    void on_addBtn_clicked();
    void on_deleteBtn_clicked();
    void on_searchBtn_clicked();
    void on_expiryBtn_clicked();
    void on_perishableBtn_clicked();
    void on_graphBtn_clicked();

private:
    Ui::MainWindow *ui;
    QList<Product> products;
    QString dbFile = "products.csv";
};

#endif // MAINWINDOW_H
