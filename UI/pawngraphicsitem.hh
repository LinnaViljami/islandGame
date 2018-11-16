#ifndef PAWNGRAPHICSITEM_HH
#define PAWNGRAPHICSITEM_HH

#include <QGraphicsObject>
#include <pawn.hh>

class PawnGraphicsItem : public QGraphicsItem {
public:
  explicit PawnGraphicsItem(QGraphicsItem *parent, Common::Pawn pawn);

private:
  Common::Pawn pawn_;
};

#endif // PAWNGRAPHICSITEM_HH
