#include "zoomablegraphicsview.hh"
#include <QDebug>>
#include <QScrollBar>
#include <QWheelEvent>
#include <qmath.h>

ZoomableGraphicsView::ZoomableGraphicsView(QWidget *parent,
                                           double zoomFactorBase)
    : QGraphicsView(parent), zoomFactorBase_(1.0015) {
  setMouseTracking(true);
}

void ZoomableGraphicsView::fitToContent() {
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void ZoomableGraphicsView::wheelEvent(QWheelEvent *event) {
  if (event->modifiers().testFlag(Qt::ControlModifier)) {
    double angle = event->angleDelta().y();
    double scaleFactor = qPow(zoomFactorBase_, angle);

    static const double minScale = 1;
    if (angle < 0 && currentScale_ <= minScale) {
      return;
    }
    currentScale_ *= scaleFactor;

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
  if (event->modifiers().testFlag(Qt::ShiftModifier)) {
    setDragMode(QGraphicsView::ScrollHandDrag);
  }
}

void ZoomableGraphicsView::keyReleaseEvent(QKeyEvent *event) {
  if (event->modifiers().testFlag(Qt::ShiftModifier)) {
    setDragMode(QGraphicsView::NoDrag);
  }
}
