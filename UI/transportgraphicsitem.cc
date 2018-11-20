#include "transportgraphicsitem.hh"
namespace Student {

TransportGraphicsItem::TransportGraphicsItem(
    QGraphicsItem *parent, std::shared_ptr<Common::Transport> transport)
    : QGraphicsSimpleTextItem(transportToText(transport), parent) {}

QString TransportGraphicsItem::transportToText(
    std::shared_ptr<Common::Transport> transport) {
  std::string type = transport->getTransportType();
  if (type == "boat") {
    return QString("V");
  } else if (type == "dolphin") {
    return QString("D");
  }
  else{
      return QString("X");
  }
}

} // namespace Student
