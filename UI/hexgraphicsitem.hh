#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <math.h>

class HexGraphicsItem : public QGraphicsItem {
public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

#endif // HEXGRAPHICSITEM_HH
