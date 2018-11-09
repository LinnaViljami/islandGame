#ifndef ZOOMABLEGRAPHICSVIEW_HH
#define ZOOMABLEGRAPHICSVIEW_HH

#include <QGraphicsView>

class ZoomableGraphicsView : public QGraphicsView {
public:
  explicit ZoomableGraphicsView(QWidget *parent = nullptr,
                                double zoomFactorBase = 1.00015);

  void fitToContent();

protected:
  void wheelEvent(QWheelEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

  void keyReleaseEvent(QKeyEvent *event) override;

private:
  const double zoomFactorBase_;

  double currentScale_ = 1;
};

#endif // ZOOMABLEGRAPHICSVIEW_HH
