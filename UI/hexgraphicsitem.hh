#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include "actorgraphicsitem.hh"
#include "pawngraphicsitem.hh"
#include "transportgraphicsitem.hh"

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <hex.hh>
#include <math.h>
#include <memory>

namespace Student {

class HexGraphicsItem : public QGraphicsObject {
  Q_OBJECT
public:
  explicit HexGraphicsItem(std::shared_ptr<Common::Hex> hex);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  QPainterPath shape() const override;

  void addOrUpdatePawn(std::shared_ptr<Common::Pawn> pawn);

  void removePawn(int pawnId);

  void addOrUpdateActor(std::shared_ptr<Common::Actor> actor);

  void removeActor(int actorId);

  void addOrUpdateTransport(std::shared_ptr<Common::Transport> transport);

  void removeTransport(int transportId);

signals:
  void mousePressed();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  std::shared_ptr<Common::Hex> hex_;

  std::map<int, std::unique_ptr<Student::PawnGraphicsItem>> pawnItemsByIds_;

  std::map<int, std::unique_ptr<Student::ActorGraphicsItem>> actorItemsByIds_;

  std::map<int, std::unique_ptr<Student::TransportGraphicsItem>>
      transportItemsByIds_;

  void alignTextItemInsideHex(QGraphicsSimpleTextItem &item);

  QPointF getPositionForPawn(int pawnNumber);

  static QPolygonF getShapePolygon();
};

} // namespace Student

#endif // HEXGRAPHICSITEM_HH
