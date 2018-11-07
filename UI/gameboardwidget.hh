#ifndef GAMEBOARDWIDGET_HH
#define GAMEBOARDWIDGET_HH

#include "hex.hh"
#include "hexgraphicsitem.hh"
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <map>

using Common::CubeCoordinate;
using Common::Hex;
using std::map;
using std::shared_ptr;
using std::unique_ptr;
using Student::HexGraphicsItem;

namespace Student {

class GameBoardWidget : public QWidget {
  Q_OBJECT
public:
  explicit GameBoardWidget(QWidget *parent = nullptr);

  void drawHexagon(CubeCoordinate coordinates);

signals:
  void hexClicked(CubeCoordinate coordinates);
public slots:
private:
  shared_ptr<HexGraphicsItem>
  getExistingHexItemOrNull(CubeCoordinate coord) const;
  void removeDrawnHexItemAt(CubeCoordinate coord);

  map<CubeCoordinate, shared_ptr<HexGraphicsItem>> _hexItemsByCoordinates;
  QGraphicsView *_graphicsView;
};

} // namespace Ui

#endif // GAMEBOARDWIDGET_HH
