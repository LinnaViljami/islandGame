#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

public slots:
    void playerCountChanged(int newCount);

private:
    Ui::StartDialog *ui;

    int _currentPlayerCount;
};

#endif // STARTDIALOG_HH
