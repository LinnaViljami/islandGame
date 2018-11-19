#include "actorgraphicsitem.hh"

namespace Student {

ActorGraphicsItem::ActorGraphicsItem(QGraphicsItem *parent,
                                     std::shared_ptr<Common::Actor> actor)
    : QGraphicsSimpleTextItem(actorToText(actor), parent) {}

QString ActorGraphicsItem::actorToText(std::shared_ptr<Common::Actor> actor) {
  std::string type = actor->getActorType();
  if (type == "kraken") {
    return QString("Kraken");
  } else if (type == "sea munster") {
    return QString("Hirviö");
  } else if (type == "shark") {
    return QString("Hai");
  } else if (type == "vortex") {
    return QString("Pyörre");
  } else {
    return QString("X");
  }
}

} // namespace Student
