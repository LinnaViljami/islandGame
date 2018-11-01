#include "hexgraphicsitem.hh"

namespace {

static const double r = 1;

} // namespace

namespace Student {

QRectF HexGraphicsItem::boundingRect() const { return QRectF(-r, -r, r, r); }

void HexGraphicsItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {

    static const double topAndBottomPointX = (sqrt(3) / 2) * r;
  static const double topAndBottomPointY = r / 2;
  static const QPointF points[] = {
      QPointF(0, r),
      QPointF(topAndBottomPointX, topAndBottomPointY),
      QPointF(topAndBottomPointX, -topAndBottomPointY),
      QPointF(0, -r),
      QPointF(-topAndBottomPointX, -topAndBottomPointY),
      QPointF(-topAndBottomPointX, topAndBottomPointY)};

  painter->save();
  painter->setPen(QPen(Qt::GlobalColor::black, 0));
  painter->setBrush(QColor(Qt::GlobalColor::yellow));
  painter->drawConvexPolygon(points, 6);
  painter->restore();
}

} // namespace Student
