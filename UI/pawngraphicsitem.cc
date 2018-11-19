#include "pawngraphicsitem.hh"

#include <QPainter>

namespace {
static const std::vector<Qt::GlobalColor> playerColors{
    Qt::GlobalColor::green, Qt::GlobalColor::blue, Qt::GlobalColor::red,
    Qt::GlobalColor::yellow};
}

namespace Student {

PawnGraphicsItem::PawnGraphicsItem(QGraphicsItem *parent,
                                   std::shared_ptr<Common::Pawn> pawn )
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
  QColor color = QColor(playerColors[pawn_->getPlayerId()]);
  painter->setBrush(QBrush(color));
  painter->setPen(color);
  painter->drawPolygon(QPolygonF(points));
  painter->restore();
}

} // namespace Student
