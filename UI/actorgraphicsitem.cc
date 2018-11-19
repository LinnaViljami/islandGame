#include "actorgraphicsitem.hh"

ActorGraphicsItem::ActorGraphicsItem(QGraphicsItem *parent,
                                     std::shared_ptr<Common::Actor> actor)
    : QGraphicsSimpleTextItem(parent, actorToText(actor)) {}

QString ActorGraphicsItem::actorToText(std::shared_ptr<Common::Actor> actor) {
  switch (actor->getActorType()) {
  case "kraken":
    return QString("Kraken");
  case "sea munster":
    return QString("Hirviö");
  case "shark":
    return QString("Hai");
  case "vortex":
    return QString("Pyörre");
  default:
    return QString("X");
  }
}
