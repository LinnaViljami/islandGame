#ifndef ACTORGRAPHICSITEM_HH
#define ACTORGRAPHICSITEM_HH

#include <QGraphicsItem>
#include <actor.hh>
#include <memory>

class ActorGraphicsItem : public QGraphicsSimpleTextItem {
public:
  explicit ActorGraphicsItem(QGraphicsItem *parent,
                             std::shared_ptr<Common::Actor> actor);

private:
  static QString actorToText(std::shared_ptr<Common::Actor> actor);
};

#endif // ACTORGRAPHICSITEM_HH
