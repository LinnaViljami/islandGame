#include "gameboardwidget.hh"
#include "QGraphicsView"
#include "coordinateconverter.hh"
#include "zoomablegraphicsview.hh"

#include <QBoxLayout>
#include <QDebug>
#include <QEvent>
#include <QPushButton>

namespace {
static int HEX_SCALE = 30;
}

using Common::CubeCoordinate;
using std::shared_ptr;

namespace Student {

GameBoardWidget::GameBoardWidget(QWidget *parent)
    : QWidget(parent), _graphicsView(new ZoomableGraphicsView(this)) {
  this->setLayout(new QHBoxLayout(this));
  QGraphicsScene *scene = new QGraphicsScene(this);
  _graphicsView->setScene(scene);
  this->layout()->addWidget(_graphicsView);
}

void GameBoardWidget::addOrUpdateHex(std::shared_ptr<Common::Hex> hex) {
  QGraphicsScene *scene = _graphicsView->scene();

  CubeCoordinate coordinates = hex->getCoordinates();
  removeDrawnHexItemAt(coordinates);

  shared_ptr<HexGraphicsItem> item = std::make_shared<HexGraphicsItem>(hex);
  _hexItemsByCoordinates[coordinates] = item;

  Student::CartesianCoordinate cartesianCoord =
      Student::convertCoordinates(hex->getCoordinates());
  item->setPos(HEX_SCALE * cartesianCoord.x, HEX_SCALE * cartesianCoord.y);
  item->setScale(HEX_SCALE);
  scene->addItem(item.get());
  connect(item.get(), &HexGraphicsItem::mousePressed, this,
          [coordinates, this]() { emit hexClicked(coordinates); });
}

void GameBoardWidget::updateBoard() {
  for (auto &&pair : _hexItemsByCoordinates) {
    auto &hexItem = pair.second;
    hexItem->updateHexContents();
    hexItem->update();
  }
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
