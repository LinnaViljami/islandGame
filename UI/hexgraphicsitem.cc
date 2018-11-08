#include "hexgraphicsitem.hh"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

namespace {

static const double R = 1;

} // namespace

namespace Student {

QRectF HexGraphicsItem::boundingRect() const {
  return QRectF(-R, -R, 2 * R, 2 * R);
}

void HexGraphicsItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  static const double topAndBottomPointX = (sqrt(3) / 2) * R;
  static const double topAndBottomPointY = R / 2;
  static const QPointF points[] = {
      QPointF(0, R),
      QPointF(topAndBottomPointX, topAndBottomPointY),
      QPointF(topAndBottomPointX, -topAndBottomPointY),
      QPointF(0, -R),
      QPointF(-topAndBottomPointX, -topAndBottomPointY),
      QPointF(-topAndBottomPointX, topAndBottomPointY)};

  painter->save();
  painter->setPen(QPen(Qt::GlobalColor::black, 0));
  painter->setBrush(QColor(Qt::GlobalColor::yellow));
  painter->drawConvexPolygon(points, 6);
  painter->restore();
}

void HexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  event->ignore();
  emit mouseReleased();
}

} // namespace Student
