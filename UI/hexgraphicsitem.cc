#include "hexgraphicsitem.hh"

namespace {

static const double yFactor = sqrt(3) / 2;

static const double r = 100;

} // namespace

QRectF HexGraphicsItem::boundingRect() const { return QRectF(-r, -r, r, r); }

void HexGraphicsItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {

  static const double topDownPointX = r / 2;
  static const double topDownPointY = yFactor * r;
  const QPointF points[] = {QPointF(r, 0),
                            QPointF(topDownPointX, topDownPointY),
                            QPointF(-topDownPointX, topDownPointY),
                            QPointF(-r, 0),
                            QPointF(-topDownPointX, -topDownPointY),
                            QPointF(topDownPointX, -topDownPointY)};

  painter->save();
  painter->setBrush(QColor(Qt::GlobalColor::yellow));
  painter->drawConvexPolygon(points, 6);
  painter->restore();
}
