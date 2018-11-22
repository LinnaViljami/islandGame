#ifndef USERGUIDEWIDGET_HH
#define USERGUIDEWIDGET_HH

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "player.hh"
#include <memory>
#include <QString>

namespace Student {

class UserGuideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserGuideWidget(QWidget *parent = nullptr);

    void setPlayerInTurn(std::shared_ptr<Student::Player> playerInTurn);
    void setNextActionGuide(QString);
    void setAdditionalMessage(QString);
private:
    QLabel* playerInTurnText_;
    QLabel* nextActionGuideText_;
    QLabel* additionalMessageText_;
};

}
#endif // USERGUIDEWIDGET_HH
