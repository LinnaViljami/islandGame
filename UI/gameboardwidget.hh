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

class GameBoardWidget : public QWidget {
  Q_OBJECT
public:
  explicit GameBoardWidget(QWidget *parent = nullptr);

  void addOrUpdateHex(std::shared_ptr<Common::Hex> hex);

  void addOrUpdatePawn(std::shared_ptr<Common::Pawn> pawn);

signals:
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
