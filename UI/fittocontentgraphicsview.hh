#ifndef FITTINGQRAPHICSVIEW_HH
#define FITTINGQRAPHICSVIEW_HH

#include <QGraphicsView>

class FitToContentGraphicsView : public QGraphicsView {
public:
  explicit FitToContentGraphicsView(QWidget *parent = nullptr);

protected:
  void resizeEvent(QResizeEvent *event) override;
};

#endif // FITTINGQRAPHICSVIEW_HH