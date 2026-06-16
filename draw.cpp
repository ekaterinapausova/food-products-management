#include "draw.h"
#include "ui_draw.h"
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <algorithm>
#include <QPainter>
#include <QVBoxLayout>

DrawDialog::DrawDialog(QWidget *parent, const QList<Product>& data)
    : QDialog(parent), ui(new Ui::DrawDialog), products(data) {
    ui->setupUi(this);

    // Увеличиваем размер окна
    this->resize(900, 700);

    QStringList names;
    for (const auto& p : products)
        if (!names.contains(p.name))
            names << p.name;

    ui->productCombo->addItems(names);

    connect(ui->productCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DrawDialog::buildGraph);

    if (!names.isEmpty())
        buildGraph();
}

DrawDialog::~DrawDialog() {
    delete ui;
}

void DrawDialog::buildGraph() {
    QString name = ui->productCombo->currentText();
    if (name.isEmpty()) return;

    // Очистка старого графика
    QLayoutItem* child;
    while ((child = ui->graphContainer->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QList<Product> filtered;
    for (const auto& p : products)
        if (p.name == name)
            filtered.append(p);

    std::sort(filtered.begin(), filtered.end(), [](const Product& a, const Product& b){
        return a.deliveryDate < b.deliveryDate;
    });

    auto *series = new QLineSeries();
    series->setName("Количество");

    int i = 0;
    for (const auto& p : filtered) {
        series->append(i, p.quantity);
        i++;
    }

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Поступления: " + name);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Поставка");
    chart->axes(Qt::Vertical).first()->setTitleText("Штук");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(700, 400);

    // Добавляем график (без stretch параметра)
    ui->graphContainer->layout()->addWidget(chartView);
}
