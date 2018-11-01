#include "gameboardwidget.hh"
#include "QGraphicsView"
#include "coordinateconverter.hh"

GameBoardWidget::GameBoardWidget(QWidget *parent)
    : QWidget(parent), _graphicsView(new QGraphicsView(this)) {
  QGraphicsScene *scene = new QGraphicsScene(this);
  _graphicsView->setScene(scene);
}

void GameBoardWidget::drawHexagon(Common::CubeCoordinate coordinates) {
  QGraphicsScene *scene = _graphicsView->scene();

  removeDrawnHexItemAt(coordinates);

  shared_ptr<HexGraphicsItem> item = std::make_shared<HexGraphicsItem>();
  _hexItemsByCoordinates[coordinates] = item;

  Student::CartesianCoordinate cartesianCoord =
      Student::convertCubeCoordinatesToCartesian(coordinates);
  item->setPos(cartesianCoord.x, cartesianCoord.y);
  item->setScale(100);
  scene->addItem(item.get());
}

void GameBoardWidget::removeDrawnHexItemAt(Common::CubeCoordinate coord) {
  shared_ptr<HexGraphicsItem> item = getExistingHexItemOrNull(coord);
  if (item != nullptr) {
    _graphicsView->scene()->removeItem(item.get());
    _hexItemsByCoordinates.erase(coord);
  }
}

shared_ptr<HexGraphicsItem>
GameBoardWidget::getExistingHexItemOrNull(CubeCoordinate coord) const {

  auto iterator = _hexItemsByCoordinates.find(coord);
  if (iterator == _hexItemsByCoordinates.end())
    return nullptr;
  else
    return iterator->second;
}
