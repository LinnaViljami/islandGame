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
    : QWidget(parent), graphicsView_(new ZoomableGraphicsView(this)) {
  this->setLayout(new QHBoxLayout(this));
  QGraphicsScene *scene = new QGraphicsScene(this);
  graphicsView_->setScene(scene);
  this->layout()->addWidget(graphicsView_);
}

void GameBoardWidget::addOrUpdateHex(std::shared_ptr<Common::Hex> hex) {
  QGraphicsScene *scene = graphicsView_->scene();

  CubeCoordinate coordinates = hex->getCoordinates();
  removeDrawnHexItemAt(coordinates);

  shared_ptr<HexGraphicsItem> item = std::make_shared<HexGraphicsItem>(hex);
  hexItemsByCoordinates_[coordinates] = item;

  Student::CartesianCoordinate cartesianCoord =
      Student::convertCoordinates(hex->getCoordinates());
  item->setPos(HEX_SCALE * cartesianCoord.x, HEX_SCALE * cartesianCoord.y);
  item->setScale(HEX_SCALE);
  scene->addItem(item.get());
  connect(item.get(), &HexGraphicsItem::mousePressed, this,
          [coordinates, this]() { emit hexClicked(coordinates); });
}

void GameBoardWidget::updateBoard() {
  for (auto &&pair : hexItemsByCoordinates_) {
    auto &hexItem = pair.second;
    hexItem->updateHexContents();
    hexItem->update();
  }
}

void GameBoardWidget::removeDrawnHexItemAt(Common::CubeCoordinate coord) {
  shared_ptr<HexGraphicsItem> item = getExistingHexItemOrNull(coord);
  if (item != nullptr) {
    graphicsView_->scene()->removeItem(item.get());
    hexItemsByCoordinates_.erase(coord);
  }
}

shared_ptr<HexGraphicsItem>
GameBoardWidget::getExistingHexItemOrNull(CubeCoordinate coord) const {
  auto iterator = hexItemsByCoordinates_.find(coord);
  if (iterator == hexItemsByCoordinates_.end()) {
    return nullptr;
  } else {
    return iterator->second;
  }
}

} // namespace Student
