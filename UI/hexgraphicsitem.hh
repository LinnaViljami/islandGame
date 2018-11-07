#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <math.h>
#include <QObject>

namespace Student {

class HexGraphicsItem : public QGraphicsObject {
    Q_OBJECT
public:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
private slots:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
  void hexClicked();
};


} // namespace Student


#endif // HEXGRAPHICSITEM_HH
