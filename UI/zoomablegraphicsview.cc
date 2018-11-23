#include "zoomablegraphicsview.hh"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <qmath.h>

namespace Student {

ZoomableGraphicsView::ZoomableGraphicsView(QWidget *parent,
                                           double zoomFactorBase)
    : QGraphicsView(parent), zoomFactorBase_(zoomFactorBase) {
  setMouseTracking(true);
}

void ZoomableGraphicsView::fitToContent() {
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void ZoomableGraphicsView::wheelEvent(QWheelEvent *event) {
  if (event->modifiers().testFlag(Qt::ControlModifier)) {
    double angle = event->angleDelta().y();
    double scaleFactor = qPow(zoomFactorBase_, angle);
    QPointF targetViewportPos = event->pos();
    QPointF targetScenePos = mapToScene(event->pos());
    this->scale(scaleFactor, scaleFactor);
    this->centerOn(targetScenePos);
    QPointF deltaViewPortPos =
        targetViewportPos -
        QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewPortCenter = mapFromScene(targetScenePos) - deltaViewPortPos;
    this->centerOn(mapToScene(viewPortCenter.toPoint()));
  }
}

void ZoomableGraphicsView::keyPressEvent(QKeyEvent *event) {
  if (keyEventHasShiftModifier(event)) {
    setDragMode(QGraphicsView::ScrollHandDrag);
  }
}

void ZoomableGraphicsView::keyReleaseEvent(QKeyEvent *event) {
  if (keyEventHasShiftModifier(event)) {
    setDragMode(QGraphicsView::NoDrag);
  }
}

bool ZoomableGraphicsView::keyEventHasShiftModifier(QKeyEvent *event) {
  return event->modifiers().testFlag(Qt::ShiftModifier);
}

} // namespace Student
