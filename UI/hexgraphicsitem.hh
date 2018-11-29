#ifndef HEXGRAPHICSITEM_HH
#define HEXGRAPHICSITEM_HH

#include "actorgraphicsitem.hh"
#include "pawngraphicsitem.hh"
#include "transportgraphicsitem.hh"

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>
#include <hex.hh>
#include <math.h>
#include <memory>

namespace Student {

///
/// \brief The HexGraphicsItem class is responsible of drawing single hex of
/// gameboard. It draws both the actual hex with correct color, and
/// corresponding QGraphicsItem- derivatives for each pawn/actor/transport.
///
class HexGraphicsItem : public QGraphicsObject {
  Q_OBJECT
public:

  ///
  /// \brief Constructs new HexGraphicsItem
  /// \param hex Used to get location, type and contents of hex.
  ///
  explicit HexGraphicsItem(std::shared_ptr<Common::Hex> hex);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  QPainterPath shape() const override;

  ///
  /// \brief Redraws all pawns, actors and trasport of the hex.
  ///
  void updateHexContents();

signals:

  ///
  /// \brief Emitted, when mouse is pressed on hex.
  ///
  void mousePressed();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  std::shared_ptr<Common::Hex> hex_;

  std::map<int, std::unique_ptr<Student::PawnGraphicsItem>> pawnItemsByIds_;

  std::map<int, std::unique_ptr<Student::ActorGraphicsItem>> actorItemsByIds_;

  std::map<int, std::unique_ptr<Student::TransportGraphicsItem>>
      transportItemsByIds_;

  QColor getPieceColor();

  void repositionAllPawnItems();

  void removeAllActors();

  void alignTextItemInsideHex(QGraphicsSimpleTextItem &item);

  QPointF getPositionForPawn(int pawnNumber);

  static QPolygonF getShapePolygon();

  void addOrUpdateActorGraphicsItem(std::shared_ptr<Common::Actor> actor);

  void addOrUpdateTransportGraphicsItem(
      std::shared_ptr<Common::Transport> transport);

  void addOrUpdatePawnGraphicsItem(std::shared_ptr<Common::Pawn> pawn);
};

} // namespace Student

#endif // HEXGRAPHICSITEM_HH
