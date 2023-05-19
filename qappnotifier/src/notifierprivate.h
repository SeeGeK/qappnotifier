#ifndef NOTIFIERPRIVATE_H
#define NOTIFIERPRIVATE_H

#include "notifyposeventfilter.h"
#include "qappnotifier/notifytypes.h"

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
    NotifierPrivate(Notifier *q_ptr, QWidget *w);

private:
    Notifier *q_ptr = nullptr;

    QWidget *m_rootWidget       = nullptr;
    QWidget *m_notifyWidget     = nullptr;
    QVBoxLayout *m_notifyLayout = nullptr;
    QPropertyAnimation *m_showAnimation  = nullptr;
    QPropertyAnimation *m_closeAnimation = nullptr;
    QTimer *m_animationTimer = nullptr;

    NotifyPosEventFilter *m_filterEvent = nullptr;

    QList<NotifyWidget *> m_notifyList;

    int m_activeNotifiers = 0;

    void applyRootWidget(QWidget *w);

    Notify::Align m_align = Notify::Left;
    Notify::Align getAlign() const;
    void setAlign(const Notify::Align &align);

    NotifyWidget *createNotifyWidget(const QString &title, const QString &text,
                                     Notify::MessageType type, int msec);

    void resetEventFilter();
    void updateEventFilter();

    void p_notify(const QString &title, const QString &text,
                  Notify::MessageType type = Notify::Info,
                  int msec = 1750);

    void updateNotifiersPositions();
    QMetaObject::Connection m_connection;

    bool m_transparentForMouse = false;
    void enableCloseOnMouseClick(bool enable);
    bool isEnabledCloseOnMouseClick() const;

    void clear();
};

#endif // NOTIFIERPRIVATE_H
