#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include "pawngraphicsitem.hh"

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

signals:
  void mousePressed();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  std::shared_ptr<Common::Hex> hex_;

  std::map<int, std::unique_ptr<Student::PawnGraphicsItem>> pawnItemsByIds_;

  QPointF getPositionForNewPawn();

  static QPolygonF getShapePolygon();
};

} // namespace Student

#endif // HEXGRAPHICSITEM_HH
