#ifndef PLAYERPOINTSWIDGET_HH
#define PLAYERPOINTSWIDGET_HH

#include "player.hh"

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <memory>

namespace Student {

///
/// \brief Widget for telling the points of the players.
///
class PlayerPointsWidget : public QWidget {
  Q_OBJECT
public:
  explicit PlayerPointsWidget(
      QWidget *parent, std::vector<std::shared_ptr<Student::Player>> players);

  ///
  /// \brief Updates points of each player. Points are fetched from player
  /// objects.
  ///
  void refreshPoints();

private:
  std::map<std::shared_ptr<Student::Player>, QLabel *> playerTextsByPlayers_;
};

} // namespace Student

#endif // PLAYERPOINTSWIDGET_HH
