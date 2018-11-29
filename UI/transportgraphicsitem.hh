#ifndef TRANSPORTGRAPHICSITEM_HH
#define TRANSPORTGRAPHICSITEM_HH

#include <QGraphicsObject>
#include <transport.hh>

namespace Student {

///
/// \brief QGraphicsItem for drawing an transport.
///
class TransportGraphicsItem : public QGraphicsSimpleTextItem {
public:
  explicit TransportGraphicsItem(QGraphicsItem *parent,
                                 std::shared_ptr<Common::Transport> transport);

private:
  static QString transportToText(std::shared_ptr<Common::Transport> transport);
};

} // namespace Student

#endif // TRANSPORTGRAPHICSITEM_HH
