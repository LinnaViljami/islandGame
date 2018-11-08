#include "spinnergraphicsitem.hh"
#include "spinnerpointergraphicsitem.hh"

#include <QPainter>

namespace {

static const double R = 1;
}

SpinnerGraphicsItem::SpinnerGraphicsItem(std::vector<QString> spinnerValues)
    : QGraphicsItem(nullptr), spinnerValues_(spinnerValues),
      pointerItem_(*(new Student::SpinnerPointerGraphicsItem(this))) {}

QRectF SpinnerGraphicsItem::boundingRect() const {
  return QRectF(-100, -100, 200, 200);
}

void SpinnerGraphicsItem::spinToValue(QString value) {
  int indexOfValue = getIndexOfSpinnerValue(value);
  pointerItem_.setRotation(indexOfValue * (360.0 / spinnerValues_.size()));
}

void SpinnerGraphicsItem::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {

  Q_UNUSED(option);
  Q_UNUSED(widget);

  paintBackground(*painter);
  paintSpinnerValues(*painter);
}

void SpinnerGraphicsItem::paintBackground(QPainter &painter) {
  painter.save();
  painter.setBrush(QColor(0, 0, 255, 127));
  painter.drawEllipse(QPoint(0, 0), 100, 100);
  painter.restore();
}

void SpinnerGraphicsItem::paintSpinnerValues(QPainter &painter) {
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

void SpinnerGraphicsItem::paintSingleSpinnerValue(QPainter &painter,
                                                  QString value,
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

int SpinnerGraphicsItem::getIndexOfSpinnerValue(QString value) {
  auto iterator =
      std::find(spinnerValues_.begin(), spinnerValues_.end(), value);
  return std::distance(spinnerValues_.begin(), iterator);
}
