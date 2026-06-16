#ifndef GRAF_H
#define GRAF_H

#include <QDialog>
#include <QVector>
#include "information.h"

namespace Ui {
class graf;
}

class graf : public QDialog
{
    Q_OBJECT

public:
    explicit graf(QWidget *parent = nullptr, QVector<Information> *db = nullptr);
    ~graf();

signals:
    void productSelected(const QString &productName);

private slots:
    void on_buildButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::graf *ui;
    QVector<Information> *database;
};

#endif // GRAF_H
