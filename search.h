#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QDate>

namespace Ui { class SearchDialog; }

class SearchDialog : public QDialog {
    Q_OBJECT  // ← Обязательно!
public:
    explicit SearchDialog(QWidget *parent = nullptr);
    QDate getFromDate();
private:
    Ui::SearchDialog *ui;
};

#endif
