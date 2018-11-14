#ifndef SPINNERCONTAINERWIDGET_HH
#define SPINNERCONTAINERWIDGET_HH

#include "spinnergraphicsitem.hh"

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

using SpinnerLayout = std::map<std::string, std::map<std::string,unsigned>>;

class SpinnerContainerWidget : public QWidget {
  Q_OBJECT
public:
  explicit SpinnerContainerWidget(QWidget *parent, SpinnerLayout layout);

  void spin(std::string actor, std::string moves);

private:
  SpinnerGraphicsItem *actorSpinnerItem_;
  SpinnerGraphicsItem *movesSpinnerItem_;

  std::vector<std::string> getActorOptions(SpinnerLayout layout);
  std::vector<std::string> getMoveOptions(SpinnerLayout layout);
};

#endif // SPINNERCONTAINERWIDGET_HH
