#ifndef GAMEBOARDWIDGET_HH
#define GAMEBOARDWIDGET_HH

#include "hex.hh"
#include "hexgraphicsitem.hh"
#include "zoomablegraphicsview.hh"
#include <QFrame>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <map>
#include <memory>
#include <pawn.hh>

namespace Student {

///
/// \brief Widget, which is responsible of drawing all hexes of the gameboard.
///
class GameBoardWidget : public QWidget {
  Q_OBJECT
public:
  explicit GameBoardWidget(QWidget *parent = nullptr);

  ///
  /// \brief Draws a HexGraphicsItem corresponding to \p hex.
  /// If there already is item in the location of the \p hex,
  /// old one is removed.
  ///
  void addOrUpdateHex(std::shared_ptr<Common::Hex> hex);

  ///
  /// \brief Redraws whole board.
  ///
  void updateBoard();

signals:

  ///
  /// \brief hexClicked is emitted, when any of the HexGraphicsItem is clicked.
  /// \param coordinates The coordinates of the clicked hex.
  ///
  void hexClicked(Common::CubeCoordinate coordinates);

private:
  std::shared_ptr<Student::HexGraphicsItem>
  getExistingHexItemOrNull(Common::CubeCoordinate coord) const;
  void removeDrawnHexItemAt(Common::CubeCoordinate coord);
  std::map<Common::CubeCoordinate, std::shared_ptr<Student::HexGraphicsItem>>
      _hexItemsByCoordinates;
  ZoomableGraphicsView *_graphicsView;
};

} // namespace Student

#endif // GAMEBOARDWIDGET_HH
