#ifndef SPINNERGRAPHICSITEM_HH
#define SPINNERGRAPHICSITEM_HH

#include <qgraphicsitem.h>

class SpinnerGraphicsItem : public QGraphicsItem {
public:
  explicit SpinnerGraphicsItem(std::vector<QString> spinnerValues);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void spinToValue(QString value);

private:
  std::vector<QString> spinnerValues_;
  double currentPointerAngle_ = 0;

  void paintBackground(QPainter &painter);
  void paintSpinnerValues(QPainter &painter);
  void paintSingleSpinnerValue(QPainter &painter, QString value,
                               double rotation);
  void paintPointer(QPainter &painter);
};

#endif // SPINNERGRAPHICSITEM_HH
