#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <hex.hh>
#include <math.h>

namespace Student {

class HexGraphicsItem : public QGraphicsObject {
  Q_OBJECT
public:
  explicit HexGraphicsItem(std::shared_ptr<Common::Hex> hex);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  QPainterPath shape() const override;

signals:
  void mousePressed();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  std::shared_ptr<Common::Hex> hex_;

  static QPolygonF getShapePolygon();

  void drawPawns(QPainter *painter);
};

} // namespace Student

#endif // HEXGRAPHICSITEM_HH
