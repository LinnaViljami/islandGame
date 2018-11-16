#include "fittocontentgraphicsview.hh"

FitToContentGraphicsView::FitToContentGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {}

void FitToContentGraphicsView::resizeEvent(QResizeEvent *event) {
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
