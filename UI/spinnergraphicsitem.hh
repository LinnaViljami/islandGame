#ifndef SPINNERGRAPHICSITEM_HH
#define SPINNERGRAPHICSITEM_HH

#include "spinnerpointergraphicsitem.hh"

#include <qgraphicsitem.h>
#include <qpropertyanimation.h>
#include <memory>

class SpinnerGraphicsItem : public QGraphicsItem {
public:
  explicit SpinnerGraphicsItem(std::vector<std::string> spinnerValues);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void spinToValue(std::string value);

private:
  std::vector<std::string> spinnerValues_;
  Student::SpinnerPointerGraphicsItem &pointerItem_;

  std::shared_ptr<QPropertyAnimation> pointerAnimation_;

  void paintBackground(QPainter &painter);
  void paintSpinnerValues(QPainter &painter);
  void paintSingleSpinnerValue(QPainter &painter, std::string value,
                               double rotation);
  int getIndexOfSpinnerValue(std::string value);
};

#endif // SPINNERGRAPHICSITEM_HH
