#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <math.h>

namespace Student {

class HexGraphicsItem : public QGraphicsObject {
  Q_OBJECT
public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
  void mouseReleased();
};

} // namespace Student

#endif // HEXGRAPHICSITEM_HH
