#include "startdialog.hh"
#include "ui_startdialog.h"

#include <QtWidgets>

StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::StartDialog), _currentPlayerCount(0) {
  ui->setupUi(this);
  connect(ui->playerCountSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
          &StartDialog::playerCountChanged);
  playerCountChanged(ui->playerCountSpinBox->value());
}

StartDialog::~StartDialog() { delete ui; }

void StartDialog::playerCountChanged(int newCount) {
  if (newCount > _currentPlayerCount) {
    for (int i = _currentPlayerCount + 1; i <= newCount; ++i) {
      QString label = QString("Pelaaja %1").arg(i);
      ui->playerNamesLayout->addRow(label, new QLineEdit(this));
    }
  } else {
    for (int i = _currentPlayerCount - 1; i >= newCount; --i) {
      ui->playerNamesLayout->removeRow(i);
    }
  }
  _currentPlayerCount = newCount;
}
