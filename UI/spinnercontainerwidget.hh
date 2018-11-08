#ifndef SPINNERCONTAINERWIDGET_HH
#define SPINNERCONTAINERWIDGET_HH

#include "spinnergraphicsitem.hh"

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class SpinnerContainerWidget : public QWidget {
  Q_OBJECT
public:
  explicit SpinnerContainerWidget(QWidget *parent,
                                  std::vector<QString> spinnerValues);

  void spinToValue(QString value);

private:
  SpinnerGraphicsItem *spinnerItem_;
};

#endif // SPINNERCONTAINERWIDGET_HH
