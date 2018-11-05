#ifndef GAMEBOARDWIDGET_HH
#define GAMEBOARDWIDGET_HH

#include "hex.hh"
#include "hexgraphicsitem.hh"
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <map>
#include "igamecontroller.hh"

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

  void setGameController(shared_ptr<Student::IGameController> controller);

  void drawHexagon(CubeCoordinate coordinates);

signals:

public slots:

protected:
private:
  shared_ptr<HexGraphicsItem>
  getExistingHexItemOrNull(CubeCoordinate coord) const;
  void removeDrawnHexItemAt(CubeCoordinate coord);

  map<CubeCoordinate, shared_ptr<HexGraphicsItem>> _hexItemsByCoordinates;
  QGraphicsView *_graphicsView;
  shared_ptr<Student::IGameController> _controller;
};

} // namespace Ui

#endif // GAMEBOARDWIDGET_HH
