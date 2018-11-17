#include "pawngraphicsitem.hh"

#include <QPainter>

namespace Student {

PawnGraphicsItem::PawnGraphicsItem(QGraphicsItem *parent,
                                   std::shared_ptr<Common::Pawn> pawn)
    : QGraphicsItem(parent), pawn_(pawn) {}

QRectF PawnGraphicsItem::boundingRect() const { return QRect(-1, -1, 2, 2); }

void PawnGraphicsItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  static const QVector<QPointF> points = {QPointF(-1, -1), QPointF(1, -1),
                                          QPointF(-1, 1), QPointF(1, 1)};
  painter->save();
  painter->drawPolygon(QPolygonF(points));
  painter->restore();
}

} // namespace Student
