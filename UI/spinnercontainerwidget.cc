#include "spinnercontainerwidget.hh"
#include "spinnergraphicsitem.hh"

#include "fittocontentgraphicsview.hh"
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QPushButton>
#include <set>

namespace Student {

SpinnerContainerWidget::SpinnerContainerWidget(QWidget *parent,
                                               SpinnerLayout layout)
    : QWidget(parent) {
  this->setLayout(new QHBoxLayout(this));
  QGraphicsView *graphicsView = new FitToContentGraphicsView(this);
  graphicsView->setSizePolicy(QSizePolicy::Policy::Ignored,
                              QSizePolicy::Policy::Preferred);
  QGraphicsScene *scene = new QGraphicsScene(this);
  graphicsView->setScene(scene);
  this->layout()->addWidget(graphicsView);
  setStyleSheet("background-color: transparent;");

  std::vector<std::string> actorOptions = getActorOptions(layout);
  std::vector<std::string> moveOptions = getMoveOptions(layout);

  actorSpinnerItem_ = new SpinnerGraphicsItem(actorOptions);
  movesSpinnerItem_ = new SpinnerGraphicsItem(moveOptions);
  movesSpinnerItem_->setPos(0, actorSpinnerItem_->boundingRect().height() + 10);
  scene->addItem(actorSpinnerItem_);
  scene->addItem(movesSpinnerItem_);

  connect(movesSpinnerItem_, &SpinnerGraphicsItem::spinningFinished, this,
          [this] { emit this->spinningFinished(); });
}

void SpinnerContainerWidget::beginSpin(std::string actor, std::string moves) {
  actorSpinnerItem_->beginSpinToValue(actor);
  movesSpinnerItem_->beginSpinToValue(moves);
}

std::vector<std::string>
SpinnerContainerWidget::getActorOptions(SpinnerLayout layout) {
  std::vector<std::string> ret;
  for (auto const &actorSectionsPair : layout) {
    ret.push_back(actorSectionsPair.first);
  }
  return ret;
}

std::vector<std::string>
SpinnerContainerWidget::getMoveOptions(SpinnerLayout layout) {
  std::set<std::string> set;
  for (auto const &actorSectionsPair : layout) {
    for (auto const &sectionsChangesPair : actorSectionsPair.second) {
      set.insert(sectionsChangesPair.first);
    }
  }
  std::vector<std::string> ret;
  std::copy(set.begin(), set.end(), std::back_inserter(ret));
  return ret;
}

} // namespace Student
