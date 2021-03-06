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
  painter->setBrush(getPieceColor());
  painter->drawConvexPolygon(getShapePolygon());
  painter->restore();
}

QPainterPath HexGraphicsItem::shape() const {
  QPainterPath path;
  path.addPolygon(getShapePolygon());
  path.closeSubpath();
  return path;
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

void HexGraphicsItem::updateHexContents()
{
    pawnItemsByIds_.clear();
    for(std::shared_ptr<Common::Pawn> pawn : hex_->getPawns()){
        addOrUpdatePawnGraphicsItem(pawn);
    }
    actorItemsByIds_.clear();
    for(std::shared_ptr<Common::Actor> actor : hex_->getActors()){
        addOrUpdateActorGraphicsItem(actor);
    }
    transportItemsByIds_.clear();
    for(std::shared_ptr<Common::Transport> transport : hex_->getTransports()){
        addOrUpdateTransportGraphicsItem(transport);
    }
}

void HexGraphicsItem::addOrUpdatePawnGraphicsItem(std::shared_ptr<Common::Pawn> pawn) {
  auto pawnItem = std::make_unique<Student::PawnGraphicsItem>(this, pawn);
  pawnItem->setScale(0.1);
  QPointF position = getPositionForPawn(pawnItemsByIds_.size() + 1);
  pawnItem->setPos(position);
  pawnItemsByIds_[pawn->getId()] = std::move(pawnItem);
}

void HexGraphicsItem::addOrUpdateActorGraphicsItem(std::shared_ptr<Common::Actor> actor) {
  auto actorItem = std::make_unique<Student::ActorGraphicsItem>(this, actor);
  alignTextItemInsideHex(*actorItem);
  actorItemsByIds_[actor->getId()] = std::move(actorItem);
}

void HexGraphicsItem::addOrUpdateTransportGraphicsItem(
    std::shared_ptr<Common::Transport> transport) {
  auto transportItem =
      std::make_unique<Student::TransportGraphicsItem>(this, transport);
  alignTextItemInsideHex(*transportItem);
  transportItemsByIds_[transport->getId()] = std::move(transportItem);
}

QColor HexGraphicsItem::getPieceColor() {
  std::string pieceType = hex_->getPieceType();
  if (pieceType == "Coral") {
    return QColor(124, 211, 208);
  } else if (pieceType == "Water") {
    return QColor(75, 165, 234);
  } else if (pieceType == "Beach") {
    return QColor(214, 202, 72);
  } else if (pieceType == "Forest") {
    return QColor(60, 140, 53);
  } else if (pieceType == "Mountain") {
    return QColor(154, 158, 157);
  } else if (pieceType == "Peak") {
    return QColor(80, 81, 81);
  } else {
    return QColor(Qt::GlobalColor::black);
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
