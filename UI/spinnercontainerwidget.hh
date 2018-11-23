#ifndef SPINNERCONTAINERWIDGET_HH
#define SPINNERCONTAINERWIDGET_HH

#include "spinnergraphicsitem.hh"

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

using SpinnerLayout = std::map<std::string, std::map<std::string, unsigned>>;

namespace Student {

class SpinnerContainerWidget : public QWidget {
  Q_OBJECT
public:
  explicit SpinnerContainerWidget(QWidget *parent, SpinnerLayout layout);

  void beginSpin(std::string actor, std::string moves);

signals:
  void spinningFinished();

private:
  SpinnerGraphicsItem *actorSpinnerItem_;
  SpinnerGraphicsItem *movesSpinnerItem_;

  std::vector<std::string> getActorOptions(SpinnerLayout layout);
  std::vector<std::string> getMoveOptions(SpinnerLayout layout);
};

} // namespace Student

#endif // SPINNERCONTAINERWIDGET_HH
