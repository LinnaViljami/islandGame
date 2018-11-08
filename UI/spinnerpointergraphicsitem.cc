#include "spinnerpointergraphicsitem.hh"

#include <QPainter>

namespace {

static const int HEIGHT = 32;

static const int WIDTH = 14;

static const int BOTTOM_SIDE_Y = 8;

} // namespace

Student::SpinnerPointerGraphicsItem::SpinnerPointerGraphicsItem(
    QGraphicsItem *parent)
    : QGraphicsItem(parent) {}

QRectF Student::SpinnerPointerGraphicsItem::boundingRect() const {
  return QRectF(-WIDTH / 2, -HEIGHT, WIDTH, HEIGHT);
}

void Student::SpinnerPointerGraphicsItem::paint(
    QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) {

  static const QPoint pointerPoints[3] = {QPoint(WIDTH / 2, BOTTOM_SIDE_Y),
                                          QPoint(-WIDTH / 2, BOTTOM_SIDE_Y),
                                          QPoint(0, -HEIGHT)};
  painter->drawConvexPolygon(pointerPoints, 3);
}
