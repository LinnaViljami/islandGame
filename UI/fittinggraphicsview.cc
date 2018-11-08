#include "fittinggraphicsview.hh"

FittingGraphicsView::FittingGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {}

void FittingGraphicsView::resizeEvent(QResizeEvent *event) {
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
