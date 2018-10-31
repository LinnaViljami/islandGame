#ifndef GAMEBOARDWIDGET_HH
#define GAMEBOARDWIDGET_HH

#include "hex.hh"
#include <QObject>
#include <QWidget>

using Common::Hex;
using std::shared_ptr;

class GameBoardWidget : public QWidget {
  Q_OBJECT
public:
  explicit GameBoardWidget(QWidget *parent = nullptr);

  void drawHexagon(shared_ptr<Hex> hex);

signals:

public slots:
};

#endif // GAMEBOARDWIDGET_HH
