#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "notifytypes.h"
#include <QObject>

class NotifierPrivate;
class Notifier : public QObject
{
    Q_OBJECT

public:
    explicit Notifier(QWidget *rootWidget);
    ~Notifier() override;

    void setTransparentForMouseEvents(bool tme);
    void clear();

    enum Align {Left, Right};

    Align getAlign() const;
    void setAlign(const Align &align);

signals:
    void notify(const QString &title, const QString &text, Notify::NotifyType type = Notify::Info,
                int msec = 1750);

    void updatePosition();

private:
    Q_DECLARE_PRIVATE_D(m_d_ptr, Notifier)
    NotifierPrivate * const m_d_ptr = nullptr;
    Align m_align = Left;
};



void
setRNotifier(Notifier *n);

void
rNotify(const QString &title, const QString &text, Notify::NotifyType type = Notify::Info,
        int msec = 1750);

#endif
