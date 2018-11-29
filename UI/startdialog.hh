#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <qlineedit.h>
#include <vector>

namespace Ui {
class StartDialog;
}

namespace Student {

///
/// \brief The StartDialog class requests user to input player count and names.
///
class StartDialog : public QDialog {
  Q_OBJECT

public:
  explicit StartDialog(QWidget *parent = 0);
  ~StartDialog();

  ///
  /// \brief Returns the names of user inputted player names. The player count
  /// is the size of return value.
  ///
  std::vector<QString> getPlayerNames();

public slots:
  void playerCountChanged(int newCount);

private:
  Ui::StartDialog *ui;

  std::vector<QLineEdit *> playerNameLineEdits_;
};

} // namespace Student

#endif // STARTDIALOG_HH
