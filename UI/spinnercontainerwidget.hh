#ifndef SPINNERCONTAINERWIDGET_HH
#define SPINNERCONTAINERWIDGET_HH

#include "spinnergraphicsitem.hh"

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

using SpinnerLayout = std::map<std::string, std::map<std::string, unsigned>>;

namespace Student {

///
/// \brief Class for combining actor type -spinner and move count -spinner.
///
class SpinnerContainerWidget : public QWidget {
  Q_OBJECT
public:
  explicit SpinnerContainerWidget(QWidget *parent, SpinnerLayout layout);

  ///
  /// \brief Begins the spins towards certain actor type and move count.
  /// \param actor The target actor type.
  /// \param moves The target move count.
  ///
  void beginSpin(std::string actor, std::string moves);

signals:

  ///
  /// \brief Emitted, when spinning animations has been finished.
  ///
  void spinningFinished();

private:
  SpinnerGraphicsItem *actorSpinnerItem_;
  SpinnerGraphicsItem *movesSpinnerItem_;

  std::vector<std::string> getActorOptions(SpinnerLayout layout);
  std::vector<std::string> getMoveOptions(SpinnerLayout layout);
};

} // namespace Student

#endif // SPINNERCONTAINERWIDGET_HH
