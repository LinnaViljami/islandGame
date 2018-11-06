#include "startdialog.hh"
#include "ui_startdialog.h"

#include <QtWidgets>

StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::StartDialog) {
  ui->setupUi(this);
  connect(ui->playerCountSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
          &StartDialog::playerCountChanged);
  playerCountChanged(ui->playerCountSpinBox->value());
}

StartDialog::~StartDialog() { delete ui; }

std::vector<QString> StartDialog::getPlayerNames() {
  std::vector<QString> ret;
  for (QLineEdit *lineEdit : _playerNameLineEdits) {
    ret.push_back(lineEdit->text());
  }
  return ret;
}

void StartDialog::playerCountChanged(int newCount) {
  int currentPlayerCount = _playerNameLineEdits.size();
  if (newCount > currentPlayerCount) {
    for (int i = currentPlayerCount + 1; i <= newCount; ++i) {
      QString labelText = QString("Pelaaja %1").arg(i);
      QLineEdit *lineEdit = new QLineEdit(this);
      lineEdit->setText(labelText);
      _playerNameLineEdits.push_back(lineEdit);
      ui->playerNamesLayout->addRow(labelText, lineEdit);
    }
  } else {
    for (int i = currentPlayerCount - 1; i >= newCount; --i) {
      _playerNameLineEdits.erase(_playerNameLineEdits.begin() + i);
      ui->playerNamesLayout->removeRow(i);
    }
  }
}
