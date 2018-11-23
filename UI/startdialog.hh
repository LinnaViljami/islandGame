#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <qlineedit.h>
#include <vector>

namespace Ui {
class StartDialog;
}

namespace Student {

class StartDialog : public QDialog {
  Q_OBJECT

public:
  explicit StartDialog(QWidget *parent = 0);
  ~StartDialog();

  std::vector<QString> getPlayerNames();

public slots:
  void playerCountChanged(int newCount);

private:
  Ui::StartDialog *ui;

  std::vector<QLineEdit *> _playerNameLineEdits;
};

} // namespace Student

#endif // STARTDIALOG_HH
