#ifndef SPINNERCONTAINERWIDGET_HH
#define SPINNERCONTAINERWIDGET_HH

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class SpinnerContainerWidget : public QWidget {
  Q_OBJECT
public:
  explicit SpinnerContainerWidget(QWidget *parent,
                                  std::vector<QString> spinnerValues);
};

#endif // SPINNERCONTAINERWIDGET_HH
