#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include <QColor>
#include <QString>
#include <QColor>

namespace Student {

class Player : public Common::IPlayer {

public:
  Player(int id, unsigned int actionsLeft, QString name);

  /**
   * @copydoc IPlayer::getPlayerId()
   */
  virtual int getPlayerId() const;

  /**
   * @copydoc IPlayer::setActionsLeft()
   */
  virtual void setActionsLeft(unsigned int actionsLeft);

  /**
   * @copydoc IPlayer::getActionsLeft()
   */
  virtual unsigned int getActionsLeft() const;

  QString getName() const;

  ///
  /// \brief addPoints Add points for player.
  /// \param change Amount of the change in points. Can be positive or negative.
  ///
  void addPoints(int change);

  int getPoints() const;

  ///
  /// \brief Returns the color for the player with \p playerId
  /// This function is static for technical reasons.
  ///
  static QColor getPlayerColor(int playerId);
private:
  int id_;

  unsigned int actionsLeft_;

  QString name_;

  int points_;
};

} // namespace Student

#endif // PLAYER_HH
