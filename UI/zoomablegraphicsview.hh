#ifndef ZOOMABLEGRAPHICSVIEW_HH
#define ZOOMABLEGRAPHICSVIEW_HH

#include <QGraphicsView>

namespace Student {

///
/// \brief The ZoomableGraphicsView class is QGraphicsView-derivative which
/// provides simple zooming and panning utilities.
///
class ZoomableGraphicsView : public QGraphicsView {
public:
  ///
  /// \brief Constructor
  /// \param parent The parent of the widget
  /// \param zoomFactorBase Floating point number telling the speed of the zoom.
  /// The higher is value, the faster is zoom.
  ///
  explicit ZoomableGraphicsView(QWidget *parent = nullptr,
                                double zoomFactorBase = 1.0015);

  ///
  /// \brief Fits view to current content.
  ///
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
