#include "spinnerwidget.hh"

#include <qboxlayout.h>
#include <qgraphicsview.h>
#include <qpainter.h>
#include <qpushbutton.h>

SpinnerWidget::SpinnerWidget(QWidget *parent,
                             std::vector<QString> spinnerValues)
    : QWidget(parent), spinner_values_(spinnerValues) {
  this->setLayout(new QHBoxLayout());
}

void SpinnerWidget::spinToValue(QString value) {}

void SpinnerWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  static const int penWidth = 2;
  painter.translate(width() / 2, height() / 2);
  int side = qMin(width(), height());
  double painterSide = (side - penWidth * 2) / 200.0;
  painter.scale(painterSide, painterSide);
  painter.setPen(QPen(Qt::black, penWidth));
  painter.drawEllipse(QPoint(0, 0), 100, 100);
}
