#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "notifytypes.h"
#include <QObject>

class NotifierPrivate;
class Notifier : public QObject
{
    Q_DECLARE_PRIVATE(Notifier)
public:
    explicit Notifier(QWidget *rootWidget);
    ~Notifier();

    void enableCloseOnMouseClick(bool enable);
    bool isEnabledCloseOnMouseClick() const;

    Notify::Align getAlign() const;
    void setAlign(const Notify::Align &align);

    void clear();

    void notify(const QString &title, const QString &text, Notify::MessageType type = Notify::Info,
                int msec = 1750);

protected:
    NotifierPrivate *const d_ptr;
};


namespace Notify {

void
setNotifier(Notifier *n);

void
notify(const QString &title, const QString &text, Notify::MessageType type = Notify::Info,
        int msec = 1750);

}

#endif
