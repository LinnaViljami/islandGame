#include "actorgraphicsitem.hh"

namespace Student {

ActorGraphicsItem::ActorGraphicsItem(QGraphicsItem *parent,
                                     std::shared_ptr<Common::Actor> actor)
    : QGraphicsSimpleTextItem(actorToText(actor), parent) {}

QString ActorGraphicsItem::actorToText(std::shared_ptr<Common::Actor> actor) {
  std::string type = actor->getActorType();
  if (type == "kraken") {
    return QString("K");
  } else if (type == "seamunster") {
    return QString("MH");
  } else if (type == "shark") {
    return QString("H");
  } else if (type == "vortex") {
    return QString("P");
  } else {
    return QString("X");
  }
}

} // namespace Student
