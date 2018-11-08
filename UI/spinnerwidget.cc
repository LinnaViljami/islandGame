#include "spinnerwidget.hh"

#include <qboxlayout.h>
#include <qgraphicsview.h>
#include <qpainter.h>
#include <qpushbutton.h>

SpinnerWidget::SpinnerWidget(QWidget *parent,
                             std::vector<QString> spinnerValues)
    : QWidget(parent), spinnerValues_(spinnerValues) {
  this->setLayout(new QHBoxLayout());
}

void SpinnerWidget::spinToValue(QString value) {
  int indexOfValue = std::distance(
      spinnerValues_.begin(),
      std::find(spinnerValues_.begin(), spinnerValues_.end(), value));
  currentPointerAngle_ = indexOfValue * 360.0 / spinnerValues_.size();
  update();
}

void SpinnerWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  std::unique_ptr<QPainter> painter = createPainter();
  paintBackground(*painter);
  paintSpinnerValues(*painter);
  paintPointer(*painter);
}

std::unique_ptr<QPainter> SpinnerWidget::createPainter() {
  std::unique_ptr<QPainter> painter = std::make_unique<QPainter>(this);
  static const int penWidth = 2;
  painter->setPen(QPen(Qt::black, penWidth));
  painter->translate(width() / 2, height() / 2);
  int side = qMin(width(), height());
  double painterSideLength = (side - penWidth * 2) / 200.0;
  painter->scale(painterSideLength, painterSideLength);
  return painter;
}

void SpinnerWidget::paintBackground(QPainter &painter) {
  painter.save();
  painter.setBrush(QColor(0, 0, 255, 127));
  painter.drawEllipse(QPoint(0, 0), 100, 100);
  painter.restore();
}

void SpinnerWidget::paintSpinnerValues(QPainter &painter) {
  painter.save();
  // Default rotation for text is +90, but we want first value
  // point towards top.
  painter.rotate(-90);
  const double unitRotation = 360.0 / spinnerValues_.size();
  for (unsigned int i = 0; i < spinnerValues_.size(); ++i) {
    QString spinnerValue = spinnerValues_[i];
    double rotation = unitRotation * i;
    paintSingleSpinnerValue(painter, spinnerValue, rotation);
  }
  painter.restore();
}

void SpinnerWidget::paintSingleSpinnerValue(QPainter &painter, QString value,
                                            double rotation) {
  painter.save();
  int flags = Qt::AlignVCenter;
  // If rotation from top is over 180, text cannot just rotated
  // more, because it would apper inverted. That's why rotation
  // is always between 0 and 180, and text is aligned to left or right.
  if (rotation < 180) {
    flags = flags | Qt::AlignRight;
  } else {
    flags = flags | Qt::AlignLeft;
    rotation -= 180;
  }
  painter.rotate(rotation);
  painter.drawText(QRectF(QPointF(-95, -10), QPointF(95, 10)), flags, value);
  painter.restore();
}

void SpinnerWidget::paintPointer(QPainter &painter) {
  painter.save();
  painter.rotate(currentPointerAngle_);
  // Pointer points to top before rotation.
  static const QPoint pointerPoints[3] = {QPoint(7, 8), QPoint(-7, 8),
                                          QPoint(0, -40)};
  painter.drawConvexPolygon(pointerPoints, 3);
  painter.restore();
}
