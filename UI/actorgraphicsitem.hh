#ifndef ACTORGRAPHICSITEM_HH
#define ACTORGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <actor.hh>
#include <memory>

namespace Student {

///
/// \brief QGraphicsItem for drawing an actor
///
class ActorGraphicsItem : public QGraphicsSimpleTextItem {
public:
  explicit ActorGraphicsItem(QGraphicsItem *parent,
                             std::shared_ptr<Common::Actor> actor);

private:
  static QString actorToText(std::shared_ptr<Common::Actor> actor);
};

} // namespace Student

#endif // ACTORGRAPHICSITEM_HH
