#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDialog>

namespace Ui { class InformationDialog; }

class InformationDialog : public QDialog {
    Q_OBJECT  // ← Обязательно!
public:
    explicit InformationDialog(QWidget *parent = nullptr);
    void setText(const QString&);
private:
    Ui::InformationDialog *ui;
};

#endif
