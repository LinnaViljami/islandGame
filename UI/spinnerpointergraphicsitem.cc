#include "spinnerpointergraphicsitem.hh"

#include <QPainter>

namespace {

static const int HEIGHT = 40;

static const int WIDTH = 14;

static const int BOTTOM_SIDE_Y = 0;

} // namespace

Student::SpinnerPointerGraphicsItem::SpinnerPointerGraphicsItem(
    QGraphicsItem *parent)
    : QGraphicsObject(parent) {}

QRectF Student::SpinnerPointerGraphicsItem::boundingRect() const {
  return QRectF(-WIDTH / 2, -HEIGHT, WIDTH, HEIGHT);
}

void Student::SpinnerPointerGraphicsItem::paint(
    QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) {

  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->save();
  static const QPoint pointerPoints[3] = {QPoint(WIDTH / 2, BOTTOM_SIDE_Y),
                                          QPoint(-WIDTH / 2, BOTTOM_SIDE_Y),
                                          QPoint(0, -HEIGHT)};
  painter->setBrush(QBrush(Qt::GlobalColor::red));
  painter->drawConvexPolygon(pointerPoints, 3);
  painter->restore();
}
