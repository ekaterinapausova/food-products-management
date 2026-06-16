#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DrawDialog;
}

class DrawDialog : public QDialog {
    Q_OBJECT
public:
    explicit DrawDialog(QWidget *parent, const QList<Product>& data);
    ~DrawDialog();

private:
    Ui::DrawDialog *ui;
    QList<Product> products;
    void buildGraph();
};

#endif // DRAW_H
