#include "spinnergraphicsitem.hh"
#include "spinnerpointergraphicsitem.hh"

#include <QPainter>
#include <QPropertyAnimation>

using std::string;

namespace {

static const double R = 1;
}

SpinnerGraphicsItem::SpinnerGraphicsItem(std::vector<string> spinnerValues)
    : QGraphicsItem(nullptr), spinnerValues_(spinnerValues),
      pointerAnimation_(nullptr),
      pointerItem_(*(new Student::SpinnerPointerGraphicsItem(this))) {}

QRectF SpinnerGraphicsItem::boundingRect() const {
  return QRectF(-100, -100, 200, 200);
}

void SpinnerGraphicsItem::spinToValue(std::string value) {
  int indexOfValue = getIndexOfSpinnerValue(value);
  double targetAngle = indexOfValue * (360.0 / spinnerValues_.size());
  int extraRounds = std::rand() % 2 + 1;
  double totalRotation = extraRounds * 360.0 + targetAngle;
  double startAngle = (static_cast<int>(pointerItem_.rotation()) % 360) - 360;

  pointerAnimation_ =
      std::make_unique<QPropertyAnimation>(&pointerItem_, "rotation");
  pointerAnimation_->setDuration(1000);
  pointerAnimation_->setStartValue(startAngle);
  pointerAnimation_->setEndValue(totalRotation);
  pointerAnimation_->setEasingCurve(QEasingCurve::OutQuad);
  pointerAnimation_->start();
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
    std::string spinnerValue = spinnerValues_[i];
    double rotation = unitRotation * i;
    paintSingleSpinnerValue(painter, spinnerValue, rotation);
  }
  painter.restore();
}

void SpinnerGraphicsItem::paintSingleSpinnerValue(QPainter &painter,
                                                  std::string value,
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
  painter.drawText(QRectF(QPointF(-95, -10), QPointF(95, 10)), flags, QString::fromStdString(value));
  painter.restore();
}

int SpinnerGraphicsItem::getIndexOfSpinnerValue(std::string value) {
  auto iterator =
      std::find(spinnerValues_.begin(), spinnerValues_.end(), value);
  return std::distance(spinnerValues_.begin(), iterator);
}
