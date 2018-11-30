#ifndef USERGUIDEWIDGET_HH
#define USERGUIDEWIDGET_HH

#include "player.hh"
#include <QLabel>
#include <QObject>
#include <QString>
#include <QWidget>
#include <memory>

namespace Student {

///
/// \brief Widget for showing information for user during the game.
///
class UserGuideWidget : public QWidget {
  Q_OBJECT
public:
  explicit UserGuideWidget(QWidget *parent = nullptr);

  ///
  /// \brief Sets the text value telling which player in currently in turn.
  ///
  void setPlayerInTurn(std::shared_ptr<Student::Player> playerInTurn);

  ///
  /// \brief Sets the text value describing next action.
  ///
  void setNextActionGuide(QString message);

  ///
  /// \brief Can be used to provide some additional information for user.
  ///
  void setAdditionalMessage(QString message);

  ///
  /// \brief Sets value telling which player won the game
  ///
  void setWinnerPlayer(std::shared_ptr<Student::Player> winner);
private:
  QLabel *playerInTurnText_;
  QLabel *nextActionGuideText_;
  QLabel *additionalMessageText_;
};

} // namespace Student
#endif // USERGUIDEWIDGET_HH
