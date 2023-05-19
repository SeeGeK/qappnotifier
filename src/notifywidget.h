#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include "qappnotifier/notifytypes.h"

#include <QWidget>

class QLabel;
class QPropertyAnimation;
class QGraphicsOpacityEffect;

class NotifyWidget : public QWidget
{
public:
    NotifyWidget(QWidget *parent = nullptr, int msec = 1750);
    ~NotifyWidget() override;

    void createAnimation(int msec);
    void showAnimated();
    void closeAnimated();
    void setData(const QString &title, const QString &text);
    void setType(Notify::MessageType type);
    void setTransparentForMouseEvents(bool tme);

private:
    QLabel *m_titleLabel = nullptr;
    QLabel *m_infoLabel = nullptr;

    QGraphicsOpacityEffect *m_gdse = nullptr;
    QPropertyAnimation *m_animation = nullptr;
    Notify::MessageType m_type = Notify::Info;

    QTimer *m_closeTimer = nullptr;

    bool event(QEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif
