#ifndef FITTINGQRAPHICSVIEW_HH
#define FITTINGQRAPHICSVIEW_HH

#include <QGraphicsView>

class FittingGraphicsView : public QGraphicsView {
public:
  explicit FittingGraphicsView(QWidget *parent = nullptr);

protected:
  void resizeEvent(QResizeEvent *event) override;
};

#endif // FITTINGQRAPHICSVIEW_HH
