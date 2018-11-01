#include "hexgraphicsitem.hh"

namespace {

static const double r = 1;

} // namespace

namespace Student {

QRectF HexGraphicsItem::boundingRect() const { return QRectF(-r, -r, r, r); }

void HexGraphicsItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {

  static const double topAndBottomPointX = r / 2;
  static const double topAndBottomPointY = (sqrt(3) / 2) * r;
  static const QPointF points[] = {
      QPointF(r, 0),
      QPointF(topAndBottomPointX, topAndBottomPointY),
      QPointF(-topAndBottomPointX, topAndBottomPointY),
      QPointF(-r, 0),
      QPointF(-topAndBottomPointX, -topAndBottomPointY),
      QPointF(topAndBottomPointX, -topAndBottomPointY)};

  painter->save();
  painter->setBrush(QColor(Qt::GlobalColor::yellow));
  painter->drawConvexPolygon(points, 6);
  painter->restore();
}

} // namespace Student
