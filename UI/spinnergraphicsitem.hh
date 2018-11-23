#ifndef SPINNERGRAPHICSITEM_HH
#define SPINNERGRAPHICSITEM_HH

#include "spinnerpointergraphicsitem.hh"

#include <QGraphicsObject>
#include <memory>
#include <qpropertyanimation.h>

namespace Student {

class SpinnerGraphicsItem : public QGraphicsObject {
  Q_OBJECT

public:
  explicit SpinnerGraphicsItem(std::vector<std::string> spinnerValues);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void beginSpinToValue(std::string value);

signals:
  void spinningFinished();

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

} // namespace Student

#endif // SPINNERGRAPHICSITEM_HH
