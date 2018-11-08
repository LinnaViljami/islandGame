#ifndef SPINNERGRAPHICSITEM_HH
#define SPINNERGRAPHICSITEM_HH

#include "spinnerpointergraphicsitem.hh"

#include <qgraphicsitem.h>
#include <qpropertyanimation.h>
#include <memory>

class SpinnerGraphicsItem : public QGraphicsItem {
public:
  explicit SpinnerGraphicsItem(std::vector<QString> spinnerValues);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void spinToValue(QString value);

private:
  std::vector<QString> spinnerValues_;
  Student::SpinnerPointerGraphicsItem &pointerItem_;

  std::shared_ptr<QPropertyAnimation> pointerAnimation_;

  void paintBackground(QPainter &painter);
  void paintSpinnerValues(QPainter &painter);
  void paintSingleSpinnerValue(QPainter &painter, QString value,
                               double rotation);
  int getIndexOfSpinnerValue(QString value);
};

#endif // SPINNERGRAPHICSITEM_HH
