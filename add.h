#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui { class AddDialog; }

class AddDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent = nullptr);
    Product getProduct();
    void accept() override; // Переопределяем для проверки

private:
    Ui::AddDialog *ui;
};

#endif // ADD_H
