#include "fittocontentgraphicsview.hh"

namespace Student {

FitToContentGraphicsView::FitToContentGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {}

void FitToContentGraphicsView::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event)
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

} // namespace Student
