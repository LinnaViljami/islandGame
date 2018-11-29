#ifndef SPINNERGRAPHICSITEM_HH
#define SPINNERGRAPHICSITEM_HH

#include "spinnerpointergraphicsitem.hh"

#include <QGraphicsObject>
#include <memory>
#include <qpropertyanimation.h>

namespace Student {

///
/// \brief QGraphicsObject for drawing random spinner.
/// The values of spinner can be set arbitrary.
///
class SpinnerGraphicsItem : public QGraphicsObject {
  Q_OBJECT

public:
  ///
  /// \brief Constructor
  /// \param spinnerValues String-values of the spinner
  ///
  explicit SpinnerGraphicsItem(std::vector<std::string> spinnerValues);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  ///
  /// \brief Starts animation towards certain spinner value.
  /// \param value The target value
  ///
  void beginSpinToValue(std::string value);

signals:

  ///
  /// \brief Emitted, when spinning animation has been finished.
  ///
  void spinningFinished();

private:
  std::vector<std::string> spinnerValues_;
  Student::SpinnerPointerGraphicsItem &pointerItem_;

  std::shared_ptr<QPropertyAnimation> pointerAnimation_;

  void paintBackground(QPainter &painter);
  void paintSpinnerValues(QPainter &painter);
  void paintSingleSpinnerValue(QPainter &painter, std::string value,
                               double rotation);
  int getIndexOfSpinnerValue(std::string value);
};

} // namespace Student

#endif // SPINNERGRAPHICSITEM_HH
