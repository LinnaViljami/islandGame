#include "gameboardwidget.hh"
#include "QGraphicsView"
#include "coordinateconverter.hh"

#include <qboxlayout.h>

namespace{
    static int HEX_SCALE = 30;
}

namespace Student {

GameBoardWidget::GameBoardWidget(QWidget *parent)
    : QWidget(parent), _graphicsView(new QGraphicsView(this)) {
  this->setLayout(new QHBoxLayout(this));
  QGraphicsScene *scene = new QGraphicsScene(this);
  _graphicsView->setScene(scene);
  this->layout()->addWidget(_graphicsView);
}

void GameBoardWidget::drawHexagon(Common::CubeCoordinate coordinates) {
  QGraphicsScene *scene = _graphicsView->scene();

  removeDrawnHexItemAt(coordinates);

  shared_ptr<HexGraphicsItem> item = std::make_shared<HexGraphicsItem>();
  _hexItemsByCoordinates[coordinates] = item;

  Student::CartesianCoordinate cartesianCoord =
      Student::convertCoordinates(coordinates);
  item->setPos(HEX_SCALE * cartesianCoord.x, HEX_SCALE * cartesianCoord.y);
  item->setScale(HEX_SCALE);
  scene->addItem(item.get());
  connect(item.get(),
          &HexGraphicsItem::hexClicked,
          this,
          [coordinates, this](){emit GameBoardWidget::hexClicked(coordinates);});
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

} // namespace Student
