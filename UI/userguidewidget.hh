#ifndef USERGUIDEWIDGET_HH
#define USERGUIDEWIDGET_HH

#include <QObject>
#include <QWidget>
#include <QLabel>

namespace Student {

class UserGuideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserGuideWidget(QWidget *parent = nullptr);


private:
    QLabel* playerInTurnText_;
    QLabel* doNextGuideText_;
    QLabel* requestToUserText_;
};

}
#endif // USERGUIDEWIDGET_HH
