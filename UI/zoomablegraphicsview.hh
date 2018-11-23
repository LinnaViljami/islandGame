#ifndef ZOOMABLEGRAPHICSVIEW_HH
#define ZOOMABLEGRAPHICSVIEW_HH

#include <QGraphicsView>

namespace Student {

class ZoomableGraphicsView : public QGraphicsView {
public:
  explicit ZoomableGraphicsView(QWidget *parent = nullptr,
                                double zoomFactorBase = 1.0015);

  void fitToContent();

protected:
  void wheelEvent(QWheelEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

  void keyReleaseEvent(QKeyEvent *event) override;

private:
  bool keyEventHasShiftModifier(QKeyEvent *event);

  const double zoomFactorBase_;
};

} // namespace Student

#endif // ZOOMABLEGRAPHICSVIEW_HH
