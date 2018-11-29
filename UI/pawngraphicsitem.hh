#ifndef PAWNGRAPHICSITEM_HH
#define PAWNGRAPHICSITEM_HH

#include <QGraphicsObject>
#include <pawn.hh>

namespace Student {

///
/// \brief QGraphicsItem for drawing an pawn.
///
class PawnGraphicsItem : public QGraphicsItem {
public:
  explicit PawnGraphicsItem(QGraphicsItem *parent, std::shared_ptr<Common::Pawn> pawn);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  std::shared_ptr<Common::Pawn> pawn_;
};

} // namespace Student

#endif // PAWNGRAPHICSITEM_HH
