#include "spinnercontainerwidget.hh"
#include "spinnergraphicsitem.hh"

#include "fittinggraphicsview.hh"
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QPushButton>

SpinnerContainerWidget::SpinnerContainerWidget(
    QWidget *parent, std::vector<QString> spinnerValues)
    : QWidget(parent) {
  this->setLayout(new QHBoxLayout(this));
  QGraphicsView *graphicsView = new FittingGraphicsView(this);
  graphicsView->setSizePolicy(QSizePolicy::Policy::Ignored,
                              QSizePolicy::Policy::Preferred);
  QGraphicsScene *scene = new QGraphicsScene(this);
  graphicsView->setScene(scene);
  this->layout()->addWidget(graphicsView);
  setStyleSheet("background-color: transparent;");

  auto spinnerItem = new SpinnerGraphicsItem(spinnerValues);
  scene->addItem(spinnerItem);
}
