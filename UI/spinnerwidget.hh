#ifndef SPINNERWIDGET_HH
#define SPINNERWIDGET_HH

#include <QObject>
#include <QWidget>
#include <memory>
#include <vector>

class SpinnerWidget : public QWidget {
  Q_OBJECT

public:
  explicit SpinnerWidget(QWidget *parent, std::vector<QString> spinnerValues);

  void spinToValue(QString value);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  std::vector<QString> spinnerValues_;
  double currentPointerAngle_ = 0;

  std::unique_ptr<QPainter> createPainter();
  void paintBackground(QPainter &painter);
  void paintSpinnerValues(QPainter &painter);
  void paintSingleSpinnerValue(QPainter &painter, QString value, double rotation);
  void paintPointer(QPainter &painter);
};

#endif // SPINNERWIDGET_HH
