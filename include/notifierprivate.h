#ifndef NOTIFIERPRIVATE_H
#define NOTIFIERPRIVATE_H

#include <QObject>
#include "notifytypes.h"
#include "notifyposeventfilter.h"

class QString;
class QWidget;
class NotifyWidget;
class QPropertyAnimation;
class QTimer;
class QVBoxLayout;

class Notifier;

class NotifierPrivate
{
    Q_DECLARE_PUBLIC(Notifier)
public:
    NotifierPrivate(Notifier *q_ptr);
    void initialize(QWidget *w);

private:
    QWidget *m_rootWidget       = nullptr;
    QWidget *m_notifyWidget     = nullptr;
    QVBoxLayout *m_notifyLayout = nullptr;
    QPropertyAnimation *m_showAnimation  = nullptr;
    QPropertyAnimation *m_closeAnimation = nullptr;
    QTimer *m_animationTimer = nullptr;

    QList<NotifyWidget *> m_notifyList;

    int m_activeNotifiers = 0;
    bool m_transparentForMouse = false;

    void setRootWidget(QWidget *w);
    void initialNotifyWidget();
    NotifyWidget *createNotifyWidget(const QString &title, const QString &text,
                                     Notify::NotifyType type, int msec);

    NotifyPosEventFilter *m_filterEvent;

    void resetEventFilter();
    void updateEventFilter();

    void p_notify(const QString &title, const QString &text,
                  Notify::NotifyType type = Notify::Info,
                  int msec = 1750);

    void updatePosition();

    Notifier *q_ptr = nullptr;
};

#endif // NOTIFIERPRIVATE_H
