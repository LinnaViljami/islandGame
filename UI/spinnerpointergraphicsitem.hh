#ifndef SPINNERPOINTERGRAPHICSITEM_HH
#define SPINNERPOINTERGRAPHICSITEM_HH

#include <QGraphicsItem>

namespace Student {

///
/// \brief QGraphicsObject for drawing spinner pointer.
/// This is implement with separate class to made animations easier.
///
class SpinnerPointerGraphicsItem : public QGraphicsObject {
public:
  explicit SpinnerPointerGraphicsItem(QGraphicsItem *parent);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
};

} // namespace Student

#endif // SPINNERPOINTERGRAPHICSITEM_HH
