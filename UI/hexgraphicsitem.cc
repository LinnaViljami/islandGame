#include "hexgraphicsitem.hh"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

namespace {

static const double R = 1;

} // namespace

namespace Student {

HexGraphicsItem::HexGraphicsItem(std::shared_ptr<Common::Hex> hex)
    : hex_(hex) {}

QRectF HexGraphicsItem::boundingRect() const {
  return QRectF(-R, -R, 2 * R, 2 * R);
}

void HexGraphicsItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->save();
  painter->setPen(QPen(Qt::GlobalColor::black, 0));
  painter->setBrush(QColor(Qt::GlobalColor::yellow));
  painter->drawConvexPolygon(getShapePolygon());
  painter->restore();
}

QPainterPath HexGraphicsItem::shape() const {
  QPainterPath path;
  path.addPolygon(getShapePolygon());
  path.closeSubpath();
  return path;
}

void HexGraphicsItem::addOrUpdatePawn(std::shared_ptr<Common::Pawn> pawn) {
  auto pawnItem = std::make_unique<Student::PawnGraphicsItem>(this, pawn);
  pawnItem->setScale(0.1);
  QPointF position = getPositionForPawn(pawnItemsByIds_.size() + 1);
  pawnItem->setPos(position);
  pawnItemsByIds_[pawn->getId()] = std::move(pawnItem);
}

void HexGraphicsItem::removePawn(int actorId) {
  pawnItemsByIds_.erase(actorId);
  repositionAllPawnItems();
}

void HexGraphicsItem::addOrUpdateActor(std::shared_ptr<Common::Actor> actor) {
  auto actorItem = std::make_unique<Student::ActorGraphicsItem>(this, actor);
  alignTextItemInsideHex(*actorItem);
  actorItemsByIds_[actor->getId()] = std::move(actorItem);
}

void HexGraphicsItem::removeActor(int actorId) {
  actorItemsByIds_.erase(actorId);
}

void HexGraphicsItem::addOrUpdateTransport(
    std::shared_ptr<Common::Transport> transport) {
  auto transportItem =
      std::make_unique<Student::TransportGraphicsItem>(this, transport);
  alignTextItemInsideHex(*transportItem);
  transportItemsByIds_[transport->getId()] = std::move(transportItem);
}

void HexGraphicsItem::removeTransport(int transportId) {
  transportItemsByIds_.erase(transportId);
}

void HexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  event->ignore();
  if (!scene()->views().isEmpty()) {
    if (scene()->views().first()->dragMode() == QGraphicsView::ScrollHandDrag) {
      return;
    }
  }
  emit mousePressed();
}

void HexGraphicsItem::repositionAllPawnItems() {
  int pawnNumber = 1;
  for (auto &&pair : pawnItemsByIds_) {
    auto &pawnItem = pair.second;
    QPointF position = getPositionForPawn(pawnNumber);
    pawnItem->setPos(position);
    ++pawnNumber;
  }
}

void HexGraphicsItem::alignTextItemInsideHex(QGraphicsSimpleTextItem &item) {
  static const double TEXT_SCALE = 0.05;
  QRectF boundingRect = item.boundingRect();
  QPointF pos(-boundingRect.width() / 2, -boundingRect.height() / 2);
  pos *= TEXT_SCALE;
  item.setPos(pos);
  item.setScale(TEXT_SCALE);
}

QPointF HexGraphicsItem::getPositionForPawn(int pawnNumber) {
  static const double DIST = 0.7;
  static const double X = sqrt(3) / 2;
  switch (pawnNumber) {
  default:
    return QPointF(0, 1) * DIST;
  case 1:
    return QPointF(-X, -1.0 / 2) * DIST;
  case 2:
    return QPointF(X, -1.0 / 2) * DIST;
  }
}

QPolygonF HexGraphicsItem::getShapePolygon() {
  static const double topAndBottomPointX = (sqrt(3) / 2) * R;
  static const double topAndBottomPointY = R / 2;
  static const QVector<QPointF> points = {
      QPointF(0, R),
      QPointF(topAndBottomPointX, topAndBottomPointY),
      QPointF(topAndBottomPointX, -topAndBottomPointY),
      QPointF(0, -R),
      QPointF(-topAndBottomPointX, -topAndBottomPointY),
      QPointF(-topAndBottomPointX, topAndBottomPointY)};
  return QPolygonF(points);
}

} // namespace Student
