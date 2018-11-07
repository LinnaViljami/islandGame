#ifndef SPINNERWIDGET_HH
#define SPINNERWIDGET_HH

#include <QObject>
#include <QWidget>
#include <vector>

class SpinnerWidget : public QWidget {
  Q_OBJECT

public:
  explicit SpinnerWidget(QWidget *parent, std::vector<QString> spinnerValues);

  void spinToValue(QString value);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  std::vector<QString> spinner_values_;
};

#endif // SPINNERWIDGET_HH
