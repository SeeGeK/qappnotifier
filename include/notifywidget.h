#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include <QWidget>
#include "notifytypes.h"

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
    void setType(Notify::NotifyType type);
    void setTransparentForMouseEvents(bool tme);

private:
    QLabel *m_titleLabel;
    QLabel *m_infoLabel;

    QGraphicsOpacityEffect *gdse;
    QPropertyAnimation *animation;
    Notify::NotifyType m_type = Notify::Info;

    QTimer *m_closeTimer;

    bool event(QEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif
